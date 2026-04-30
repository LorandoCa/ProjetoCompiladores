#ifndef _SEMANTICS_H
#define _SEMANTICS_H

#include "ast1.h"

struct symbol_list {
	char *identifier;
	sem_type type;
	struct node *node;
	struct symbol_list *next;
	int param; // a value that will tell me if the token is a parametre or not( for print )
};


struct symbol_list_stack { // Usado so para metodos. Haverá um so symbol_list para fieldDeclaration e methodDeclaration para facil acesso no caso de utilizacao de uma var global
	char *identifier; // Nome do metodo/escopo
	struct symbol_list *list ;
	struct node *header; // Ajuda a limitar a  identificar o scope posteriormente
	struct symbol_list_stack *next;
};



struct symbol_list *insert_symbol(struct symbol_list *table, char *identifier, sem_type type, struct node *node, int param);
struct symbol_list *insert_method_symbol(struct symbol_list *table, char *identifier, sem_type type, struct node *node);
struct symbol_list *search_symbol(struct symbol_list *symbol_table, char *identifier);
int check_program(struct node *program);
void check_MethodDecl(struct node *Decl);
void check_MethodBody(struct node *body);
void check_statement(struct node *n);
void check_MethodHead(struct node *head);
sem_type check_expression(struct node *n) ;
struct symbol_list *check_parameters(struct node *MethodParams, struct symbol_list *symbol_table_prov);
sem_type check_calls(struct node *call);
void printError(struct node *no);
struct symbol_list *newlist();
struct symbol_list_stack *newStack();
// Calcular o numero de filhos do nó parameter declaration 

//auxiliar functions
void fill_args_from_header(struct node *header, char *args);
static int count_children(struct node *n) ;
static struct node *nth_child(struct node *n, int idx);
void print_symbol_tables(char *class_name);
const char *op_name(enum category c); // Para converter simbolos "add" em "+" por exemplo 

#endif
