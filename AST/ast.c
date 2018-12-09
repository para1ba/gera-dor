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

program* newProgram(){
    program* anyProgram = NULL;

    anyProgram = (program*) malloc(sizeof(program));
    anyProgram->functions = createLista();

    return anyProgram;
}
void insertFunctionOnProgram(program* anyProgram, funct* anyFunction){
    addNode(anyProgram->functions, anyFunction);
}
funct* newFunction(char name[256]){
    funct* anyFunction = NULL;

    anyFunction = (funct*) malloc(sizeof(funct));
    strcpy(anyFunction->name, name);
    anyFunction->parameters = createLista();
    anyFunction->commands = createLista();

    return anyFunction;
}
void insertParameterOnFunction(funct* anyFunction, variable* anyVariable){
    addNode(anyFunction->parameters, anyVariable);
}
void insertCommandsOnFunction(funct* anyFunction, command* anyCommand){
    addNode(anyFunction->commands, anyCommand);
}
variable* newVariable(int type, char name[256]){
    variable* anyVariable = NULL;

    anyVariable = (variable*) malloc(sizeof(variable));
    anyVariable->type = type;
    strcpy(anyVariable->name, name);

    return anyVariable;
}
command* newCommand(int type){
    command* anyCommand = NULL;

    anyCommand = (command*) malloc(sizeof(command));
    anyCommand->type = type;
    anyCommand->expression = NULL;
    if(type == IF_STMT){
        anyCommand->field1 = createLista();
        anyCommand->field2 = createLista();
    }
    else if(type == WHILE_STMT){
        anyCommand->field1 = createLista();
        anyCommand->field2 = NULL;
    }
    else if(type == EXP_STMT){
        anyCommand->field1 = NULL;
        anyCommand->field2 = NULL;
    }

    return anyCommand;
}
void insertExpressionOnCommand(command* anyCommand, treenode* anyExpression){
    if((anyCommand->type == IF_STMT || anyCommand->type == WHILE_STMT) && anyCommand->expression == NULL)
        anyCommand->expression = anyExpression;
    else
        printf("ERRO AO INSERIR EXPRESSÃO\n");
}
void insertCommandOnCommand(command* anyCommand, command* anotherCommand, int field){
    if((anyCommand->type == IF_STMT || anyCommand->type == WHILE_STMT)){
        if(field == 1)
            addNode(anyCommand->field1, anotherCommand);
        else if(field == 2){
            if(anyCommand->type == IF_STMT)
                addNode(anyCommand->field2, anotherCommand);
            else
                printf("ERRO AO INSERIR COMANDO\n");
        }
    }
    else
        printf("ERRO AO INSERIR COMANDO\n");
}
treenode* insertNode(int type, char value[256], treenode* left, treenode* right){
	treenode* aux = (treenode*) malloc(sizeof(treenode));

	aux->type = type;
	strcpy(aux->value, value);
	aux->left = left;
	aux->right = right;

	return aux;
}



void printProgram(program* anyProgram){
    int i, size;
    Node anyNode = NULL;
    funct* anyFunction = NULL;

    size = lenghtLista(anyProgram->functions);
    anyNode = getFirstNode(anyProgram->functions);
    for(i=0;i<size;i++){
        anyFunction = getThing(anyNode);
        printFunction(anyFunction);
        anyNode = getNext(anyNode);
    }
}
void printFunction(funct* anyFunction){
    int i, size;
    Node anyNode = NULL;
    variable* anyVariable = NULL;
    command* anyCommand = NULL;

    printf("NOME DA FUNÇÃO: %s\n", anyFunction->name);
    printf("PARÂMETROS DA FUNCAO: ");
    size = lenghtLista(anyFunction->parameters);
    anyNode = getFirstNode(anyFunction->parameters);
    for(i=0;i<size;i++){
        anyVariable = getThing(anyNode);
        printVariable(anyVariable);
        anyNode = getNext(anyNode);
        if(anyNode!=NULL)
            printf(",");
    }
    printf("\n");
    printf("COMANDOS DA FUNCAO:\n");
    size = lenghtLista(anyFunction->commands);
    anyNode = getFirstNode(anyFunction->commands);
    for(i=0;i<size;i++){
        anyCommand = getThing(anyNode);
        printCommand(anyCommand);
        anyNode = getNext(anyNode);
        if(anyNode!=NULL)
            printf("\n");
    }
}
void printVariable(variable* anyVariable){
    switch(anyVariable->type){
        case INT:
            printf("int ");
            break;
        case CHAR:
            printf("char ");
            break;
        case DOUBLE:
            printf("double ");
            break;
        case FLOAT:
            printf("float ");
            break;
    }
    printf(" %s", anyVariable->name);
}
void printCommand(command* anyCommand){
    int i, size;
    Node anyNode = NULL;
    command* anotherCommand = NULL;

    switch(anyCommand->type){
        case IF_STMT:
            printf("if ");
            printExpression(anyCommand->expression);
            printf("\n");
            size = lenghtLista(anyCommand->field1);
            anyNode = getFirstNode(anyCommand->field1);
            for(i=0;i<size;i++){
                anotherCommand = getThing(anyNode);
                printCommand(anotherCommand);
                anyNode = getNext(anyNode);
                if(anyNode!=NULL)
                    printf("\n");
            }
            size = lenghtLista(anyCommand->field2);
            anyNode = getFirstNode(anyCommand->field2);
            for(i=0;i<size;i++){
                anotherCommand = getThing(anyNode);
                printCommand(anotherCommand);
                anyNode = getNext(anyNode);
                if(anyNode!=NULL)
                    printf("\n");
            }
            break;

        case WHILE_STMT:
            printf("while ");
            printExpression(anyCommand->expression);
            printf("\n");
            size = lenghtLista(anyCommand->field1);
            anyNode = getFirstNode(anyCommand->field1);
            for(i=0;i<size;i++){
                anotherCommand = getThing(anyNode);
                printCommand(anotherCommand);
                anyNode = getNext(anyNode);
                if(anyNode!=NULL)
                    printf("\n");
            }
            break;
        case EXP_STMT:
            printExpression(anyCommand->expression);
            break;
    }
}
void printExpression(treenode* anyTreenode){
    if(anyTreenode){
        printExpression(anyTreenode->left);
        printExpression(anyTreenode->right);
        switch(anyTreenode->type){
            case NUMBER:
                printf(" %s ", anyTreenode->value);
                break;
            case PLUS:
                printf("+");
                break;
            case MULTI:
                printf("*");
                break;
            case MINUS:
                printf("-");
                break;
            case DIV:
                printf("/");
                break;
        }
    }
}
