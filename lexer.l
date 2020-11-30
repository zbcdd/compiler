%x COMMENT
D			[0-9]
L           [a-zA-Z_]

%{
#include <stdio.h>
#include "./ast/AST.h"
#include "parser.tab.h"

extern symtab_list* list_ptr;

void yyerror(char const *s);
void count(char const*, char const*);
%}
%option yylineno

%%

"/*"           { BEGIN(COMMENT) ; }
<COMMENT>"*/"  { BEGIN(INITIAL); }
<COMMENT>[ \t\n]+   {printf("inside commenet ws\n");}
<COMMENT>([^*]|\en)+|.
<COMMENT><<EOF>>    {printf("Unterminated comment\n"); return 0;}
"//".*\n        

"break"			{ count("BREAK", "---"); return(BREAK); }
"continue"		{ count("CONTINUE", "---"); return(CONTINUE); }
"do"			{ count("DO", "---"); return(DO); }
"else"			{ count("ELSE", "---"); return(ELSE); }
"for"			{ count("FOR", "---"); return(FOR); }
"if"			{ count("IF", "---"); return(IF); }
"int"			{ count("INT", "---"); return(INT); }
"return"		{ count("RETURN", "---"); return(RETURN); }
"struct"		{ count("STRUCT", "---"); return(STRUCT); }
"void"			{ count("VOID", "---"); return(VOID); }
"while"			{ count("WHILE", "---"); return(WHILE); }
"cin"           { count("CIN", "---"); return(CIN); }
"cout"          { count("COUT", "---"); return(COUT); }

{L}({L}|{D})*	{ yylval.str = yytext; count("IDENTIFIER", yytext); return(IDENTIFIER); }
0|[1-9]{D}*|-[1-9]{D}*  { yylval.str = yytext; count("CONSTANT", yytext); return(CONSTANT); }

">>"			{ count("IO_OP", "RIGHT_OP"); return(RIGHT_OP); }
"<<"			{ count("IO_OP", "LEFT_OP"); return(LEFT_OP); }
"->"			{ count("POINTER_OP", "PTR_OP"); return(PTR_OP); }
"&&"			{ count("LOGICAL_OP", "AND_OP"); return(AND_OP); }
"||"			{ count("LOGICAL_OP", "OR_OP"); return(OR_OP); }
"<="			{ count("REL_OP", "LE_OP"); return(LE_OP); }
">="			{ count("REL_OP", "GE_OP"); return(GE_OP); }
"=="			{ count("REL_OP", "EQ_OP"); return(EQ_OP); }
"!="			{ count("REL_OP", "NE_OP"); return(NE_OP); }
";"			    { count("SEMICOLON", "---"); return(';'); }
"{"		        { count("LBRACE", "---"); list_ptr -> push_symtab(); return('{');}
"}"		        { count("RBRACE", "---"); return('}'); }
","			    { count("COMA", "---"); return(','); }
"="			    { count("ASSIGN", "---"); return('='); }
"("			    { count("LP", "---"); return('('); }
")"			    { count("RP", "---"); return(')'); }
"["		        { count("LMP", "---"); return('['); }
"]"		        { count("RMP", "---"); return(']'); }
"."			    { count("DOT", "---"); return('.'); }
"!"			    { count("LOGICAL_OP", "NOT_OP"); return('!'); }
"-"			    { count("ARI_OP", "---"); return('-'); }
"+"			    { count("ARI_OP", "---"); return('+'); }
"*"			    { count("ARI_OP", "---"); return('*'); }
"/"			    { count("ARI_OP", "---"); return('/'); }
"%"			    { count("ARI_OP", "---"); return('%'); }
"<"			    { count("REL_OP", "---"); return('<'); }
">"			    { count("REL_OP", "---"); return('>'); }
"^"			    { count("ARI_OP", "---"); return('^'); }
"&"             { count("POINTER_OP", "---"); return('&'); }

[ \t\v\n\f]
.			    { printf("syntax error!: %s", yytext); }

%%

int yywrap(void)
{
	return 1;
}

int column = 0;

void count(char const* token_name, char const* token_value)
{
    printf("%*s%*s%*s\n", -20, yytext, -20, token_name, -20, token_value);
}
