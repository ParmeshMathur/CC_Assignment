%option noyywrap

%{
#include <bits/stdc++.h>
#include "parser.tab.h"

using namespace std;
void syntaxError(char *);
%}

%%

"ADD"					{ return ADD; }
"SUBTRACT"				{ return SUBTRACT; }
"MULTIPLY"				{ return MULTIPLY; }
"DIVIDE"				{ return DIVIDE; }

"LEFT"					{ return LEFT; }
"RIGHT"					{ return RIGHT; }
"UP"					{ return UP; }
"DOWN"					{ return DOWN; }

"ASSIGN"				{ return ASSIGN; }
"TO"					{ return TO; }

"VAR"					{ return VAR; }
"IS"					{ return IS; }

"VALUE"					{ return VALUE; }
"IN"					{ return IN; }

,						{ return comma; }
[a-zA-z]+				{ strcpy(yylval.name, yytext); return identifier; }
([0-9]+[a-zA-z]+)		{ printf("Variable name cannot start with number.\n"); }
[+-]?[0-9]+				{ yylval.num = atoi(yytext); return number; }
\.						{ return full_stop; }
[ \t]					{ }
\n						{ return newline; }
.						{ syntaxError(yytext); }

%%


void syntaxError(char *s)
{
	printf("Syntax error at line %s\nTry again.", s);
}