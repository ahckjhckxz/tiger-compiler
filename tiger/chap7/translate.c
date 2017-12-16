#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "absyn.h"
#include "types.h"
#include "temp.h"
#include "tree.h"
#include "frame.h"
#include "translate.h"
#include "printtree.h"
extern char asmBuf[0xFFFFFFF];
extern Temp_label main_label;
/******frame******/
struct Tr_level_ {
	Tr_level parent;
	Temp_label name;
	F_frame frame;
	Tr_accessList formals;
};

struct Tr_access_ {
	Tr_level level;
	F_access access;
};

static Tr_accessList makeFormalAccessList(Tr_level);
static Tr_access Tr_Access(Tr_level, F_access);
/**debug info**/
static void display_l(Tr_level);
static void display_ac(Tr_access);
/*******IR*******/
struct Cx {
	patchList trues;
	patchList falses;
	T_stm stm;
};

struct Tr_exp_ {
	/* actually Tr_exp_ is (T_ex, T_nx, struct Cx)'s set 
	 * T_stm also can express T_exp
	 * T_exp stand for a exp-val
	 * struct Cx stand for condition-jump
	 */
	enum {Tr_ex, Tr_nx, Tr_cx} kind;
	union {
		T_exp ex;    /*exp*/
		T_stm nx;    /*non-exp*/
		struct Cx cx;/*condition-stm*/ 
	} u;
};

struct patchList_ {
	Temp_label * head; /*??? why save a point-to-Temp_label (because) */
	patchList tail;
};

struct Tr_expList_ {
	Tr_exp head;
	Tr_expList tail;
};
int numLevel(Tr_level l)
{
	int n = 0;
	while (l->parent)
	{
		l = l->parent;
		n++;
	}
	return n;
}
static Tr_exp Tr_Ex(T_exp);
static Tr_exp Tr_Nx(T_stm);
static Tr_exp Tr_Cx(patchList, patchList, T_stm);
static patchList PatchList(Temp_label *, patchList);
static T_exp unEx(Tr_exp);
static T_stm unNx(Tr_exp);
static struct Cx unCx(Tr_exp);
static void doPatch(patchList, Temp_label);
static patchList joinPatch(patchList, patchList);
static Tr_exp Tr_StaticLink(Tr_level, Tr_level);

Tr_expList Tr_ExpList(Tr_exp h, Tr_expList t) {
    Tr_expList l = checked_malloc(sizeof(*l));
	l->head = h;
	l->tail = t;
	return l;
}

void Tr_expList_prepend(Tr_exp h, Tr_expList * l) {
	/* add a newhead at a old expList, alter the point-content*/
	Tr_expList newhead = Tr_ExpList(h, NULL);
	newhead->tail = *l;
	*l = newhead;
}
int isOutmost(Tr_level level) {
	return (level->parent == NULL) ? 1 : 0;
}
static Tr_exp Tr_Ex(T_exp exp) {
	/* trans T_exp to Tr_exp*/
	Tr_exp e = checked_malloc(sizeof(*e));
	e->kind = Tr_ex;
	e->u.ex = exp;
	return e;
}

static Tr_exp Tr_Nx(T_stm stm) {
	/* trans T_stm to Tr_exp */
	Tr_exp e = checked_malloc(sizeof(*e));
	e->kind = Tr_nx;
	e->u.nx = stm;
	return e;
}

static Tr_exp Tr_Cx(patchList trues, patchList falses, T_stm stm) {
	Tr_exp e = checked_malloc(sizeof(*e));
	e->kind = Tr_cx;
	e->u.cx.trues  = trues;
	e->u.cx.falses = falses;
	e->u.cx.stm    = stm;
	return e;
}

static T_exp unEx(Tr_exp e) {
	/*trans Tr_exp to T_exp*/
	switch (e->kind) {
	case Tr_ex:
		return e->u.ex;
	case Tr_nx:
		return T_Eseq(e->u.nx, T_Const(0));
	case Tr_cx: {
		Temp_temp r = Temp_newtemp(); /* temp for save exp-val */
		Temp_label t = Temp_newlabel(), f = Temp_newlabel(); /* actually ture-label & false-label added here */
		doPatch(e->u.cx.trues, t);
		doPatch(e->u.cx.falses, f);
		return T_Eseq(T_Move(T_Temp(r), T_Const(1)),
				      T_Eseq(e->u.cx.stm,
						     T_Eseq(T_Label(f),
								    T_Eseq(T_Move(T_Temp(r), T_Const(0)),
										   T_Eseq(T_Label(t), T_Temp(r))))));
		}
	}
	assert(0 && "only 3 condition");
}

static T_stm unNx(Tr_exp e) {
	/*trans Tr_exp to T_stm*/
	switch (e->kind) {
    case Tr_ex:
		return T_Exp(e->u.ex);
	case Tr_nx:
		return e->u.nx;
	case Tr_cx: {
		Temp_temp r = Temp_newtemp(); /*temp for save exp-val*/
		Temp_label t = Temp_newlabel(), f = Temp_newlabel(); /* ture-label & false-label added here */
		doPatch(e->u.cx.trues, t);
		doPatch(e->u.cx.falses, f);
		return T_Exp(T_Eseq(T_Move(T_Temp(r), T_Const(1)),
				            T_Eseq(e->u.cx.stm,
						           T_Eseq(T_Label(f),
								          T_Eseq(T_Move(T_Temp(r), T_Const(0)),
										         T_Eseq(T_Label(t), T_Temp(r)))))));

		}
	}
	assert(0);
}

static struct Cx unCx(Tr_exp e){
	switch (e->kind) {
	case Tr_cx:
		return e->u.cx;
	case Tr_ex: {
		struct Cx cx;
		/*there is no real-label in patchList*/
		cx.stm = T_Cjump(T_eq, e->u.ex, T_Const(1), NULL, NULL);
		cx.trues = PatchList(&(cx.stm->u.CJUMP.true), NULL);
		cx.falses = PatchList(&(cx.stm->u.CJUMP.false), NULL);
		return cx;
	}
	case Tr_nx:
		assert(0); /*this should not occur*/
	}
	assert(0);
}

Tr_exp Tr_simpleVar(Tr_access ac, Tr_level l) {
	T_exp addr = T_Temp(F_FP());
	while (l != ac->level) { 
		addr = F_ExpUp(addr);
		l = l->parent;
	}
	return Tr_Ex(F_Exp(ac->access, addr)); 
}

Tr_exp Tr_fieldVar(Tr_exp base, int offs) {
	/* return base + offs * WORD-SIZE */
	return Tr_Ex(T_Mem(T_Binop(T_plus, unEx(base), T_Const(offs * F_WORD_SIZE))));
}

Tr_exp Tr_subscriptVar(Tr_exp base, Tr_exp index) {
	/* return base + index * WORD-SIZE */
	return Tr_Ex(T_Mem(T_Binop(T_plus,
					           unEx(base),
							   T_Binop(T_mul, unEx(index), T_Const(F_WORD_SIZE)))));
}

static F_fragList fragList[100];
Temp_label getLevelName(Tr_level level)
{
	return level->name;
}
void Tr_procEntryExit(Tr_level level, Tr_exp body, Tr_accessList formals) {
	F_frag procfrag = F_ProcFrag(unNx(body), level->frame, level->name);
	fragList[numLevel(level)] = F_FragList(procfrag, fragList[numLevel(level)]);
}
void Tr_decEntryExit(Tr_level level, Tr_exp body, Tr_accessList formals) {
	F_frag decfrag = F_DecFrag(unNx(body), level->frame);
	fragList[numLevel(level)] = F_FragList(decfrag, fragList[numLevel(level)]);
}
static F_fragList stringFragList = NULL;
Tr_exp Tr_stringExp(string s) { 
	/*const-string is a label point a addr*/
	Temp_label slabel = Temp_newlabel();
	F_frag fragment = F_StringFrag(slabel, s);
	stringFragList = F_FragList(fragment, stringFragList);
	return Tr_Ex(T_Name(slabel));
}

Tr_exp Tr_intExp(int i) {
	return Tr_Ex(T_Const(i));
}

Tr_exp Tr_doubleExp(float f) {
	return Tr_Ex(T_Double(f));
}

static Temp_temp nilTemp = NULL;
Tr_exp Tr_nilExp() {
	if (!nilTemp) {
		nilTemp = Temp_newtemp(); /*use Temp_temp for nil due to compatible record type*/
		/*??? why init nil record 0 SIZE*/
		T_stm alloc = T_Move(T_Temp(nilTemp),
				             F_externalCall(String("initRecord"), T_ExpList(T_Const(0), NULL)));
		return Tr_Ex(T_Eseq(alloc, T_Temp(nilTemp)));
	}
	return Tr_Ex(T_Temp(nilTemp));
}

Tr_exp Tr_noExp() {
	/*const 0 stand-for non-val-exp*/
	return Tr_Ex(T_Const(0));
}

Tr_exp Tr_recordExp(int n, Tr_expList l) {
	Temp_temp r = Temp_newtemp();
	/*alloc n * WORD-SIZE mem*/
	T_stm alloc = T_Move(T_Temp(r),
			             F_externalCall(String("initRecord"), T_ExpList(T_Const(n * F_WORD_SIZE), NULL)));

	int i = n - 1;
	T_stm seq = T_Move(T_Mem(T_Binop(T_plus, T_Temp(r), T_Const(i-- * F_WORD_SIZE))), 
						     unEx(l->head));

	/*put value to the alloc-addr*/
	for (l = l->tail; l; l = l->tail, i--) {
		seq = T_Seq(T_Move(T_Mem(T_Binop(T_plus, T_Temp(r), T_Const(i * F_WORD_SIZE))), 
						   unEx(l->head)),
				    seq);
	}
	/* resl is a pointer point addr */
	return Tr_Ex(T_Eseq(T_Seq(alloc, seq), T_Temp(r)));
}

Tr_exp Tr_arrayExp(Tr_exp size, Tr_exp init) {
	return Tr_Ex(F_externalCall(String("initArray"), 
				                T_ExpList(unEx(size), T_ExpList(unEx(init), NULL))));
}

Tr_exp Tr_seqExp(Tr_expList l) {
	T_exp resl = unEx(l->head); /* resl cant be NULL */
	for (l = l->tail; l; l = l->tail) {
		resl = T_Eseq(T_Exp(unEx(l->head)), resl);
	}
	return Tr_Ex(resl);
}

Tr_exp Tr_doneExp() { return Tr_Ex(T_Name(Temp_newlabel())); } /* doneExp may is a breakExp JUMP label */

Tr_exp Tr_whileExp(Tr_exp test, Tr_exp body, Tr_exp done) {
	/* use your pen draw this data graph then you understand */
	Temp_label testl = Temp_newlabel(), bodyl = Temp_newlabel();
	return Tr_Ex(T_Eseq(T_Jump(T_Name(testl), Temp_LabelList(testl, NULL)), 
				        T_Eseq(T_Label(bodyl),
							   T_Eseq(unNx(body),
								      T_Eseq(T_Label(testl),
								             T_Eseq(T_Cjump(T_eq, unEx(test), T_Const(0), unEx(done)->u.NAME, bodyl),
										            T_Eseq(T_Label(unEx(done)->u.NAME), T_Const(0))))))));
}

Tr_exp Tr_assignExp(Tr_exp lval, Tr_exp exp) { return Tr_Nx(T_Move(unEx(lval), unEx(exp))); }
Tr_exp Tr_forExp(Tr_exp lval, Tr_exp lo, Tr_exp hi, Tr_exp body, Tr_exp done) {
	/* use your pen draw this data graph then you understand */
	Temp_label testl = Temp_newlabel(), bodyl = Temp_newlabel();
	return Tr_Ex(T_Eseq(T_Move(unEx(lval), unEx(lo)),
		T_Eseq(T_Jump(T_Name(testl), Temp_LabelList(testl, NULL)),
			T_Eseq(T_Label(bodyl),
				T_Eseq(unNx(body),
					T_Eseq(T_Move(unEx(lval), unEx(Tr_arithExp(A_plusOp, lval, Tr_Ex(T_Const(1))))),		// i:= i + 1
						T_Eseq(T_Label(testl),
							T_Eseq(T_Cjump(T_le, unEx(lval), unEx(hi), bodyl, unEx(done)->u.NAME),	// i<=hi
								T_Eseq(T_Label(unEx(done)->u.NAME), T_Const(0))))))))));
}

Tr_exp Tr_breakExp(Tr_exp b) { return Tr_Nx(T_Jump(T_Name(unEx(b)->u.NAME), Temp_LabelList(unEx(b)->u.NAME, NULL))); }

Tr_exp Tr_arithExp(A_oper op, Tr_exp left, Tr_exp right) { /* (+, -, *, /) */
	T_binOp opp;
	switch(op) {
	case A_plusOp  : opp = T_plus; break;
	case A_minusOp : opp = T_minus; break;
	case A_timesOp : opp = T_mul; break;
	case A_divideOp: opp = T_div; break;
	case A_andOp: opp = T_and; break;
	case A_orOp: opp = T_or; break;
	default: assert(0);
	}
	return Tr_Ex(T_Binop(opp, unEx(left), unEx(right)));
}

Tr_exp Tr_eqExp(A_oper op, Tr_exp left, Tr_exp right) {
	/* num is equal */
    T_relOp opp;
	if (op == A_eqOp) opp = T_eq; else opp = T_ne;
	T_stm cond = T_Cjump(opp, unEx(left), unEx(right), NULL, NULL);
	patchList trues = PatchList(&cond->u.CJUMP.true, NULL);
	patchList falses = PatchList(&cond->u.CJUMP.false, NULL);
	return Tr_Cx(trues, falses, cond);
}

Tr_exp Tr_eqStringExp(A_oper op, Tr_exp left, Tr_exp right) {
	/* string-content is equal */
	T_exp resl = F_externalCall(String("stringEqual"), T_ExpList(unEx(left), T_ExpList(unEx(right), NULL)));
	if (op == A_eqOp) return Tr_Ex(resl);
	else if (op == A_neqOp){
		T_exp e = (resl->kind == T_CONST && resl->u.CONST != 0) ? T_Const(0): T_Const(1);
		return Tr_Ex(e);
	} else {
		if (op == A_ltOp) return (resl->u.CONST < 0) ? Tr_Ex(T_Const(0)) : Tr_Ex(T_Const(1));
		else return (resl->u.CONST > 0) ? Tr_Ex(T_Const(0)) : Tr_Ex(T_Const(1));
	}
}

Tr_exp Tr_eqRef(A_oper op, Tr_exp left, Tr_exp right) {
	/* how to compare two addr?
	 * point-addr is equal 
	 */
	T_relOp opp;
	if (op == A_eqOp) opp = T_eq; else opp = T_ne;
	T_stm cond = T_Cjump(opp, unEx(left), unEx(right), NULL, NULL);
	patchList trues = PatchList(&cond->u.CJUMP.true, NULL);
	patchList falses = PatchList(&cond->u.CJUMP.false, NULL);
	return Tr_Cx(trues, falses, cond);
}

Tr_exp Tr_relExp(A_oper op, Tr_exp left, Tr_exp right) {
	T_relOp oper;
	switch(op) {
		case A_ltOp: oper = T_lt; break;
		case A_leOp: oper = T_le; break;
		case A_gtOp: oper = T_gt; break;
		case A_geOp: oper = T_ge; break;
		default: assert(0); /* should never happen*/
	}
	T_stm cond = T_Cjump(oper, unEx(left), unEx(right), NULL, NULL);
	patchList trues = PatchList(&cond->u.CJUMP.true, NULL);
	patchList falses = PatchList(&cond->u.CJUMP.false, NULL);
	return Tr_Cx(trues, falses, cond);
}

Tr_exp Tr_ifExp(Tr_exp test, Tr_exp then, Tr_exp elsee) {
	/* init */
	Tr_exp result = NULL;
	Temp_label t = Temp_newlabel(), f = Temp_newlabel(), join = Temp_newlabel();
	struct Cx cond = unCx(test);
	doPatch(cond.trues, t);
	doPatch(cond.falses, f);
    /* use your pen draw the data graph you will understand */	
	if (!elsee) {/* there is no-else sentence */
		if (then->kind == Tr_nx) {
			result = Tr_Nx(T_Seq(cond.stm, 
						         T_Seq(T_Label(t),
					                   T_Seq(then->u.nx, T_Label(f))))); 
		} else if (then->kind == Tr_cx) {
			result = Tr_Nx(T_Seq(cond.stm,
					             T_Seq(T_Label(t),
					                   T_Seq(then->u.cx.stm, T_Label(f))))); 
		} else { /*ex*/
			result = Tr_Nx(T_Seq(cond.stm, 
					             T_Seq(T_Label(t),
					                   T_Seq(T_Exp(unEx(then)), T_Label(f)))));
		}
	} else {
		Temp_temp r = Temp_newtemp();
		T_stm joinJump = T_Jump(T_Name(join), Temp_LabelList(join, NULL));
		T_stm thenStm;
		if (then->kind == Tr_ex) thenStm = T_Exp(then->u.ex);
		else thenStm = (then->kind == Tr_nx) ? then->u.nx : then->u.cx.stm;
		T_stm elseeStm;
		if (elsee->kind == Tr_ex) elseeStm = T_Exp(elsee->u.ex);
		else elseeStm = (elsee->kind == Tr_nx) ? elsee->u.nx : elsee->u.cx.stm;
		result = Tr_Nx(T_Seq(cond.stm, 
					         T_Seq(T_Label(t), 
								   T_Seq(thenStm,
									     T_Seq(joinJump, 
											   T_Seq(T_Label(f),
							                         T_Seq(elseeStm, 
													       T_Seq(joinJump, T_Label(join))))))))); 
	}
	return result;
}

static Tr_exp Tr_StaticLink(Tr_level now, Tr_level def) {
	/* get call-function's static-link */
	T_exp addr = T_Temp(F_FP());/* frame-point */
	while(now && (now != def->parent)) { /* until find the level which def the function */
		F_access sl = F_formals(now->frame)->head;
		addr = F_Exp(sl, addr);
		now = now->parent;
	}
	return Tr_Ex(addr);
}

static T_expList Tr_expList_convert(Tr_expList l) {
	/*trans Tr_expList to T_expList*/
	T_expList h = NULL, t = NULL;
	for (; l; l = l->tail) {
		T_exp tmp = unEx(l->head);
		if (h) {
			t->tail =  T_ExpList(tmp, NULL);
			t = t->tail;
		} else {
			h = T_ExpList(tmp, NULL);
			t = h;
		}	
	}
	return h;
}

Tr_exp Tr_callExp(Temp_label label, Tr_level fun, Tr_level call, Tr_expList * l) {
	T_expList args = NULL;
	args = Tr_expList_convert(*l);
	return Tr_Ex(T_Call(T_Name(label), args));
}

static patchList PatchList(Temp_label * h, patchList t) {
	patchList p = checked_malloc(sizeof(*p));
	p->head = h;
	p->tail = t;
	return p;
}

static void doPatch(patchList t, Temp_label label) {
	/*for the list every item value the same label*/
	for (; t; t = t->tail) {
		*(t->head) = label;
	}
}

static patchList joinPatch(patchList fir, patchList scd) {
	/*add patch-List in the tail*/
	if (!fir) return scd;
	for (; fir->tail; fir = fir->tail);
	fir->tail = scd;
	return fir;
}

F_fragList Tr_StringFrag()
{
	return stringFragList;
}

F_fragList Tr_levelFrag(int level) {/*link stringFragList -> fragList */
	return fragList[level];
}

/*******STACK-FRAME*******/
Tr_level Tr_newLevel(Tr_level p, Temp_label n, U_boolList f) {
	Tr_level l = checked_malloc(sizeof(*l));
	l->parent = p;
	l->name = n;
	l->frame = F_newFrame(n, U_BoolList(TRUE, f));
	l->formals = makeFormalAccessList(l);
	/*display_l(l);*/
	return l;
}

Tr_access Tr_allocLocal(Tr_level l, bool escape) {
	Tr_access a = checked_malloc(sizeof(*a));
	a->level = l;
	a->access = F_allocLocal(l->frame, escape);
	/*display_ac(a);*/
	return a;
}

Tr_accessList Tr_AccessList(Tr_access h, Tr_accessList t) {
	Tr_accessList al = checked_malloc(sizeof(*al));
	al->head = h;
	al->tail = t;
	return al;
} 

Tr_accessList Tr_formals(Tr_level l) {
	return l->formals;
}

static Tr_accessList makeFormalAccessList(Tr_level l) {
 /* get the access-list from frame (ingnore the first one) */
	Tr_accessList head = NULL, tail = NULL;
	F_accessList  acsl = F_formals(l->frame)->tail; /*ignore the first one due-to static-link*/
	for (; acsl; acsl = acsl->tail) {
		Tr_access ac = Tr_Access(l, acsl->head);
		if (head) {
			tail->tail = Tr_AccessList(ac, NULL);
			tail = tail->tail;
		} else {
			head = Tr_AccessList(ac, NULL);
			tail = head;
		}
	}
	return head;
}

static Tr_level outer = NULL;
Tr_level Tr_outermost(void) {
	/* the outest level, like global-env */
	if (!outer) outer = Tr_newLevel(NULL, Temp_newlabel(), NULL);
	return outer;
}

static Tr_access Tr_Access(Tr_level l, F_access a) {
	Tr_access T_a = checked_malloc(sizeof(*T_a));
	T_a->level  = l;
	T_a->access = a;
	return T_a;
}

//@@@
void test_Tr_expList_prepend(Tr_expList l) {
	while (l) {
		printf("Tr_exp->type: %d\n", l->head->kind);
		l = l->tail;
	}
}
//@@@
void test_T_expList(T_expList l) {
	while (l) {
		printf("T_exp->type: %d\n", l->head->kind);
		l = l->tail;
	}
}

static void display_l(Tr_level l) {
	static int lnum;
	if (l->parent) {
		printf("parent: %s\n", Temp_labelstring(l->parent->name));
	}
	else {
		printf("parent: root\n");
	}
	printf("addr: %s\n", Temp_labelstring(l->name));
	display_f(l->frame);
}

static void display_ac(Tr_access ac) {
	printf("level: %s\n", Temp_labelstring(ac->level->name));
	dis_ac(ac->access);
}

T_exp public_unEx(Tr_exp e) {
	return unEx(e);
}
T_stm public_unNx(Tr_exp e) {
	return unNx(e);
}
//@@@ print Tr_exp
void print(Tr_exp et, FILE * out) {
	if (et->kind == Tr_ex) printExp(unEx(et), out);
	if (et->kind == Tr_nx) printStm(unNx(et), out);
	if (et->kind == Tr_cx) printStm(unCx(et).stm, out);
}
void toASM(Tr_exp et)
{
	if (et->kind == Tr_ex) asmExp(unEx(et));
	if (et->kind == Tr_nx) asmStm(unNx(et));
	if (et->kind == Tr_cx) asmStm(unCx(et).stm);
}
extern int curLevel;
void getMASM(F_fragList fl, int level)
{
	if (!fl) {
		puts("fragList is NULL");
		return;
	}
	//int flag = 0;
	curLevel = level;
	if (fl->head->kind == F_decFrag)
	{
		char buf[100];
		itoa((curLevel+1)*4, buf, 10);
		strcat(asmBuf, "push ebp\nmov ebp, esp\nsub esp, 0xFF\n");
		strcat(asmBuf, "mov LevelFrame[");
		strcat(asmBuf, buf);
		strcat(asmBuf, "], ebp\n");
	}
	while (fl) {
		F_frag f = fl->head;
		switch (f->kind) {
		case F_decFrag:
		{
			toASM(Tr_Nx(f->u.proc.body));
			break;
		}		
		case F_procFrag:
		{
			char buf[100], sbuf[100];
			itoa((curLevel + 1) * 4, sbuf, 10);
			strcpy(buf, S_name(f->u.proc.name));
			strcat(asmBuf, buf);
			strcat(asmBuf, ":\n"); 
			strcat(asmBuf, "push ebp\nmov ebp, esp\n");
			strcat(asmBuf, "sub esp, 0xFF\n");
			if (strcmp(buf, S_name(main_label))!=0)
			{
				strcat(asmBuf, "mov LevelFrame[");
				strcat(asmBuf, sbuf);
				strcat(asmBuf, "], ebp\n");
			}
			toASM(Tr_Nx(f->u.proc.body));
			strcat(asmBuf, "push ebp\npop esp\n");
			if (strcmp(buf, S_name(main_label)) == 0)
				strcat(asmBuf, "pop ebp\njmp end\n");
			else
				strcat(asmBuf, "pop ebp\nret\n");
			break;
		}			
		}
		fl = fl->tail;
	}
	//if(flag)
		//(asmBuf, "jmp initer\n");
}
void print_frag(F_fragList fl, FILE * out) {
	if (!fl) {
		puts("fragList is NULL");
		return;
	}
	while (fl) {
		F_frag f = fl->head;
		switch (f->kind) {
		case F_stringFrag:
		{
			char buf[2048] = {"char "};
			char stringhex[5];
			strcat(buf, S_name(f->u.stringg.label));
			strcat(buf, "[]=\"");
			int len = strlen(f->u.stringg.str);
			for (int i = 0; i < len; i++)
			{
				char p = f->u.stringg.str[i];
				itoa(p, stringhex, 16);
				strcat(buf, "\\x");
				strcat(buf, stringhex);
			}
			strcat(buf, "\";\n");
			fputs(buf, out);
			break;
		}		
		case F_procFrag:
		{
			char buf[100];
			strcpy(buf, S_name(f->u.proc.name));
			fputs(buf, out);
			fputs("\n", out);
			print(Tr_Nx(f->u.proc.body), out);
			fputs("\n", out);
			break;
		}
		case F_decFrag:
			print(Tr_Nx(f->u.proc.body), out);
			fputs("\n", out);
			break;
		default: assert(0 && "frag-kind is error");
		}
		fl = fl->tail;
	}
}

