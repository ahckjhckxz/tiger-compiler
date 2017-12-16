
/*  A Bison parser, made from .\tiger.y with Bison version GNU Bison version 1.24
*/

#define YYBISON 1  /* Identify Bison output.  */

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

#line 1 ".\tiger.y"


#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "absyn.h"
#include "errormsg.h"

int yylex(void); /* function prototype */

A_exp absyn_root;

void yyerror(char *s)
{
	EM_error(EM_tokPos, "%s", s);
}


#line 21 ".\tiger.y"
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

#ifndef YYLTYPE
typedef
struct yyltype
{
	int timestamp;
	int first_line;
	int first_column;
	int last_line;
	int last_column;
	char *text;
}
yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		145
#define	YYFLAG		-32768
#define	YYNTBASE	48

#define YYTRANSLATE(x) ((unsigned)(x) <= 302 ? yytranslate[x] : 68)

static const char yytranslate[] = { 0,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
46,    47
};

#if YYDEBUG != 0
static const short yyprhs[] = { 0,
0,     2,     4,     6,    10,    12,    14,    16,    18,    20,
26,    33,    38,    42,    46,    50,    54,    58,    61,    65,
69,    73,    77,    81,    85,    89,    91,    93,    98,   107,
109,   113,   118,   124,   128,   129,   136,   139,   140,   142,
144,   146,   149,   151,   156,   158,   162,   166,   172,   176,
177,   182,   189,   192,   194,   202,   212,   216,   218,   219,
221,   225,   230,   235,   240,   244,   246,   247
};

static const short yyrhs[] = { 49,
0,    64,     0,    65,     0,    64,     7,    49,     0,    44,
0,    50,     0,     5,     0,     6,     0,     4,     0,    39,
54,    40,    63,    41,     0,    32,    49,    33,    49,    34,
49,     0,    32,    49,    33,    49,     0,    49,    16,    49,
0,    49,    17,    49,     0,    49,    18,    49,     0,    49,
19,    49,     0,    49,    10,    49,     0,    17,    49,     0,
49,    11,    49,     0,    49,    14,    49,     0,    49,    12,
49,     0,    49,    15,    49,     0,    49,    13,    49,     0,
49,     8,    49,     0,    49,     9,    49,     0,    51,     0,
53,     0,    35,    49,    38,    49,     0,    36,    64,     7,
49,    37,    49,    38,    49,     0,    43,     0,    24,    63,
25,     0,    67,    28,    52,    29,     0,    67,    10,    49,
21,    52,     0,    67,    10,    49,     0,     0,    67,    26,
49,    27,    42,    49,     0,    55,    54,     0,     0,    56,
0,    60,     0,    61,     0,    57,    56,     0,    57,     0,
47,    67,    10,    58,     0,    67,     0,    28,    59,    29,
0,    31,    42,    67,     0,    67,    22,    67,    21,    59,
0,    67,    22,    67,     0,     0,    46,    67,     7,    49,
0,    46,    67,    22,    67,     7,    49,     0,    62,    61,
0,    62,     0,    45,    67,    24,    59,    25,    10,    49,
0,    45,    67,    24,    59,    25,    22,    67,    10,    49,
0,    49,    23,    63,     0,    49,     0,     0,    67,     0,
64,    30,    67,     0,    67,    26,    49,    27,     0,    64,
26,    49,    27,     0,    67,    24,    66,    25,     0,    49,
21,    66,     0,    49,     0,     0,     3,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
79,    81,    82,    83,    84,    85,    86,    87,    88,    89,
90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
111,   113,   115,   116,   117,   119,   122,   123,   125,   126,
127,   129,   130,   132,   134,   135,   136,   138,   139,   140,
142,   143,   145,   146,   148,   149,   151,   152,   153,   155,
156,   157,   158,   160,   162,   163,   164,   166
};

static const char * const yytname[] = { "$","error","$undefined.","ID","STRING",
"INT","DOUBLE","ASSIGN","AND","OR","EQ","NEQ","LT","LE","GT","GE","PLUS","MINUS",
"TIMES","DIVIDE","UMINUS","COMMA","COLON","SEMICOLON","LPAREN","RPAREN","LBRACK",
"RBRACK","LBRACE","RBRACE","DOT","ARRAY","IF","THEN","ELSE","WHILE","FOR","TO",
"DO","LET","IN","END","OF","BREAK","NIL","FUNCTION","VAR","TYPE","program","exp",
"seq","record","refields","array","decs","dec","tydecs","tydec","ty","typefields",
"vardec","fundecs","fundec","explist","lvalue","funcall","args","id",""
};
#endif

static const short yyr1[] = { 0,
48,    49,    49,    49,    49,    49,    49,    49,    49,    49,
49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
50,    51,    52,    52,    52,    53,    54,    54,    55,    55,
55,    56,    56,    57,    58,    58,    58,    59,    59,    59,
60,    60,    61,    61,    62,    62,    63,    63,    63,    64,
64,    64,    64,    65,    66,    66,    66,    67
};

static const short yyr2[] = { 0,
1,     1,     1,     3,     1,     1,     1,     1,     1,     5,
6,     4,     3,     3,     3,     3,     3,     2,     3,     3,
3,     3,     3,     3,     3,     1,     1,     4,     8,     1,
3,     4,     5,     3,     0,     6,     2,     0,     1,     1,
1,     2,     1,     4,     1,     3,     3,     5,     3,     0,
4,     6,     2,     1,     7,     9,     3,     1,     0,     1,
3,     4,     4,     4,     3,     1,     0,     1
};

static const short yydefact[] = { 0,
68,     9,     7,     8,     0,    59,     0,     0,     0,    38,
30,     5,     1,     6,    26,    27,     2,     3,    60,    18,
58,     0,     0,     0,     0,    60,     0,     0,     0,     0,
38,    39,    43,    40,    41,    54,     0,     0,     0,     0,
0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
0,    67,     0,    35,    59,    31,     0,     0,     0,     0,
0,     0,     0,    59,    37,    42,    53,    24,    25,    17,
19,    21,    23,    20,    22,    13,    14,    15,    16,     4,
0,    61,    66,     0,     0,     0,     0,    57,    12,    28,
0,     0,    50,     0,     0,     0,     0,    63,    67,    64,
62,    32,     0,     0,     0,    62,     0,     0,    51,     0,
50,     0,    44,    45,    10,    65,     0,    34,    11,     0,
0,     0,     0,     0,     0,    36,    35,     0,     0,     0,
49,    52,    46,    47,    33,    29,    55,     0,    50,     0,
48,    56,     0,     0,     0
};

static const short yydefgoto[] = { 143,
21,    14,    15,    86,    16,    30,    31,    32,    33,   113,
107,    34,    35,    36,    22,    17,    18,    84,    19
};

static const short yypact[] = { 83,
-32768,-32768,-32768,-32768,    83,    83,    83,    83,     1,   -28,
-32768,-32768,   316,-32768,-32768,-32768,    84,-32768,   -15,-32768,
272,   -19,   186,    16,    90,   -16,     1,     1,     1,   -25,
-28,-32768,   -24,-32768,-32768,   -23,    83,    83,    83,    83,
83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
1,    83,    83,     1,    83,-32768,    83,    83,    83,    83,
31,    -6,    52,    83,-32768,-32768,-32768,   144,   144,   199,
199,   199,   199,   199,   199,     2,     2,-32768,-32768,   316,
212,-32768,   288,    38,   232,    36,    56,-32768,   174,   316,
133,   252,     1,    83,     1,    33,    26,-32768,    83,-32768,
43,-32768,    83,    83,    83,-32768,    65,    46,   316,    85,
1,    53,-32768,-32768,-32768,-32768,    83,   302,   316,    64,
-8,     1,    83,    69,     1,   316,     1,    83,    83,     1,
80,   316,-32768,-32768,-32768,   316,   316,    96,     1,    83,
-32768,   316,   108,   109,-32768
};

static const short yypgoto[] = { -32768,
0,-32768,-32768,   -14,-32768,    81,-32768,    78,-32768,-32768,
-55,-32768,    88,-32768,   -52,   112,-32768,    32,    42
};


#define	YYLAST		335


static const short yytable[] = { 13,
94,   129,    88,     1,    20,    56,    23,    24,    52,    60,
53,    97,    54,   130,    64,    95,    27,    28,    29,    47,
48,    27,    29,    37,    38,    39,    40,    41,    42,    43,
44,    45,    46,    47,    48,     1,    68,    69,    70,    71,
72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
26,    83,    85,    58,    93,   124,    89,    90,    91,    92,
111,    96,   100,   112,   102,   103,   115,   122,    61,    62,
63,    37,    38,    39,    40,    41,    42,    43,    44,    45,
46,    47,    48,   141,   117,     1,     2,     3,     4,   121,
49,   123,    82,   109,   125,    87,    59,   133,    83,     5,
139,   128,   118,   119,   120,   140,     6,   144,   145,    50,
66,    65,   135,    51,     7,    50,   126,     8,     9,    51,
25,    10,   132,    67,     0,    11,    12,   136,   137,     0,
116,     0,     0,     0,   108,     0,   110,   114,     0,   142,
37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
47,    48,   108,    39,    40,    41,    42,    43,    44,    45,
46,    47,    48,   131,     0,     0,   134,     0,    87,   105,
0,   138,     0,     0,     0,     0,     0,     0,     0,     0,
108,    37,    38,    39,    40,    41,    42,    43,    44,    45,
46,    47,    48,    37,    38,    39,    40,    41,    42,    43,
44,    45,    46,    47,    48,     0,     0,   104,-32768,-32768,
-32768,-32768,-32768,-32768,    45,    46,    47,    48,    57,    37,
38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
48,     0,     0,     0,     0,     0,     0,     0,    98,    37,
38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
48,     0,     0,     0,     0,     0,     0,     0,   101,    37,
38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
48,     0,     0,     0,     0,     0,     0,     0,   106,    37,
38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
48,     0,     0,     0,    55,    37,    38,    39,    40,    41,
42,    43,    44,    45,    46,    47,    48,     0,    99,    37,
38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
48,     0,   127,    37,    38,    39,    40,    41,    42,    43,
44,    45,    46,    47,    48
};

static const short yycheck[] = { 0,
7,    10,    55,     3,     5,    25,     7,     8,    24,    26,
26,    64,    28,    22,    40,    22,    45,    46,    47,    18,
19,    45,    47,     8,     9,    10,    11,    12,    13,    14,
15,    16,    17,    18,    19,     3,    37,    38,    39,    40,
41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
9,    52,    53,    38,    24,   111,    57,    58,    59,    60,
28,    10,    25,    31,    29,    10,    41,    22,    27,    28,
29,     8,     9,    10,    11,    12,    13,    14,    15,    16,
17,    18,    19,   139,    42,     3,     4,     5,     6,    25,
7,     7,    51,    94,    42,    54,     7,    29,    99,    17,
21,    38,   103,   104,   105,    10,    24,     0,     0,    26,
33,    31,   127,    30,    32,    26,   117,    35,    36,    30,
9,    39,   123,    36,    -1,    43,    44,   128,   129,    -1,
99,    -1,    -1,    -1,    93,    -1,    95,    96,    -1,   140,
8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
18,    19,   111,    10,    11,    12,    13,    14,    15,    16,
17,    18,    19,   122,    -1,    -1,   125,    -1,   127,    37,
-1,   130,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
139,     8,     9,    10,    11,    12,    13,    14,    15,    16,
17,    18,    19,     8,     9,    10,    11,    12,    13,    14,
15,    16,    17,    18,    19,    -1,    -1,    34,    10,    11,
12,    13,    14,    15,    16,    17,    18,    19,    33,     8,
9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,     8,
9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,     8,
9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,     8,
9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
19,    -1,    -1,    -1,    23,     8,     9,    10,    11,    12,
13,    14,    15,    16,    17,    18,    19,    -1,    21,     8,
9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
19,    -1,    21,     8,     9,    10,    11,    12,    13,    14,
15,    16,    17,    18,    19
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
Bison output file, you may use that output file without restriction.
This special exception was added by the Free Software Foundation
in version 1.24 of Bison.  */
#include <malloc.h>      /*  add by lyh */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
#pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
	void *alloca(unsigned int);
};
#else /* not __cplusplus */
void *alloca();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
when the %semantic_parser declaration is not specified in the grammar.
It was written by Richard Stallman by simplifying the hairy parser
used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
It is replaced by the list of actions, each action
as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
This remains here temporarily to ease the
transition to the new meaning of YYERROR, for GCC.
Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
						/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
						/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
						/* Since this is uninitialized, it does not stop multiple parsers
						from coexisting.  */
#endif

						/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

						/*  YYMAXDEPTH is the maximum size the stacks can grow to
						(effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

						/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse(void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
in available built-in functions on various systems.  */
static void
__yy_memcpy(from, to, count)
char *from;
char *to;
int count;
{
	register char *f = from;
	register char *t = to;
	register int i = count;

	while (i-- > 0)
		*t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
in available built-in functions on various systems.  */
static void
__yy_memcpy(char *from, char *to, int count)
{
	register char *f = from;
	register char *t = to;
	register int i = count;

	while (i-- > 0)
		*t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
into yyparse.  The argument should have type void *.
It should actually point to an object.
Grammar actions can access the variable by casting it
to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
YYPARSE_PARAM_DECL
{
	register int yystate;
	register int yyn;
	register short *yyssp;
	register YYSTYPE *yyvsp;
	int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
	int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

	short	yyssa[YYINITDEPTH];	/*  the state stack			*/
	YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

	short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
	YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
	YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
	YYLTYPE *yyls = yylsa;
	YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

	int yystacksize = YYINITDEPTH;

#ifdef YYPURE
	int yychar;
	YYSTYPE yylval;
	int yynerrs;
#ifdef YYLSP_NEEDED
	YYLTYPE yylloc;
#endif
#endif

	YYSTYPE yyval;		/*  the variable used to return		*/
						/*  semantic values from the action	*/
						/*  routines				*/

	int yylen;

#if YYDEBUG != 0
	if (yydebug)
		fprintf(stderr, "Starting parse\n");
#endif

	yystate = 0;
	yyerrstatus = 0;
	yynerrs = 0;
	yychar = YYEMPTY;		/* Cause a token to be read.  */

							/* Initialize stack pointers.
							Waste one element of value and location stack
							so that they stay on the same level as the state stack.
							The wasted elements are never initialized.  */

	yyssp = yyss - 1;
	yyvsp = yyvs;
#ifdef YYLSP_NEEDED
	yylsp = yyls;
#endif

	/* Push a new state, which is found in  yystate  .  */
	/* In all cases, when you get here, the value and location stacks
	have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

	*++yyssp = yystate;

	if (yyssp >= yyss + yystacksize - 1)
	{
		/* Give user a chance to reallocate the stack */
		/* Use copies of these so that the &'s don't force the real ones into memory. */
		YYSTYPE *yyvs1 = yyvs;
		short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
		YYLTYPE *yyls1 = yyls;
#endif

		/* Get the current used size of the three stacks, in elements.  */
		int size = yyssp - yyss + 1;

#ifdef yyoverflow
		/* Each stack pointer address is followed by the size of
		the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
		/* This used to be a conditional around just the two extra args,
		but that might be undefined if yyoverflow is a macro.  */
		yyoverflow("parser stack overflow",
			&yyss1, size * sizeof(*yyssp),
			&yyvs1, size * sizeof(*yyvsp),
			&yyls1, size * sizeof(*yylsp),
			&yystacksize);
#else
		yyoverflow("parser stack overflow",
			&yyss1, size * sizeof(*yyssp),
			&yyvs1, size * sizeof(*yyvsp),
			&yystacksize);
#endif

		yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
		yyls = yyls1;
#endif
#else /* no yyoverflow */
		/* Extend the stack our own way.  */
		if (yystacksize >= YYMAXDEPTH)
		{
			yyerror("parser stack overflow");
			return 2;
		}
		yystacksize *= 2;
		if (yystacksize > YYMAXDEPTH)
			yystacksize = YYMAXDEPTH;
		yyss = (short *)malloc(yystacksize * sizeof(*yyssp));
		__yy_memcpy((char *)yyss1, (char *)yyss, size * sizeof(*yyssp));
		yyvs = (YYSTYPE *)malloc(yystacksize * sizeof(*yyvsp));
		__yy_memcpy((char *)yyvs1, (char *)yyvs, size * sizeof(*yyvsp));
#ifdef YYLSP_NEEDED
		yyls = (YYLTYPE *)malloc(yystacksize * sizeof(*yylsp));
		__yy_memcpy((char *)yyls1, (char *)yyls, size * sizeof(*yylsp));
#endif
#endif /* no yyoverflow */

		yyssp = yyss + size - 1;
		yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
		yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
		if (yydebug)
			fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

		if (yyssp >= yyss + yystacksize - 1)
			YYABORT;
	}

#if YYDEBUG != 0
	if (yydebug)
		fprintf(stderr, "Entering state %d\n", yystate);
#endif

	goto yybackup;
yybackup:

	/* Do appropriate processing given the current state.  */
	/* Read a lookahead token if we need one and don't already have one.  */
	/* yyresume: */

	/* First try to decide what to do without reference to lookahead token.  */

	yyn = yypact[yystate];
	if (yyn == YYFLAG)
		goto yydefault;

	/* Not known => get a lookahead token if don't already have one.  */

	/* yychar is either YYEMPTY or YYEOF
	or a valid token in external form.  */

	if (yychar == YYEMPTY)
	{
#if YYDEBUG != 0
		if (yydebug)
			fprintf(stderr, "Reading a token: ");
#endif
		yychar = YYLEX;
	}

	/* Convert token to internal form (in yychar1) for indexing tables with */

	if (yychar <= 0)		/* This means end of input. */
	{
		yychar1 = 0;
		yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
		if (yydebug)
			fprintf(stderr, "Now at end of input.\n");
#endif
	}
	else
	{
		yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
		if (yydebug)
		{
			fprintf(stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
			/* Give the individual parser a way to print the precise meaning
			of a token, for further debugging info.  */
#ifdef YYPRINT
			YYPRINT(stderr, yychar, yylval);
#endif
			fprintf(stderr, ")\n");
		}
#endif
	}

	yyn += yychar1;
	if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
		goto yydefault;

	yyn = yytable[yyn];

	/* yyn is what to do for this token type in this state.
	Negative => reduce, -yyn is rule number.
	Positive => shift, yyn is new state.
	New state is final state => don't bother to shift,
	just return success.
	0, or most negative number => error.  */

	if (yyn < 0)
	{
		if (yyn == YYFLAG)
			goto yyerrlab;
		yyn = -yyn;
		goto yyreduce;
	}
	else if (yyn == 0)
		goto yyerrlab;

	if (yyn == YYFINAL)
		YYACCEPT;

	/* Shift the lookahead token.  */

#if YYDEBUG != 0
	if (yydebug)
		fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

	/* Discard the token being shifted unless it is eof.  */
	if (yychar != YYEOF)
		yychar = YYEMPTY;

	*++yyvsp = yylval;
#ifdef YYLSP_NEEDED
	*++yylsp = yylloc;
#endif

	/* count tokens shifted since error; after three, turn off error status.  */
	if (yyerrstatus) yyerrstatus--;

	yystate = yyn;
	goto yynewstate;

	/* Do the default action for the current state.  */
yydefault:

	yyn = yydefact[yystate];
	if (yyn == 0)
		goto yyerrlab;

	/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
	yylen = yyr2[yyn];
	if (yylen > 0)
		yyval = yyvsp[1 - yylen]; /* implement default value of the action */

#if YYDEBUG != 0
	if (yydebug)
	{
		int i;

		fprintf(stderr, "Reducing via rule %d (line %d), ",
			yyn, yyrline[yyn]);

		/* Print the symbols being reduced, and their result.  */
		for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
			fprintf(stderr, "%s ", yytname[yyrhs[i]]);
		fprintf(stderr, " -> %s\n", yytname[yyr1[yyn]]);
	}
#endif


	switch (yyn) {

	case 1:
#line 79 ".\tiger.y"
	{absyn_root = yyvsp[0].exp;;
	break; }
	case 2:
#line 81 ".\tiger.y"
	{yyval.exp = A_VarExp(EM_tokPos, yyvsp[0].var);;
	break; }
	case 3:
#line 82 ".\tiger.y"
	{yyval.exp = yyvsp[0].exp;;
	break; }
	case 4:
#line 83 ".\tiger.y"
	{yyval.exp = A_AssignExp(EM_tokPos, yyvsp[-2].var, yyvsp[0].exp);;
	break; }
	case 5:
#line 84 ".\tiger.y"
	{yyval.exp = A_NilExp(EM_tokPos);;
	break; }
	case 6:
#line 85 ".\tiger.y"
	{yyval.exp = yyvsp[0].exp;;
	break; }
	case 7:
#line 86 ".\tiger.y"
	{yyval.exp = A_IntExp(EM_tokPos, yyvsp[0].ival);;
	break; }
	case 8:
#line 87 ".\tiger.y"
	{yyval.exp = A_DoubleExp(EM_tokPos, yyvsp[0].dval);;
	break; }
	case 9:
#line 88 ".\tiger.y"
	{yyval.exp = A_StringExp(EM_tokPos, yyvsp[0].sval);;
	break; }
	case 10:
#line 89 ".\tiger.y"
	{yyval.exp = A_LetExp(EM_tokPos, yyvsp[-3].declist, A_SeqExp(EM_tokPos, yyvsp[-1].explist));;
	break; }
	case 11:
#line 90 ".\tiger.y"
	{yyval.exp = A_IfExp(EM_tokPos, yyvsp[-4].exp, yyvsp[-2].exp, yyvsp[0].exp);;
	break; }
	case 12:
#line 91 ".\tiger.y"
	{yyval.exp = A_IfExp(EM_tokPos, yyvsp[-2].exp, yyvsp[0].exp, NULL);;
	break; }
	case 13:
#line 92 ".\tiger.y"
	{yyval.exp = A_OpExp(EM_tokPos, A_plusOp, yyvsp[-2].exp, yyvsp[0].exp);;
	break; }
	case 14:
#line 93 ".\tiger.y"
	{yyval.exp = A_OpExp(EM_tokPos, A_minusOp, yyvsp[-2].exp, yyvsp[0].exp);;
	break; }
	case 15:
#line 94 ".\tiger.y"
	{yyval.exp = A_OpExp(EM_tokPos, A_timesOp, yyvsp[-2].exp, yyvsp[0].exp);;
	break; }
	case 16:
#line 95 ".\tiger.y"
	{yyval.exp = A_OpExp(EM_tokPos, A_divideOp, yyvsp[-2].exp, yyvsp[0].exp);;
	break; }
	case 17:
#line 96 ".\tiger.y"
	{yyval.exp = A_OpExp(EM_tokPos, A_eqOp, yyvsp[-2].exp, yyvsp[0].exp);;
	break; }
	case 18:
#line 97 ".\tiger.y"
	{yyval.exp = A_OpExp(EM_tokPos, A_minusOp, A_IntExp(EM_tokPos, 0), yyvsp[0].exp);;
	break; }
	case 19:
#line 98 ".\tiger.y"
	{yyval.exp = A_OpExp(EM_tokPos, A_neqOp, yyvsp[-2].exp, yyvsp[0].exp);;
	break; }
	case 20:
#line 99 ".\tiger.y"
	{yyval.exp = A_OpExp(EM_tokPos, A_gtOp, yyvsp[-2].exp, yyvsp[0].exp);;
	break; }
	case 21:
#line 100 ".\tiger.y"
	{yyval.exp = A_OpExp(EM_tokPos, A_ltOp, yyvsp[-2].exp, yyvsp[0].exp);;
	break; }
	case 22:
#line 101 ".\tiger.y"
	{yyval.exp = A_OpExp(EM_tokPos, A_geOp, yyvsp[-2].exp, yyvsp[0].exp);;
	break; }
	case 23:
#line 102 ".\tiger.y"
	{yyval.exp = A_OpExp(EM_tokPos, A_leOp, yyvsp[-2].exp, yyvsp[0].exp);;
	break; }
	case 24:
#line 103 ".\tiger.y"
	{yyval.exp = A_OpExp(EM_tokPos, A_andOp, yyvsp[-2].exp, yyvsp[0].exp);;
	break; }
	case 25:
#line 104 ".\tiger.y"
	{yyval.exp = A_OpExp(EM_tokPos, A_orOp, yyvsp[-2].exp, yyvsp[0].exp);;
	break; }
	case 26:
#line 105 ".\tiger.y"
	{yyval.exp = yyvsp[0].exp;;
	break; }
	case 27:
#line 106 ".\tiger.y"
	{yyval.exp = yyvsp[0].exp;;
	break; }
	case 28:
#line 107 ".\tiger.y"
	{yyval.exp = A_WhileExp(EM_tokPos, yyvsp[-2].exp, yyvsp[0].exp);;
	break; }
	case 29:
#line 108 ".\tiger.y"
	{yyval.exp = A_ForExp(EM_tokPos, yyvsp[-6].var, yyvsp[-4].exp, yyvsp[-2].exp, yyvsp[0].exp);;
	break; }
	case 30:
#line 109 ".\tiger.y"
	{yyval.exp = A_BreakExp(EM_tokPos);;
	break; }
	case 31:
#line 111 ".\tiger.y"
	{yyval.exp = A_SeqExp(EM_tokPos, yyvsp[-1].explist);;
	break; }
	case 32:
#line 113 ".\tiger.y"
	{yyval.exp = A_RecordExp(EM_tokPos, yyvsp[-3].sym, yyvsp[-1].efieldlist);;
	break; }
	case 33:
#line 115 ".\tiger.y"
	{yyval.efieldlist = A_EfieldList(A_Efield(yyvsp[-4].sym, yyvsp[-2].exp), yyvsp[0].efieldlist);;
	break; }
	case 34:
#line 116 ".\tiger.y"
	{yyval.efieldlist = A_EfieldList(A_Efield(yyvsp[-2].sym, yyvsp[0].exp), NULL);;
	break; }
	case 35:
#line 117 ".\tiger.y"
	{yyval.efieldlist = NULL;;
	break; }
	case 36:
#line 119 ".\tiger.y"
	{yyval.exp = A_ArrayExp(EM_tokPos, yyvsp[-5].sym, yyvsp[-3].exp, yyvsp[0].exp);;
	break; }
	case 37:
#line 122 ".\tiger.y"
	{yyval.declist = A_DecList(yyvsp[-1].dec, yyvsp[0].declist);;
	break; }
	case 38:
#line 123 ".\tiger.y"
	{yyval.declist = NULL;;
	break; }
	case 39:
#line 125 ".\tiger.y"
	{yyval.dec = yyvsp[0].dec;;
	break; }
	case 40:
#line 126 ".\tiger.y"
	{yyval.dec = yyvsp[0].dec;;
	break; }
	case 41:
#line 127 ".\tiger.y"
	{yyval.dec = yyvsp[0].dec;;
	break; }
	case 42:
#line 129 ".\tiger.y"
	{yyval.dec = A_TypeDec(EM_tokPos, A_NametyList(yyvsp[-1].namety, yyvsp[0].dec->u.type));;
	break; }
	case 43:
#line 130 ".\tiger.y"
	{yyval.dec = A_TypeDec(EM_tokPos, A_NametyList(yyvsp[0].namety, NULL));;
	break; }
	case 44:
#line 132 ".\tiger.y"
	{yyval.namety = A_Namety(yyvsp[-2].sym, yyvsp[0].ty);;
	break; }
	case 45:
#line 134 ".\tiger.y"
	{yyval.ty = A_NameTy(EM_tokPos, yyvsp[0].sym);;
	break; }
	case 46:
#line 135 ".\tiger.y"
	{yyval.ty = A_RecordTy(EM_tokPos, yyvsp[-1].fieldlist);;
	break; }
	case 47:
#line 136 ".\tiger.y"
	{yyval.ty = A_ArrayTy(EM_tokPos, yyvsp[0].sym);;
	break; }
	case 48:
#line 138 ".\tiger.y"
	{yyval.fieldlist = A_FieldList(A_Field(EM_tokPos, yyvsp[-4].sym, yyvsp[-2].sym), yyvsp[0].fieldlist);;
	break; }
	case 49:
#line 139 ".\tiger.y"
	{yyval.fieldlist = A_FieldList(A_Field(EM_tokPos, yyvsp[-2].sym, yyvsp[0].sym), NULL);;
	break; }
	case 50:
#line 140 ".\tiger.y"
	{yyval.fieldlist = NULL;;
	break; }
	case 51:
#line 142 ".\tiger.y"
	{/*printf("\n$%s$\n", $2);*/ yyval.dec = A_VarDec(EM_tokPos, yyvsp[-2].sym, NULL, yyvsp[0].exp);;
	break; }
	case 52:
#line 143 ".\tiger.y"
	{yyval.dec = A_VarDec(EM_tokPos, yyvsp[-4].sym, yyvsp[-2].sym, yyvsp[0].exp);;
	break; }
	case 53:
#line 145 ".\tiger.y"
	{yyval.dec = A_FunctionDec(EM_tokPos, A_FundecList(yyvsp[-1].fundec, yyvsp[0].dec->u.function));;
	break; }
	case 54:
#line 146 ".\tiger.y"
	{yyval.dec = A_FunctionDec(EM_tokPos, A_FundecList(yyvsp[0].fundec, NULL));;
	break; }
	case 55:
#line 148 ".\tiger.y"
	{yyval.fundec = A_Fundec(EM_tokPos, yyvsp[-5].sym, yyvsp[-3].fieldlist, NULL, yyvsp[0].exp);;
	break; }
	case 56:
#line 149 ".\tiger.y"
	{yyval.fundec = A_Fundec(EM_tokPos, yyvsp[-7].sym, yyvsp[-5].fieldlist, yyvsp[-2].sym, yyvsp[0].exp);;
	break; }
	case 57:
#line 151 ".\tiger.y"
	{yyval.explist = A_ExpList(yyvsp[-2].exp, yyvsp[0].explist);;
	break; }
	case 58:
#line 152 ".\tiger.y"
	{yyval.explist = A_ExpList(yyvsp[0].exp, NULL);;
	break; }
	case 59:
#line 153 ".\tiger.y"
	{yyval.explist = NULL;;
	break; }
	case 60:
#line 155 ".\tiger.y"
	{/*printf("\nf$%s$f\n", S_name($1));*/ yyval.var = A_SimpleVar(EM_tokPos, yyvsp[0].sym);;
	break; }
	case 61:
#line 156 ".\tiger.y"
	{yyval.var = A_FieldVar(EM_tokPos, yyvsp[-2].var, yyvsp[0].sym);;
	break; }
	case 62:
#line 157 ".\tiger.y"
	{yyval.var = A_SubscriptVar(EM_tokPos, A_SimpleVar(EM_tokPos, yyvsp[-3].sym), yyvsp[-1].exp);;
	break; }
	case 63:
#line 158 ".\tiger.y"
	{yyval.var = A_SubscriptVar(EM_tokPos, yyvsp[-3].var, yyvsp[-1].exp);;
	break; }
	case 64:
#line 160 ".\tiger.y"
	{yyval.exp = A_CallExp(EM_tokPos, yyvsp[-3].sym, yyvsp[-1].explist);;
	break; }
	case 65:
#line 162 ".\tiger.y"
	{yyval.explist = A_ExpList(yyvsp[-2].exp, yyvsp[0].explist);;
	break; }
	case 66:
#line 163 ".\tiger.y"
	{yyval.explist = A_ExpList(yyvsp[0].exp, NULL);;
	break; }
	case 67:
#line 164 ".\tiger.y"
	{yyval.explist = NULL;;
	break; }
	case 68:
#line 166 ".\tiger.y"
	{/*printf("\n$%s$\n",$1);*/yyval.sym = S_Symbol(yyvsp[0].sval); /*printf("\nt$%s$t\n", S_name($$));*/;
	break; }
	}
	/* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

	yyvsp -= yylen;
	yyssp -= yylen;
#ifdef YYLSP_NEEDED
	yylsp -= yylen;
#endif

#if YYDEBUG != 0
	if (yydebug)
	{
		short *ssp1 = yyss - 1;
		fprintf(stderr, "state stack now");
		while (ssp1 != yyssp)
			fprintf(stderr, " %d", *++ssp1);
		fprintf(stderr, "\n");
	}
#endif

	*++yyvsp = yyval;

#ifdef YYLSP_NEEDED
	yylsp++;
	if (yylen == 0)
	{
		yylsp->first_line = yylloc.first_line;
		yylsp->first_column = yylloc.first_column;
		yylsp->last_line = (yylsp - 1)->last_line;
		yylsp->last_column = (yylsp - 1)->last_column;
		yylsp->text = 0;
	}
	else
	{
		yylsp->last_line = (yylsp + yylen - 1)->last_line;
		yylsp->last_column = (yylsp + yylen - 1)->last_column;
	}
#endif

	/* Now "shift" the result of the reduction.
	Determine what state that goes to,
	based on the state we popped back to
	and the rule number reduced by.  */

	yyn = yyr1[yyn];

	yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
	if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
		yystate = yytable[yystate];
	else
		yystate = yydefgoto[yyn - YYNTBASE];

	goto yynewstate;

yyerrlab:   /* here on detecting error */

	if (!yyerrstatus)
		/* If not already recovering from an error, report this error.  */
	{
		++yynerrs;

#ifdef YYERROR_VERBOSE
		yyn = yypact[yystate];

		if (yyn > YYFLAG && yyn < YYLAST)
		{
			int size = 0;
			char *msg;
			int x, count;

			count = 0;
			/* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
			for (x = (yyn < 0 ? -yyn : 0);
				x < (sizeof(yytname) / sizeof(char *)); x++)
				if (yycheck[x + yyn] == x)
					size += strlen(yytname[x]) + 15, count++;
			msg = (char *)malloc(size + 15);
			if (msg != 0)
			{
				strcpy(msg, "parse error");

				if (count < 5)
				{
					count = 0;
					for (x = (yyn < 0 ? -yyn : 0);
						x < (sizeof(yytname) / sizeof(char *)); x++)
						if (yycheck[x + yyn] == x)
						{
							strcat(msg, count == 0 ? ", expecting `" : " or `");
							strcat(msg, yytname[x]);
							strcat(msg, "'");
							count++;
						}
				}
				yyerror(msg);
				free(msg);
			}
			else
				yyerror("parse error; also virtual memory exceeded");
		}
		else
#endif /* YYERROR_VERBOSE */
			yyerror("parse error");
	}

	goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

	if (yyerrstatus == 3)
	{
		/* if just tried and failed to reuse lookahead token after an error, discard it.  */

		/* return failure if at end of input */
		if (yychar == YYEOF)
			YYABORT;

#if YYDEBUG != 0
		if (yydebug)
			fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

		yychar = YYEMPTY;
	}

	/* Else will try to reuse lookahead token
	after shifting the error token.  */

	yyerrstatus = 3;		/* Each real token shifted decrements this */

	goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
			   /* This is wrong; only states that explicitly want error tokens
			   should shift them.  */
	yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
	if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

	if (yyssp == yyss) YYABORT;
	yyvsp--;
	yystate = *--yyssp;
#ifdef YYLSP_NEEDED
	yylsp--;
#endif

#if YYDEBUG != 0
	if (yydebug)
	{
		short *ssp1 = yyss - 1;
		fprintf(stderr, "Error: state stack now");
		while (ssp1 != yyssp)
			fprintf(stderr, " %d", *++ssp1);
		fprintf(stderr, "\n");
	}
#endif

yyerrhandle:

	yyn = yypact[yystate];
	if (yyn == YYFLAG)
		goto yyerrdefault;

	yyn += YYTERROR;
	if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
		goto yyerrdefault;

	yyn = yytable[yyn];
	if (yyn < 0)
	{
		if (yyn == YYFLAG)
			goto yyerrpop;
		yyn = -yyn;
		goto yyreduce;
	}
	else if (yyn == 0)
		goto yyerrpop;

	if (yyn == YYFINAL)
		YYACCEPT;

#if YYDEBUG != 0
	if (yydebug)
		fprintf(stderr, "Shifting error token, ");
#endif

	*++yyvsp = yylval;
#ifdef YYLSP_NEEDED
	*++yylsp = yylloc;
#endif

	yystate = yyn;
	goto yynewstate;
}
#line 167 ".\tiger.y"
