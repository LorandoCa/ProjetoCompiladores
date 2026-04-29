#include <stdlib.h>
#include <stdio.h>
#include "ast1.h"

// create a node of a given category with a given lexical symbol
struct node *newnode(enum category category, char *token) {
    struct node *new = malloc(sizeof(struct node));
    new->category = category;
    new->token = token;
    new->args = NULL;
    new->type = TYPE_UNDEF;
    new->children = malloc(sizeof(struct node_list));
    new->children->node = NULL;
    new->children->next = NULL;
    return new;
}

// append a node to the list of children of the parent node
void addchild(struct node *parent, struct node *child) {

    struct node_list *children = parent->children;
    if(children->node == NULL){
        children->node = child;
        return;
    }

    struct node_list *new = malloc(sizeof(struct node_list));
    new->node = child;
    new->next = NULL;

    while(children->next != NULL)
        children = children->next;
    children->next = new;
}

//Append a new program to the previous programs list
void append(struct programs_list *programs, struct node *new_program){
    struct programs_list *atual = programs;

    struct programs_list *new = malloc(sizeof(struct programs_list));
    new->program = new_program;
    new->next = NULL;

    if(atual->program != NULL){ //Nao é o 1º elemento na lista ligada a ser preenchido

        while (atual->next != NULL){
            atual= atual->next;
        }
        atual->next = new;
        return;
    }

    atual->program = new_program;
    atual->next = NULL;

}


struct node *addChildren(struct programs_list *programs){

    //Percorer tudo e adicionar cada function ao node final
    struct node *finalTree = newnode(Program, NULL);

    struct programs_list *aux = programs;
    while (aux != NULL){
        struct node *atual = aux->program; // So childrens deste e passar para o proximo programa : programs->next

        struct node_list *child = atual->children;
        while (child != NULL){
            addchild(finalTree, child->node);
            child = child->next;
        }

        aux = aux -> next;
        
    }
    return finalTree;

}


void addFront(struct node *parent, struct node *child){

    if(parent == NULL || child == NULL) return;

    struct node_list *aux = parent->children;
    
    struct node_list *newFront = malloc( sizeof(struct node_list) );
    newFront->node = child;
    newFront->next = aux;
    parent->children = newFront;
    
}



