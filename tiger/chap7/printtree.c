/*
 * printtree.c - functions to print out intermediate representation (IR) trees.
 *
 */
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "symbol.h"
#include "temp.h"
#include "tree.h"
#include "printtree.h"
char asmBuf[0xFFFFFFF];
int curLevel;
static int argNum = 0;
typedef struct Block_ Block;
struct Block_{
	char Label[100];
	char *asmcode;
};
typedef struct ASM_exp_ *ASM_exp;
struct ASM_exp_ {
	enum {
		eax,
		ebx,
		ecx,
		edx,
		ebp,
		esi,
		edi,
		esp
	}reg;
};
static char bin_oper[][12] = {
	"PLUS", "MINUS", "TIMES", "DIVIDE",
	"AND", "OR", "LSHIFT", "RSHIFT", "ARSHIFT", "XOR" };
static char rel_oper[][12] = {
	"EQ", "NE", "LT", "GT", "LE", "GE", "ULT", "ULE", "UGT", "UGE" };
typedef struct BlockList_* BlockList;
struct BlockList_ { Block head; BlockList tail; };
/* local function prototype */
static void pr_tree_exp(FILE *out, T_exp exp, int d);
static void asm_tree_exp(T_exp exp, int d, int reg);
static void asm_stm(T_stm stm, int d);

ASM_exp asm_exp(int reg)
{
	ASM_exp p = checked_malloc(sizeof(*p));
	p->reg = reg;
	return p;
}
static void indent(FILE *out, int d) {
 int i;
 for (i = 0; i <= d; i++) fprintf(out, " ");
}
static void pr_stm(FILE *out, T_stm stm, int d)
{
  switch (stm->kind) {
  case T_SEQ:
    indent(out,d);
    fprintf(out, "SEQ(\n"); pr_stm(out, stm->u.SEQ.left,d+1);  fprintf(out, ",\n"); 
    pr_stm(out, stm->u.SEQ.right,d+1); fprintf(out, ")");
    break;
  case T_LABEL:
    indent(out,d); fprintf(out, "LABEL %s", S_name(stm->u.LABEL));
    break;
  case T_JUMP:
    indent(out,d); fprintf(out, "JUMP(\n"); 
	pr_tree_exp(out, stm->u.JUMP.exp,d+1); 
    fprintf(out, ")");
    break;
  case T_CJUMP:
    indent(out,d); fprintf(out, "CJUMP(%s,\n", rel_oper[stm->u.CJUMP.op]);
    pr_tree_exp(out, stm->u.CJUMP.left,d+1); fprintf(out, ",\n"); 
    pr_tree_exp(out, stm->u.CJUMP.right,d+1); fprintf(out, ",\n");
    indent(out,d+1); 
	if (stm->u.CJUMP.true) fprintf(out, "%s,", S_name(stm->u.CJUMP.true)); 
	else fprintf(out, "NULL,");
    if(stm->u.CJUMP.false) fprintf(out, "%s", S_name(stm->u.CJUMP.false)); 
	else fprintf(out, "NULL,");
	fprintf(out, ")");
    break;
  case T_MOVE:
    indent(out,d); fprintf(out, "MOVE(\n"); 
	pr_tree_exp(out, stm->u.MOVE.dst,d+1); 
    fprintf(out, ",\n");
    pr_tree_exp(out, stm->u.MOVE.src,d+1); fprintf(out, ")");
    break;
  case T_EXP:
    indent(out,d); fprintf(out, "EXP(\n"); 
	pr_tree_exp(out, stm->u.EXP,d+1); 
    fprintf(out, ")");
    break;
  }
}

static void pr_tree_exp(FILE *out, T_exp exp, int d)
{
  switch (exp->kind) {
  case T_BINOP:
    indent(out,d); fprintf(out, "BINOP(%s,\n", bin_oper[exp->u.BINOP.op]); 
    pr_tree_exp(out, exp->u.BINOP.left,d+1); fprintf(out, ",\n"); 
    pr_tree_exp(out, exp->u.BINOP.right,d+1); fprintf(out, ")");
    break;
  case T_MEM:
    indent(out,d); fprintf(out, "MEM");
    fprintf(out, "(\n"); 
	pr_tree_exp(out, exp->u.MEM,d+1); fprintf(out, ")");
    break;
  case T_TEMP:
    indent(out,d); fprintf(out, "TEMP t%s", 
			   Temp_look(Temp_name(), exp->u.TEMP));
    break;
  case T_ESEQ:
    indent(out,d); fprintf(out, "ESEQ(\n"); 
	pr_stm(out, exp->u.ESEQ.stm,d+1); 
    fprintf(out, ",\n");
    pr_tree_exp(out, exp->u.ESEQ.exp,d+1); fprintf(out, ")");
    break;
  case T_NAME:
    indent(out,d); fprintf(out, "NAME %s", S_name(exp->u.NAME));
    break;
  case T_CONST:
    indent(out,d); fprintf(out, "CONST %d", exp->u.CONST);
    break;
  case T_DOUBLE:
	  indent(out, d); fprintf(out, "DOUBLE %f", exp->u.DOUBLE);
	  break;
  case T_CALL:
    {T_expList args = exp->u.CALL.args;
     indent(out,d); fprintf(out, "CALL(\n"); 
	 pr_tree_exp(out, exp->u.CALL.fun,d+1);
     for (;args; args=args->tail) {
       fprintf(out, ",\n"); 
	   pr_tree_exp(out, args->head,d+2);
     }
     fprintf(out, ")");
     break;
   }
  } /* end of switch */
}

void printStmList (FILE *out, T_stmList stmList) 
{
  for (; stmList; stmList=stmList->tail) {
    pr_stm(out, stmList->head,0); fprintf(out, "\n");
  }
}

void printExp(T_exp e, FILE * out) {
	pr_tree_exp(out, e, 0);
}
void asmExp(T_exp e)
{
	asm_tree_exp(e, 0, 0);
}
void printStm(T_stm s, FILE * out) {
	pr_stm(out, s, 0);
}
void asmStm(T_stm s) {
	asm_stm(s, 0);
}


static void asm_tree_exp(T_exp exp, int d, int reg)
{
	switch (exp->kind) {
	case T_BINOP:
	{
		if (exp->u.BINOP.left->kind == T_TEMP)
		{
			char *buf = Temp_look(Temp_name(), exp->u.BINOP.left->u.TEMP);
			if (strcmp(buf, "100") == 0 && exp->u.BINOP.op == T_plus)
			{
				strcat(asmBuf, "mov eax, ebp\n");
			}
			else
				asm_tree_exp(exp->u.BINOP.left, d + 1, 0);
		}
		else
			asm_tree_exp(exp->u.BINOP.left, d + 1, 0);
		strcat(asmBuf, "push eax\n");
		asm_tree_exp(exp->u.BINOP.right, d + 1, 2);
		strcat(asmBuf, "pop eax\n");
		switch (exp->u.BINOP.op)
		{
		case 0:
			strcat(asmBuf, "add eax, ecx\n");
			break;
		case 1:
			strcat(asmBuf, "sub eax, ecx\n");
			break;
		case 2:
			strcat(asmBuf, "push edx\n");
			strcat(asmBuf, "imul ecx\n");
			strcat(asmBuf, "pop edx\n");
			break;
		case 3:
			strcat(asmBuf, "push edx\n");
			strcat(asmBuf, "xor edx, edx\n");
			strcat(asmBuf, "idiv ecx\n");
			strcat(asmBuf, "pop edx\n");
			break;
		case 4:
			strcat(asmBuf, "and eax, ecx\n");
			break;
		case 5:
			strcat(asmBuf, "or eax, ecx\n");
			break;
		case 6:
			strcat(asmBuf, "shl eax, ecx\n");
			break;
		case 7:
			strcat(asmBuf, "shr eax, ecx\n");
			break;
		case 8:
			strcat(asmBuf, "sar eax, ecx\n");
			break;
		case 9:
			strcat(asmBuf, "xor eax, ecx\n");
			break;
		}
		if (reg != eax)
		{
			assignRegTo(reg);
			assignRegFrom(eax);
		}
		break;
	}	
	case T_MEM:
	{
		T_exp staticlink = exp->u.MEM;
		int len = 0;
		while (staticlink->kind == T_MEM)
		{
			staticlink = staticlink->u.MEM;
			len++;
		}
		if (staticlink->kind == T_TEMP && len > 0 && strcmp(Temp_look(Temp_name(), staticlink->u.TEMP), "100")==0)
		{
			char sbuf[100];
			int tarlevel = curLevel - len;
			itoa(tarlevel * 4, sbuf, 10);
			leaRegTo(ebx);
			strcat(asmBuf, "LevelFrame[");
			strcat(asmBuf, sbuf);
			strcat(asmBuf, "]\n");
		}
		else
			asm_tree_exp(exp->u.MEM, d + 1, 1);
		assignRegTo(esi);
		strcat(asmBuf, "ebx\n");
		assignRegTo(reg);
		strcat(asmBuf, "[ebx]\n");
		break;
	}
	case T_TEMP:
	{
		char *buf = Temp_look(Temp_name(), exp->u.TEMP);
		if (strcmp(buf, "100") == 0)
		{
			char sbuf[100];
			itoa(curLevel*4, sbuf, 10);
			leaRegTo(reg);
			strcat(asmBuf, "LevelFrame[");
			strcat(asmBuf, sbuf);
			strcat(asmBuf, "]\n");
		}
		else
		{
			char abuf[100];
			int num = atoi(buf);
			num = num - 100;
			itoa(num * 4, abuf, 10);
			char sbuf[100] = "TEMP[";
			strcat(sbuf, abuf);
			strcat(sbuf, "]\n");
			assignRegTo(reg);
			strcat(asmBuf, sbuf);
			leaRegTo(edi);
			strcat(asmBuf, sbuf);
		}
		break;
	}
	case T_ESEQ:
		asm_stm(exp->u.ESEQ.stm, d + 1);
		asm_tree_exp(exp->u.ESEQ.exp, d + 1, reg);
		break;
	case T_NAME:
	{
		leaRegTo(reg);
		if(strcmp(S_name(exp->u.NAME), "L0") == 0)
			strcat(asmBuf, "printf");
		else
			strcat(asmBuf, S_name(exp->u.NAME));
		strcat(asmBuf, "\n");
		break;
	}	
	case T_CONST:
	{
		char buf[33];
		itoa(exp->u.CONST, buf, 10);
		assignRegTo(reg);
		strcat(asmBuf, buf);
		strcat(asmBuf, "\n");
		break;
	}
	case T_CALL:
	{
		T_expList args = exp->u.CALL.args;
		int n = 0;
		asm_tree_exp(exp->u.CALL.fun, d + 1, 1);
		strcat(asmBuf, "push ebx\n");
		for (; args; args = args->tail) 
		{
			char buf[100];
			char abuf[100] = "ARG[";
			asm_tree_exp(args->head, d + 2, 3);
			itoa(argNum, buf, 10);
			argNum += 4;
			strcat(abuf, buf);
			strcat(asmBuf, "mov ");
			strcat(asmBuf, abuf);
			strcat(asmBuf, "], edx\n");
			n++;
		}
		strcat(asmBuf, "pop ebx\n");
		for (int i = 0, k= argNum - 4; i < n; i++,k-=4)
		{
			char buf[100];
			char abuf[100] = "ARG[";
			itoa(k, buf, 10);
			strcat(abuf, buf);
			strcat(asmBuf, "mov ecx, ");
			strcat(asmBuf, abuf);
			strcat(asmBuf, "]\npush ecx\n");
		}		
		if (reg != eax)
		{
			strcat(asmBuf, "call ebx\n");
			assignRegTo(reg);
			strcat(asmBuf, "eax\n");
		}
		else
		{
			strcat(asmBuf, "call ebx\n");
		}
		char buf[100];
		sprintf(buf, "%d\n", n * 4);
		strcat(asmBuf, "add esp, ");
		strcat(asmBuf, buf);
		break;
	}
	} /* end of switch */
}
static void asm_stm(T_stm stm, int d)
{
	switch (stm->kind) {
	case T_SEQ:
		asm_stm(stm->u.SEQ.left, d + 1); 
		asm_stm(stm->u.SEQ.right, d + 1);
		break;
	case T_LABEL:
	{
		char buf[100];
		sprintf(buf, "%s:\n", S_name(stm->u.LABEL));
		strcat(asmBuf, buf);
		break;
	}
	case T_JUMP:
	{
		strcat(asmBuf, "push eax\n");
		asm_tree_exp(stm->u.JUMP.exp, d + 1, 0);
		strcat(asmBuf, "push eax\n");
		strcat(asmBuf, "pop eax\n");
		strcat(asmBuf, "pop eax\n");
		strcat(asmBuf, "jmp [esp-8]\n");
		break;
	}	
	case T_CJUMP:
	{
		char Tbuf[100], Fbuf[100];
		strcat(asmBuf, "push eax\n");
		strcat(asmBuf, "push ecx\n");
		asm_tree_exp(stm->u.CJUMP.left, d + 1, 0);
		strcat(asmBuf, "push eax\n");
		asm_tree_exp(stm->u.CJUMP.right, d + 1, 2);
		strcat(asmBuf, "pop eax\n");
		if (stm->u.CJUMP.true)
			sprintf(Tbuf, "%s\n", S_name(stm->u.CJUMP.true));		
		if (stm->u.CJUMP.false)
			sprintf(Fbuf, "%s\n", S_name(stm->u.CJUMP.false));	
		strcat(asmBuf, "cmp eax, ecx\n");
		strcat(asmBuf, "pop ecx\n");
		strcat(asmBuf, "pop eax\n");
		switch (stm->u.CJUMP.op)
		{
		case 0:
			strcat(asmBuf, "je ");
			break;
		case 1:
			strcat(asmBuf, "jne ");
			break;
		case 2:
			strcat(asmBuf, "jl ");
			break;
		case 3:
			strcat(asmBuf, "jg ");
			break;
		case 4:
			strcat(asmBuf, "jle ");
			break;
		case 5:
			strcat(asmBuf, "jge ");
			break;
		case 6:
			strcat(asmBuf, "jb ");
			break;
		case 7:
			strcat(asmBuf, "jbe ");
			break;
		case 8:
			strcat(asmBuf, "ja ");
			break;
		case 9:
			strcat(asmBuf, "jae ");
			break;
		}
		strcat(asmBuf, Tbuf);
		strcat(asmBuf, "jmp ");
		strcat(asmBuf, Fbuf);
		break;
	}
	case T_MOVE:
	{
		strcat(asmBuf, "push eax\n");
		strcat(asmBuf, "push ebx\n");
		asm_tree_exp(stm->u.MOVE.dst, d + 1, 1);
		strcat(asmBuf, "push ebx\n");
		if (stm->u.MOVE.dst->kind == T_MEM)
			strcat(asmBuf, "push esi\n");
		if (stm->u.MOVE.dst->kind == T_TEMP)
			strcat(asmBuf, "push edi\n");
		asm_tree_exp(stm->u.MOVE.src, d + 1, 0);
		if (stm->u.MOVE.dst->kind == T_TEMP)
			strcat(asmBuf, "pop edi\n");
		if (stm->u.MOVE.dst->kind == T_MEM)
			strcat(asmBuf, "pop esi\n");
		strcat(asmBuf, "pop ebx\n");
		if (stm->u.MOVE.dst->kind  == T_MEM)
			strcat(asmBuf, "mov [esi], eax\n");
		else if(stm->u.MOVE.dst->kind == T_TEMP)
			strcat(asmBuf, "mov [edi], eax\n");
		else
			strcat(asmBuf, "mov ebx, eax\n");

		strcat(asmBuf, "pop ebx\n");
		strcat(asmBuf, "pop eax\n");
		break;
	}		
	case T_EXP:
		strcat(asmBuf, "push eax\n");
		asm_tree_exp(stm->u.EXP, d + 1, 0);
		strcat(asmBuf, "pop eax\n");
		break;
	}
}
void assignRegTo(int reg)
{
	switch (reg)
	{
	case eax:
		strcat(asmBuf, "mov eax, ");
		break;
	case ebx:
		strcat(asmBuf, "mov ebx, ");
		break;
	case ecx:
		strcat(asmBuf, "mov ecx, ");
		break;
	case edx:
		strcat(asmBuf, "mov edx, ");
		break;
	case esi:
		strcat(asmBuf, "mov esi, ");
		break;
	 case edi:
		strcat(asmBuf, "mov edi, ");
		break;
	case esp:
		strcat(asmBuf, "mov esp, ");
		break;
	case ebp:
		strcat(asmBuf, "mov ebp, ");
		break;
	}
}
void leaRegTo(int reg)
{
	switch (reg)
	{
	case eax:
		strcat(asmBuf, "lea eax, ");
		break;
	case ebx:
		strcat(asmBuf, "lea ebx, ");
		break;
	case ecx:
		strcat(asmBuf, "lea ecx, ");
		break;
	case edx:
		strcat(asmBuf, "lea edx, ");
		break;
	case esi:
		strcat(asmBuf, "lea esi, ");
		break;
	case edi:
		strcat(asmBuf, "lea edi, ");
		break;
	case esp:
		strcat(asmBuf, "lea esp, ");
		break;
	case ebp:
		strcat(asmBuf, "lea ebp, ");
		break;
	}
}
void assignRegFrom(int reg)
{
	switch (reg)
	{
	case eax:
		strcat(asmBuf, "eax\n");
		break;
	case ebx:
		strcat(asmBuf, "ebx\n");
		break;
	case ecx:
		strcat(asmBuf, "ecx\n");
		break;
	case edx:
		strcat(asmBuf, "edi\n");
		break;
	case esi:
		strcat(asmBuf, "esi\n");
		break;
	case edi:
		strcat(asmBuf, "edi\n");
		break;
	case esp:
		strcat(asmBuf, "esp\n");
		break;
	case ebp:
		strcat(asmBuf, "ebp\n");
		break;
	}
}