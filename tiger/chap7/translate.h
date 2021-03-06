typedef struct Tr_access_ * Tr_access;
typedef struct Tr_level_ * Tr_level;

typedef struct Tr_accessList_ * Tr_accessList;
struct Tr_accessList_ {
	Tr_access head;
	Tr_accessList tail;
};

Tr_accessList Tr_AccessList(Tr_access h, Tr_accessList t);
Tr_level Tr_outermost(void);
int isOutmost(Tr_level level);
Tr_level Tr_newLevel(Tr_level parent, Temp_label name, U_boolList formals);
Tr_accessList Tr_formals(Tr_level level);
Tr_access Tr_allocLocal(Tr_level l, bool e);
/*************IR************/
typedef struct Tr_exp_ * Tr_exp;
typedef struct Tr_expList_ * Tr_expList;
typedef struct patchList_ *patchList;

Tr_exp Tr_arithExp(A_oper, Tr_exp, Tr_exp);
Tr_exp Tr_simpleVar(Tr_access, Tr_level);
Tr_exp Tr_fieldVar(Tr_exp, int);
Tr_exp Tr_subscriptVar(Tr_exp, Tr_exp);
Tr_exp Tr_stringExp(string);
Tr_exp Tr_intExp(int);
Tr_exp Tr_doubleExp(float);
Tr_exp Tr_noExp();
Tr_exp Tr_callExp(Temp_label label, Tr_level, Tr_level, Tr_expList *);
Tr_exp Tr_nilExp();
Tr_exp Tr_recordExp(int, Tr_expList);
Tr_exp Tr_arrayExp(Tr_exp, Tr_exp);
Tr_exp Tr_seqExp(Tr_expList);
Tr_exp Tr_doneExp();
Tr_exp Tr_whileExp(Tr_exp, Tr_exp, Tr_exp);
Tr_exp Tr_assignExp(Tr_exp, Tr_exp);
Tr_exp Tr_forExp(Tr_exp lval, Tr_exp lo, Tr_exp hi, Tr_exp body, Tr_exp done);
Tr_exp Tr_breakExp(Tr_exp);
Tr_exp Tr_eqExp(A_oper, Tr_exp, Tr_exp);
Tr_exp Tr_eqStringExp(A_oper, Tr_exp, Tr_exp);
Tr_exp Tr_eqRef(A_oper, Tr_exp, Tr_exp);
Tr_exp Tr_relExp(A_oper, Tr_exp, Tr_exp);
Tr_exp Tr_ifExp(Tr_exp, Tr_exp, Tr_exp);
int numLevel(Tr_level l);
void Tr_expList_prepend(Tr_exp, Tr_expList *);
Temp_label getLevelName(Tr_level level);
void Tr_procEntryExit(Tr_level, Tr_exp, Tr_accessList);
void Tr_decEntryExit(Tr_level , Tr_exp , Tr_accessList );
F_fragList Tr_levelFrag(int level);
F_fragList Tr_StringFrag();
/******DEBUD INFO******/
T_exp public_unEx(Tr_exp);
T_stm public_unNx(Tr_exp);
void print_frag(F_fragList, FILE *);
void getMASM(F_fragList fl, int level);
void toASM(Tr_exp et);