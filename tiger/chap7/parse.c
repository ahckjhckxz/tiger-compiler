/* 29.11.14 by Mkth
 * translate to Tree IR
 * input A_exp AST
 * output function Fragment
 */

#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "symbol.h"
#include "absyn.h"
#include "errormsg.h"
#include "parse.h"
#include "prabsyn.h"
#include "types.h"
#include "temp.h"
#include "tree.h"
#include "frame.h"
#include "translate.h"
#include "semant.h"

extern char asmBuf[0x7FFFFFFF];
extern A_exp absyn_root;
char Chead[] = "#include <string.h>\n#include <stdio.h>\n#include <stdlib.h>\nint stringEqual(char *s, char *t);\nint *initArray(int len, int init);\nint *initRecord(int size);\nint ARG[2048];\nint TEMP[2048];\nint LevelFrame[2048];\nint execute();\n";
char CBody[] = "int main()\n{\n\texecute();\n\tsystem(\"pause\");\n}\nint execute()\n{\n\t__asm {\n";
char CTail[] = "\t}\n__asm {\nend:\npush ebp\npop esp\npop ebp\n}\n}\nint *initArray(int len, int init)\n{\n\tint *p = (int *)malloc(4 * len);\n\tfor (int i = 0; i < len; i++)\n\t\tp[i] = init;\n\treturn p;\n}\n int *initRecord(int size)\n{\n\tint *p = (int *)malloc(size);\n\tmemset(p, 0, size);\n\treturn p;\n}\nint stringEqual(char *s, char *t)\n{\n\tif (strcmp(s, t) == 0)\n\t\treturn 1;\n\telse\n\t\treturn 0;\n}";
/* parse source file fname; 
   return abstract syntax data structure */
A_exp parse(string fname) 
{
	EM_reset(fname);
    if (yyparse() == 0) /* parsing worked */
		return absyn_root;
	else 
		printf("fuck! not pass syntax!\n");
		return NULL;
}

int main(int argc, char **argv) {
	A_exp temp = parse("8queens.tig");
	FILE * f1 = fopen("1.txt", "w");
	FILE * f2 = fopen("2.txt", "w");
	FILE * Tc = fopen("out.c", "w");
	if (temp) {
		SEM_transProg(temp);
		F_fragList str =  Tr_StringFrag();
		print_frag(str, f1);
		for (int i = 0; i < 1000; i++)
		{
			F_fragList level = Tr_levelFrag(i);
			if (level == NULL)
				break;
			getMASM(level, i);
			print_frag(level, f1);
		}
		fputs(Chead, Tc);
		print_frag(str, Tc);
		fputs(CBody, Tc);
		fputs(asmBuf, Tc);
		fputs(CTail, Tc);
	}
	fclose(f1);
	fclose(f2);
	system("pause");
	return 0;
}

F_fragList newAFragment()
{
	F_fragList fl = 0;
	return 	fl;
}
