%{
	#include <stdio.h>	
	#include <stdlib.h>
	#include <string.h>
	extern int yylex();
	char* getCadeia(FILE* entrada);
	extern char* yytext;
	extern int errorColumn;
	extern int errorLine;
	char* fullString;

	int yyerror(char *s){   
		int i, line=1, tabs=0, iAux, lineComment=0, limit;
		char* fullString;

		rewind(stdin);
		fullString = getCadeia(stdin);
		//printf("ERROR LINE: %d\n", errorLine);
		//printf("PROGRAMA: \n%s\n\n", fullString);
		for(i=0;i<strlen(fullString) && line<=errorLine-1;i++){
			if(fullString[i]=='\n')
				line++;
		}
		iAux = i;
		for(i=iAux;;i++){
			if(fullString[i]!='\n' && fullString[i]!='\0'){
				if(fullString[i]=='/' && fullString[i+1]=='/')
					lineComment=i;
			}
			else
				break;
		}
		if(yytext[0]!=0)
			printf("error:syntax:%d:%d: %s\n", errorLine, (errorColumn-strlen(yytext)), yytext);
		else{
			if(lineComment==0)
				printf("error:syntax:%d:%d: expected declaration or statement at end of input\n", errorLine, (errorColumn-strlen(yytext)));
			else
				printf("error:syntax:%d:%d: expected declaration or statement at end of input\n", errorLine, lineComment+1);
		}
		for(i=iAux;;i++){
			if(fullString[i]!='\n' && fullString[i]!='\0'){
				printf("%c", fullString[i]);
				if(fullString[i]=='\t' && i-iAux<=errorColumn-1)
					tabs++;
				if(fullString[i]=='/' && fullString[i+1]=='/')
					lineComment=i;
			}
			else
				break;
		}
		printf("\n");
		if(yytext[0]==0 && lineComment>0)
			limit=lineComment;
		else
			limit=errorColumn-strlen(yytext)-1;
		for(i=0;i<tabs;i++)
			printf("\t");
		for(i=tabs;;i++){
			if(i<limit)
				printf(" ");
			else{
				printf("^");
				break;
			}
		}
		//printf("NUMBER TABS: %d\n COLUNA: %d\n", tabs, errorColumn);

		exit(1);
	}

%}
	
	/* Declare Tokens */
	%token VOID
	%token INT
	%token CHAR
	%token RETURN
	%token BREAK
	%token SWITCH
	%token CASE
	%token DEFAULT
	%token DO
	%token WHILE
	%token FOR
	%token IF
	%token ELSE
	%token TYPEDEF
	%token STRUCT
	%token PLUS
	%token MINUS
	%token MULTIPLY
	%token DIV
	%token REMAINDER
	%token INC
	%token DEC
	%token BITWISE_AND
	%token BITWISE_OR
	%token BITWISE_NOT
	%token BITWISE_XOR
	%token LOGICAL_AND
	%token LOGICAL_OR
	%token EQUAL
	%token NOT
	%token NOT_EQUAL
	%token LESS_THAN
	%token GREATER_THAN
	%token LESS_EQUAL
	%token GREATER_EQUAL
	%token R_SHIFT
	%token L_SHIFT
	%token ASSIGN
	%token ADD_ASSIGN
	%token MINUS_ASSIGN
	%token SEMICOLON
	%token COMMA
	%token COLON
	%token L_PAREN
	%token R_PAREN
	%token L_CURLY_BRACKET
	%token R_CURLY_BRACKET
	%token L_SQUARE_BRACKET
	%token R_SQUARE_BRACKET
	%token TERNARY_CONDITIONAL
	%token NUMBER_SIGN
	%token POINTER
	%token PRINTF
	%token SCANF
	%token DEFINE
	%token EXIT
	%token IDENTIFIER
	%token NUM_OCTAL
	%token NUM_INTEGER
	%token NUM_HEXA
	%token STRING
	%token CHARACTER

%start inicio

%%

inicio:  programa {printf("SUCCESSFUL COMPILATION.");}

programa:  declaracoes endPrograma
		|  funcao endPrograma
;
endPrograma:  programa
		|
;

declaracoes:  NUMBER_SIGN DEFINE IDENTIFIER expressao
		|  varDeclar
		|  protoDeclar
;

funcao:  tipo aFnc
;
aFnc:  MULTIPLY aFnc
	|  IDENTIFIER params L_CURLY_BRACKET bFnc
;
bFnc:  comandos R_CURLY_BRACKET
	|  varDeclar bFnc
;

varDeclar:  tipo aVdc
;
aVdc:  MULTIPLY aVdc
	|  IDENTIFIER bVdc
;
bVdc:  L_SQUARE_BRACKET expressao R_SQUARE_BRACKET bVdc
	|  ASSIGN attrExpressao cVdc
	|  cVdc
;
cVdc:  SEMICOLON
	|  COMMA aVdc
;

protoDeclar:  tipo aPtd
;
aPtd:  MULTIPLY aPtd
	|  IDENTIFIER params SEMICOLON
;

params:  L_PAREN aPrm
;
aPrm:  R_PAREN
	|  bPrm
;
bPrm:  tipo cPrm
;
cPrm:  MULTIPLY cPrm
	|  IDENTIFIER dPrm
;
dPrm:  COMMA bPrm
	|  R_PAREN
	|  L_SQUARE_BRACKET expressao R_SQUARE_BRACKET dPrm
;

tipo:  INT
	|  CHAR
	|  VOID
;

bloco:  L_CURLY_BRACKET comandos R_CURLY_BRACKET
;

comandos:  listaComandos aCmd
;
aCmd:  comandos
	|
;

listaComandos: DO bloco WHILE L_PAREN expressao R_PAREN SEMICOLON
			|  IF L_PAREN expressao R_PAREN bloco aLcm
			|  WHILE L_PAREN expressao R_PAREN bloco
			|  FOR L_PAREN bLcm SEMICOLON bLcm SEMICOLON bLcm R_PAREN bloco
			|  PRINTF L_PAREN STRING cLcm R_PAREN SEMICOLON
			|  SCANF L_PAREN STRING COMMA BITWISE_AND IDENTIFIER R_PAREN SEMICOLON
			|  EXIT L_PAREN expressao R_PAREN SEMICOLON
			|  RETURN bLcm SEMICOLON
			|  expressao SEMICOLON
			|  SEMICOLON
			|  bloco
;
aLcm:  ELSE bloco
	|
;
bLcm:  expressao
	|
;
cLcm:  COMMA expressao
	|
;

expressao:  attrExpressao aExp
;
aExp:  COMMA expressao
	|
;

attrExpressao: condExpressao
			|  unaryExpressao aAtt attrExpressao
;
aAtt:  ASSIGN
	|  ADD_ASSIGN
	|  MINUS_ASSIGN
;

condExpressao:  logicORExpressao aCnd
;
aCnd:  TERNARY_CONDITIONAL expressao COLON condExpressao
	|
;

logicORExpressao:  logicANDExpressao aOrl
;
aOrl:  LOGICAL_OR logicANDExpressao aOrl
	|
;

logicANDExpressao:  ORExpressao aAnl
;
aAnl:  LOGICAL_AND ORExpressao aAnl
	|
;

ORExpressao:  XORExpressao aOre
;
aOre:  BITWISE_OR XORExpressao aOre
	|
;

XORExpressao:  ANDExpressao aXor
;
aXor:  BITWISE_XOR ANDExpressao aXor
	|
;

ANDExpressao:  igualExpressao aAnd
;
aAnd:  BITWISE_AND igualExpressao aAnd
	|
;

igualExpressao:  relacExpressao aIge
;
aIge:  EQUAL relacExpressao aIge
	|  NOT_EQUAL relacExpressao aIge
	|
;

relacExpressao:  shiftExpressao aRlc
;
aRlc:  LESS_THAN shiftExpressao aRlc
	|  LESS_EQUAL shiftExpressao aRlc
	|  GREATER_THAN shiftExpressao aRlc
	|  GREATER_EQUAL shiftExpressao aRlc
	|
;

shiftExpressao:  aditExpressao aShf
;
aShf:  R_SHIFT aditExpressao aShf
	|  L_SHIFT aditExpressao aShf
	|
;

aditExpressao:  multipExpressao aAdt
;
aAdt:  MINUS multipExpressao aAdt
	|  PLUS multipExpressao aAdt
	|
;

multipExpressao:  castExpressao aMtp
;
aMtp:  MULTIPLY castExpressao aMtp
	|  DIV castExpressao aMtp
	|  REMAINDER castExpressao aMtp
	|
;

castExpressao:  unaryExpressao
			|  L_PAREN tipo aCst
;
aCst:  MULTIPLY aCst
	|  R_PAREN castExpressao
;

unaryExpressao:  posFixExpressao
			  |  INC unaryExpressao
			  |  DEC unaryExpressao
			  |  BITWISE_AND castExpressao
			  |  MULTIPLY castExpressao
			  |  PLUS castExpressao
			  |  MINUS castExpressao
			  |  BITWISE_NOT castExpressao
			  |  NOT castExpressao
;

posFixExpressao:  primaryExpressao
			   |  posFixExpressao aPfx
;
aPfx:  L_SQUARE_BRACKET expressao R_SQUARE_BRACKET
	|  INC
	|  DEC
	|  L_PAREN R_PAREN
	|  L_PAREN bPfx
;
bPfx:  attrExpressao R_PAREN
	|  attrExpressao COMMA bPfx
;

primaryExpressao:  IDENTIFIER
				|  numero
				|  CHARACTER
				|  STRING
				|  L_PAREN expressao R_PAREN
;

numero:  NUM_INTEGER
	  |  NUM_HEXA
	  |  NUM_OCTAL
;

%%
char* getCadeia(FILE* entrada){
    char* cadeia;
    long int size;
    char aux;
    int i;


    for(i=0;aux!=EOF;i++)
        aux=fgetc(entrada);
    size=i+1;
    rewind(entrada);
    cadeia = (char*) malloc(size*sizeof(char));
    for(i=0;i<size-2;i++)
        cadeia[i] = fgetc(entrada);
    cadeia[strlen(cadeia)] = '\0';

    return cadeia;
}
int main(int argc, char **argv){

	yyparse();
    return 0;
}