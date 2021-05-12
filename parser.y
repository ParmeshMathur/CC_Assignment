%{
#include <bits/stdc++.h>
using namespace std;

int yylex();
int yyerror(string s);
int op_func(int optype);
extern int operate(int oper, int dir);
extern int assign(int val, int x, int y);
extern int namer(string s, int x, int y);
extern int query(int x, int y);
extern int printState();
extern int printBoard();
extern int putRand();

int oper;
int dir;
char varname[10];
int x, y;
int val;
%}

%define parse.lac full
%define parse.error verbose

%start statements

%type statement assignment naming query

%token ADD SUBTRACT MULTIPLY DIVIDE
%token LEFT RIGHT UP DOWN
%type <name> operation
%type <name> direction

%token ASSIGN TO

%token VAR IS 

%token VALUE IN

%token number identifier

%token full_stop comma newline

%type <num> number
%type <name> identifier

%union
{
	char name[10];
	int num;
}


%%


statements:	statement statements
			|

statement:	operation direction full_stop newline	{ printf("2048> "); op_func(1); }
			| operation direction newline			{ printf("2048> Command must end with a full stop\n"); fprintf(stderr, "-1\n" ); printf("\n\n----> "); }
			| assignment full_stop newline			{ printf("2048> "); op_func(2); }
			| assignment newline					{ printf("2048> Command must end with a full stop\n"); fprintf(stderr, "-1\n" ); printf("\n\n----> "); }
			| naming full_stop newline				{ printf("2048> "); op_func(3); }
			| naming newline						{ printf("2048> Command must end with a full stop\n"); fprintf(stderr, "-1\n" ); printf("\n\n----> "); }
			| query full_stop newline				{ printf("2048> "); op_func(4); }
			| query	newline							{ printf("2048> Command must end with a full stop\n"); fprintf(stderr, "-1\n" ); printf("\n\n----> "); }
			| newline								{ printf("2048> Unexpected new line.\n\n----> "); }
			| error newline 						{ yyerrok; fprintf(stderr, "-1\n" ); printf("\n\n----> "); }

operation:	ADD										{ oper = 1; }
			| SUBTRACT								{ oper = 2; }
			| MULTIPLY								{ oper = 3; }
			| DIVIDE								{ oper = 4; }

direction: 	LEFT									{ dir = 1; }
			| RIGHT									{ dir = 2; }
			| UP									{ dir = 3; }
			| DOWN									{ dir = 4; }

assignment:	ASSIGN number TO coordinates			{ printf("2048> Assign %d\n", $2); val = $2; }

naming: 	VAR identifier IS coordinates			{ printf("2048> Name %s\n", $2); memset(varname, 0, sizeof(varname)); strcpy(varname, $2); }

query: 		VALUE IN coordinates

coordinates:number comma number						{ x=$1; y=$3; }

%%

int op_func(int optype)
{
	switch(optype)
	{
		case 1:
		{
			// printf("calling operate\n");
			switch(oper)
			{
				case 1:
				{
					printf("Adding ");
					break;
				}
				case 2:
				{
					printf("Subtracting ");
					break;
				}
				case 3:
				{
					printf("Multiplying ");
					break;
				}
				case 4:
				{
					printf("Dividing ");
					break;
				}
			}
			switch(dir)
			{
				case 1:
				{
					printf("left\n");
					break;
				}
				case 2:
				{
					printf("right\n");
					break;
				}
				case 3:
				{
					printf("up\n");
					break;
				}
				case 4:
				{
					printf("down\n");
					break;
				}
			}
			if(operate(oper, dir)==0)
			{
				putRand();
			}
			else
			{
				printf("No change in state.\n");
			}
			printBoard();
			printState();
			break;
		}
		case 2:
		{
			// printf("calling assign\n");
			assign(val, x, y);
			break;
		}
		case 3:
		{
			// printf("calling namer\n");
			string s;
			{
				for(int i=0;i<strlen(varname);i++)
				{
					s.push_back(varname[i]);
				}
			}
			cout<<"String is: "<<s<<"\n\n";
			namer(s, x, y);
			break;
		}
		case 4:
		{
			// printf("calling query\n");
			query(x, y);
			break;
		}
		default: break;
	}
	printf("2048> Enter Command\n");
	printf("----> ");
	return 0;
}

int yyerror(string s)
{
	cout << s << "\n";
	return 0;
}