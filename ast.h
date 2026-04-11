#ifndef _AST_H
#define _AST_H

enum category { Program, Function, Parameters, Parameter, Arguments, Integer, Double, Identifier, Natural, Decimal, Call, If, Add, Sub, Mul, Div };

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

#endif
