#ifndef AST_H
#define AST_H

    /*TYPES: 1 = INT, 2 = CHAR, 3 = DOUBLE, 4 = FLOAT;*/
    typedef struct _treenode{
        int type;
        char value[256];
        struct _treenode* left;
        struct _treenode* right;
    }treenode;
    typedef struct _program{
        Lista functions;
    }program;
    typedef struct _funct{
        char name[256];
        Lista parameters;
        Lista commands;
    }funct;
    typedef struct _variable{
        int type;
        char name[256];
    }variable;
    /*TYPE: 1 = IF, 2 = WHILE, 3 = EXPRESSION*/
    typedef struct _command{
        int type;
        treenode* expression;
        Lista field1;
        Lista field2;
    }command;


    program* newProgram();
    void insertFunctionOnProgram(program* anyProgram, funct* anyFunction);
    funct* newFunction(char name[256]);
    void insertParameterOnFunction(funct* anyFunction, variable* anyVariable);
    void insertCommandsOnFunction(funct* anyFunction, command* anyCommand);
    variable* newVariable(int type, char name[256]);
    command* newCommand(int type);
    void insertExpressionOnCommand(command* anyCommand, treenode* anyExpression);
    void insertCommandOnCommand(command* anyCommand, command* anotherCommand, int field);
    treenode* insertNode(int type, char value[256], treenode* left, treenode* right);


    void printProgram(program* anyProgram);
    void printFunction(funct* anyFunction);
    void printVariable(variable* anyVariable);
    void printCommand(command* anyCommand);
    void printExpression(treenode* anyTreenode);



#endif
