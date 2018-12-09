%option noyywrap

%x IN_COMMENT

%{
	#include "sintatico.tab.h"
	#include <stdio.h>

	void errorPosition(char* string, int* errorLine, int* errorColumn){
		int i;

		for(i=0;i<strlen(string);i++){
			if(string[i]=='\n'){
				*errorLine=*errorLine+1;
				*errorColumn=1;
			}
			else
				*errorColumn=*errorColumn+1;
		}
	}
	int errorColumn=1;
	int errorLine=1;
	int startCommentLine=0;
	int startCommentColumn=0;
	int lexicalErrors=0;
%}

%%
[\n]            									{errorPosition(yytext, &errorLine, &errorColumn);}
[\t]            									{errorPosition(yytext, &errorLine, &errorColumn);}
" "             									{errorPosition(yytext, &errorLine, &errorColumn);}
"void"          									{errorPosition(yytext, &errorLine, &errorColumn); return VOID;}
"int"           									{errorPosition(yytext, &errorLine, &errorColumn); return INT;}
"char"          									{errorPosition(yytext, &errorLine, &errorColumn); return CHAR;}
"return"       										{errorPosition(yytext, &errorLine, &errorColumn); return RETURN;}
"break"         									{errorPosition(yytext, &errorLine, &errorColumn); return BREAK;}
"switch"        									{errorPosition(yytext, &errorLine, &errorColumn); return SWITCH;}
"case"          									{errorPosition(yytext, &errorLine, &errorColumn); return CASE;}
"default"       									{errorPosition(yytext, &errorLine, &errorColumn); return DEFAULT;}
"do"            									{errorPosition(yytext, &errorLine, &errorColumn); return DO;}
"while"         									{errorPosition(yytext, &errorLine, &errorColumn); return WHILE;}
"for"           									{errorPosition(yytext, &errorLine, &errorColumn); return FOR;}
"if"            									{errorPosition(yytext, &errorLine, &errorColumn); return IF;}
"else"          									{errorPosition(yytext, &errorLine, &errorColumn); return ELSE;}
"typedef"       									{errorPosition(yytext, &errorLine, &errorColumn); return TYPEDEF;}
"struct"        									{errorPosition(yytext, &errorLine, &errorColumn); return STRUCT;}
"+"             									{errorPosition(yytext, &errorLine, &errorColumn); return PLUS;}
"-"             									{errorPosition(yytext, &errorLine, &errorColumn); return MINUS;}
"*"             									{errorPosition(yytext, &errorLine, &errorColumn); return MULTIPLY;}
"/"             									{errorPosition(yytext, &errorLine, &errorColumn); return DIV;}
"%"             									{errorPosition(yytext, &errorLine, &errorColumn); return REMAINDER;}
"++"            									{errorPosition(yytext, &errorLine, &errorColumn); return INC;}
"--"            									{errorPosition(yytext, &errorLine, &errorColumn); return DEC;}
"&"             									{errorPosition(yytext, &errorLine, &errorColumn); return BITWISE_AND;}
"|"             									{errorPosition(yytext, &errorLine, &errorColumn); return BITWISE_OR;}
"~"             									{errorPosition(yytext, &errorLine, &errorColumn); return BITWISE_NOT;}
"^"             									{errorPosition(yytext, &errorLine, &errorColumn); return BITWISE_XOR;}
"!"             									{errorPosition(yytext, &errorLine, &errorColumn); return NOT;}
"&&"            									{errorPosition(yytext, &errorLine, &errorColumn); return LOGICAL_AND;}
"||"            									{errorPosition(yytext, &errorLine, &errorColumn); return LOGICAL_OR;}
"=="            									{errorPosition(yytext, &errorLine, &errorColumn); return EQUAL;}
"!="            									{errorPosition(yytext, &errorLine, &errorColumn); return NOT_EQUAL;}
"<"             									{errorPosition(yytext, &errorLine, &errorColumn); return LESS_THAN;}
">"             									{errorPosition(yytext, &errorLine, &errorColumn); return GREATER_THAN;}
"<="            									{errorPosition(yytext, &errorLine, &errorColumn); return LESS_EQUAL;}
">="            									{errorPosition(yytext, &errorLine, &errorColumn); return GREATER_EQUAL;}
">>"            									{errorPosition(yytext, &errorLine, &errorColumn); return R_SHIFT;}
"<<"            									{errorPosition(yytext, &errorLine, &errorColumn); return L_SHIFT;}
"="             									{errorPosition(yytext, &errorLine, &errorColumn); return ASSIGN;}
"+="            									{errorPosition(yytext, &errorLine, &errorColumn); return ADD_ASSIGN;}
"-="            									{errorPosition(yytext, &errorLine, &errorColumn); return MINUS_ASSIGN;}
";"             									{errorPosition(yytext, &errorLine, &errorColumn); return SEMICOLON;}
","             									{errorPosition(yytext, &errorLine, &errorColumn); return COMMA;}
":"             									{errorPosition(yytext, &errorLine, &errorColumn); return COLON;}
"("             									{errorPosition(yytext, &errorLine, &errorColumn); return L_PAREN;}
")"             									{errorPosition(yytext, &errorLine, &errorColumn); return R_PAREN;}
"{"             									{errorPosition(yytext, &errorLine, &errorColumn); return L_CURLY_BRACKET;}
"}"             									{errorPosition(yytext, &errorLine, &errorColumn); return R_CURLY_BRACKET;}
"["             									{errorPosition(yytext, &errorLine, &errorColumn); return L_SQUARE_BRACKET;}
"]"             									{errorPosition(yytext, &errorLine, &errorColumn); return R_SQUARE_BRACKET;}
"?"            	 									{errorPosition(yytext, &errorLine, &errorColumn); return TERNARY_CONDITIONAL;}
"#"             									{errorPosition(yytext, &errorLine, &errorColumn); return NUMBER_SIGN;}
"->"            									{errorPosition(yytext, &errorLine, &errorColumn); return POINTER;}
"printf"        									{errorPosition(yytext, &errorLine, &errorColumn); return PRINTF;}
"scanf"         									{errorPosition(yytext, &errorLine, &errorColumn); return SCANF;}
"define"        									{errorPosition(yytext, &errorLine, &errorColumn); return DEFINE;}
"exit"          									{errorPosition(yytext, &errorLine, &errorColumn); return EXIT;}
[a-zA-Z_][a-zA-Z0-9_]*    			 				{errorPosition(yytext, &errorLine, &errorColumn); return IDENTIFIER;}
"0"[1-7]                  			 				{errorPosition(yytext, &errorLine, &errorColumn); return NUM_OCTAL;}
[0-9]+                    			 				{errorPosition(yytext, &errorLine, &errorColumn); return NUM_INTEGER;}
("0x"|"0X")[0-9a-fA-F]+          					{errorPosition(yytext, &errorLine, &errorColumn); return NUM_HEXA;}
"\"".*"\""               				 			{errorPosition(yytext, &errorLine, &errorColumn); return STRING;}
"\'"."\'"    				             			{errorPosition(yytext, &errorLine, &errorColumn); return CHARACTER;}
"//".*[\n]?      									{errorPosition(yytext, &errorLine, &errorColumn);}
"/*"												{startCommentLine=errorLine; startCommentColumn=errorColumn;errorPosition(yytext, &errorLine, &errorColumn);} BEGIN(IN_COMMENT);
.       											{printf("error:lexical:%d:%d: %s", errorLine, errorColumn, yytext); exit(1);}
<IN_COMMENT>{
		<<EOF>>   {printf("error:lexical:%d:%d: unterminated comment", startCommentLine, startCommentColumn); exit(1);}
     	"*/"      {errorPosition(yytext, &errorLine, &errorColumn);} BEGIN(INITIAL);
     	[^*\n]+   {errorPosition(yytext, &errorLine, &errorColumn);}
     	"*"       {errorPosition(yytext, &errorLine, &errorColumn);}
    	\n        {errorPosition(yytext, &errorLine, &errorColumn);}
	}
%%