#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "ast.h"

#define INT 1
    #define CHAR 2
    #define DOUBLE 3
    #define FLOAT 4
    #define IF_STMT 1
    #define WHILE_STMT 2
    #define EXP_STMT 3
    #define NUMBER 0
    #define PLUS 1
    #define MULTI 2
    #define MINUS 3
    #define DIV 4

int main(void){
    program* anyProgram = NULL;
    funct* fun = NULL;
    command* anyCommand = NULL;
    treenode* anyExpression = NULL;
    treenode* aux1 = NULL;
    treenode* aux2 = NULL;

    anyProgram = newProgram();
    fun = newFunction("renanBoiola");
    insertFunctionOnProgram(anyProgram, fun);
    anyCommand = newCommand(WHILE_STMT);
    aux1 = insertNode(NUMBER, "1", NULL, NULL);
    aux2 = insertNode(NUMBER, "2", NULL, NULL);
    anyExpression = insertNode(PLUS, "\0", aux1, aux2);
    insertExpressionOnCommand(anyCommand, anyExpression);
    insertCommandsOnFunction(fun, anyCommand);
    printProgram(anyProgram);

    return 0;
}
