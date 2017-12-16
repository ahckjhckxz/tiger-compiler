#ifndef TIGER_PRINTTREE_H_
#define TIGER_PRINTTREE_H_

/* function prototype from printtree.c */
void printStmList(FILE * out, T_stmList stmList);
void printExp(T_exp, FILE * out);
void printStm(T_stm, FILE * out);
void assignRegFrom(int reg);
void assignRegTo(int reg);
void leaRegTo(int reg);
static void asm_stm(T_stm stm, int d);
static void asm_tree_exp(T_exp exp, int d, int reg);
#endif /* TIGER_PRINTTREE_H_ */


