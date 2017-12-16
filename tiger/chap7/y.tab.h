typedef union {
	int pos;
	int ival;
	double dval;
	string sval;
	S_symbol sym;
	A_var var;
	A_exp exp;
	A_dec dec;
	A_decList declist;
	A_expList explist;
	A_efieldList efieldlist;
	A_ty ty;
	A_fieldList fieldlist;
	A_fundec fundec;
	A_namety namety;
	/* et cetera */
} YYSTYPE;
#define	ID	258
#define	STRING	259
#define	INT	260
#define	DOUBLE	261
#define	ASSIGN	262
#define	AND	263
#define	OR	264
#define	EQ	265
#define	NEQ	266
#define	LT	267
#define	LE	268
#define	GT	269
#define	GE	270
#define	PLUS	271
#define	MINUS	272
#define	TIMES	273
#define	DIVIDE	274
#define	UMINUS	275
#define	COMMA	276
#define	COLON	277
#define	SEMICOLON	278
#define	LPAREN	279
#define	RPAREN	280
#define	LBRACK	281
#define	RBRACK	282
#define	LBRACE	283
#define	RBRACE	284
#define	DOT	285
#define	ARRAY	286
#define	IF	287
#define	THEN	288
#define	ELSE	289
#define	WHILE	290
#define	FOR	291
#define	TO	292
#define	DO	293
#define	LET	294
#define	IN	295
#define	END	296
#define	OF	297
#define	BREAK	298
#define	NIL	299
#define	FUNCTION	300
#define	VAR	301
#define	TYPE	302


extern YYSTYPE yylval;
