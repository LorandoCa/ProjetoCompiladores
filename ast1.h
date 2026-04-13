#ifndef AST1_H
#define AST1_H

enum category {
    /* Nó raiz */
    Program,

    /* Declarações */
    FieldDecl,
    VarDecl,

    /* Métodos */
    MethodDecl,
    MethodHeader,
    MethodParams,
    ParamDecl,
    MethodBody,
    //Added for support    -> Ignore them in print function 
    Args,
    Dummy, //Added to store nodes that had errors

    /* Statements */
    Block,
    If,
    While,
    Return,
    Call,
    Print,
    ParseArgs,
    Assign,

    /* Operadores binários */
    Or,
    And,
    Eq,
    Ne,
    Lt,
    Gt,
    Le,
    Ge,
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    Lshift,
    Rshift,
    Xor,

    /* Operadores unários */
    Not,
    Minus,
    Plus,

    /* Outros operadores */
    Length,

    /* Tipos */
    Bool,
    Int,
    Double,
    Void,
    StringArray,

    /* Terminais / Literais */
    Boollit,
    Decimal,
    Natural,
    Strlit,
    Identifier,
};


struct node {
    enum category category;
    char *token;
    struct node_list *children;
};

struct node_list {
    struct node *node;
    struct node_list *next;
};

struct programs_list {
    struct node *program;
    struct programs_list *next;  //Next program
};

struct node *newnode(enum category category, char *token);
void addchild(struct node *parent, struct node *child);
void append(struct programs_list *programs, struct node *new_program);
struct node *addChildren(struct programs_list *programs);
void addFront(struct node *parent, struct node *auxTree);
#endif