/* START definitions section -- C code delimited by %{ ... %} and token declarations */

%{

#include <stdio.h>
#include "ast1.h"

int yylex(void);
void yyerror(char *);

struct programs_list *handle;
struct node *ast;

%}


%token CLASS LBRACE RBRACE PUBLIC STATIC SEMICOLON COMMA
%token BOOL INT VOID STRING LPAR RPAR LSQ RSQ
%token IF ELSE WHILE RETURN PRINT PARSEINT
%token DOTLENGTH ASSIGN
%token OR AND XOR EQ NE LT LE GT GE
%token LSHIFT RSHIFT PLUS MINUS STAR DIV MOD NOT
%token RESERVED

%token<lexeme> IDENTIFIER NATURAL DECIMAL INTEGER DOUBLE STRLIT BOOLLIT

%type<node> program DeclList MethodDecl FieldDecl IdentList IdentListVar Type
%type<node> MethodHeader FormalParamOpt FormalParams MethodBody
%type<node> StmtOrVarList VarDecl Statement StmtList IfStmt
%type<node> ExprOpt ExprStmt Expr AssignExpr
%type<node> OrExpr AndExpr XorExpr EqExpr RelExpr ShiftExpr
%type<node> AddExpr MulExpr UnaryExpr PostfixExpr ArgListOpt ArgList


%union{
    char *lexeme;
    struct node *node;
}

%nonassoc WITHOUT_ELSE
%nonassoc ELSE

%%


/* Falta adicionar funcionalidade para vários programas de uma vez */

/* === PROGRAMA === */
program: CLASS IDENTIFIER LBRACE DeclList RBRACE
                                    {   ast = $$ = $4;
                                        addFront($$, newnode(Identifier, $2) );
                                       }
    ;

DeclList: DeclList MethodDecl       { $$ = $1;
                                      addchild($1, $2); }

        | DeclList FieldDecl        {   $$ = $1;
                                        struct node *aux = $2;
                                        int type = 9;
                                        if( (aux != NULL) && (aux->children != NULL) && (aux->children->node != NULL) ) type = aux->children->node->category; // nodes type
                                        if(type != 9 ){ // Not dummy 
                                            struct node_list *childrenList = aux->children->next;
                                            while ((childrenList != NULL) ) {
                                                if (childrenList->node != NULL) {
                                                    struct node *parent = newnode(FieldDecl, NULL);
                                                    struct node *newtype = newnode(type , NULL); // copia o tipo
                                                    struct node *newNode = newnode( childrenList->node->category, childrenList->node->token);
                                                    addchild(parent, newtype);
                                                    addchild(parent, newNode );
                                                    addchild($$, parent);
                                                }
                                                childrenList = childrenList->next;
                                            }
                                        }
                                      }

        | DeclList SEMICOLON        { $$ = $1; }

        | /* vazio */               { $$ = newnode(Program, NULL); }    ;


/* === DECLARAÇÕES === */
MethodDecl: PUBLIC STATIC MethodHeader MethodBody
                                    {   $$ = newnode(MethodDecl, NULL); 
                                        addchild($$, $3);
                                        addchild($$, $4);
                                        }
    ;

FieldDecl: PUBLIC STATIC Type IdentList SEMICOLON
                                    { 
                                        $$ = $4;
                                        addFront($$, $3); //type fica no final
                                        }
            | error SEMICOLON  { $$ = newnode(Dummy, NULL); }
    ;

IdentList: IdentList COMMA IDENTIFIER
                                    {   $$ = $1;
                                        addchild($$, newnode(Identifier, $3) );
                                        }
         | IDENTIFIER               {   $$ = newnode(FieldDecl, NULL); // Posteriormente ignorado
                                        addchild($$, newnode(Identifier, $1) ); }
    ;

IdentListVar: IdentListVar COMMA IDENTIFIER
                                    {   $$ = $1;
                                        addchild($$, newnode(Identifier, $3) );
                                        }
         | IDENTIFIER               {   $$ = newnode(VarDecl, NULL);
                                        addchild($$, newnode(Identifier, $1) ); }
    ;

Type: BOOL                          { $$ = newnode(Bool, NULL); }
    | INT                           { $$ = newnode(Int, NULL); }
    | DOUBLE                        { $$ = newnode(Double, NULL); }
    ;

/* === CABEÇALHO DE MÉTODO === */
MethodHeader: Type IDENTIFIER LPAR FormalParamOpt RPAR
                                    {   $$ = newnode(MethodHeader, NULL);
                                        addchild($$, $1);
                                        addchild($$, newnode(Identifier, $2) );
                                        addchild($$, $4);
                                        }

            | VOID IDENTIFIER LPAR FormalParamOpt RPAR
                                    {   $$ = newnode(MethodHeader, NULL);
                                        addchild($$, newnode(Void, NULL) );
                                        addchild($$, newnode(Identifier, $2) );
                                        addchild($$, $4);
                                        }
    ;

FormalParamOpt: FormalParams        { $$ = $1; }
              | /* vazio */         { $$ = newnode(MethodParams, NULL); }
    ;

FormalParams: Type IDENTIFIER       { $$ = newnode(MethodParams, NULL);
                                      struct node *aux = newnode(ParamDecl, NULL);
                                      addchild(aux, $1);
                                      addchild(aux, newnode(Identifier, $2));
                                      addchild($$, aux); }

            | FormalParams COMMA Type IDENTIFIER
                                    { $$ = $1;
                                      struct node *aux = newnode(ParamDecl, NULL);
                                      addchild(aux, $3);
                                      addchild(aux, newnode(Identifier, $4));
                                      addchild($$, aux); }

            | STRING LSQ RSQ IDENTIFIER
                                    { $$ = newnode(MethodParams, NULL);
                                      struct node *aux = newnode(ParamDecl, NULL);
                                      addchild(aux, newnode(StringArray, NULL));
                                      addchild(aux, newnode(Identifier, $4));
                                      addchild($$, aux); }
    ;

/* === CORPO DE MÉTODO === */
MethodBody: LBRACE StmtOrVarList RBRACE
                                    {   $$ = $2;
                                        }
    ;

StmtOrVarList: StmtOrVarList Statement
                                    { $$ = $1;
                                      if( $2 != NULL) addchild($$, $2); }

             | StmtOrVarList VarDecl
                                    {    $$ = $1;
                                        struct node *aux = $2;
                                        int type = 9;
                                         if( (aux != NULL) && (aux->children != NULL) && (aux->children->node != NULL) ) type = aux->children->node->category; // nodes type
                                        if(type != 9){ // Not Dummy
                                            struct node_list *childrenList = aux->children->next;
                                            while ((childrenList != NULL) ) {
                                                if (childrenList->node != NULL) {
                                                    struct node *parent = newnode(VarDecl, NULL);
                                                    struct node *newtype = newnode(type, NULL);
                                                    struct node *newNode = newnode(childrenList->node->category, childrenList->node->token);
                                                    
                                                    addchild(parent, newtype);
                                                    addchild(parent, newNode);
                                                    addchild($$, parent);
                                                }
                                                childrenList = childrenList->next;
                                            }
                                        }
                                    }
             | /* vazio */          { $$ = newnode(MethodBody, NULL);
                                        }
    ;

VarDecl: Type IdentListVar SEMICOLON   {    $$ = $2;
                                            addFront($$, $1);
                                        
                                        }
    ;

/* === STATEMENTS === */
Statement: LBRACE StmtList RBRACE   { 
                                      struct node_list *children = $2->children;
                                      int count = 0;
                                      struct node_list *cur = children;
                                      while(cur != NULL) { count++; cur = cur->next; }

                                      if(count == 1 ) {
                                          $$ = children->node; /* passa o filho diretamente */
                                      } else {
                                          $$ = $2; /* 0 ou 2+ filhos, mantém o Block */
                                      }
                                    }

         | IfStmt                   {   $$ = $1; }

         | SEMICOLON                {   $$ = NULL;
                                         } 

         | WHILE LPAR Expr RPAR Statement
                                    {   $$ = newnode(While, NULL); 
                                        addchild($$, $3); 
                                        if($5 != NULL) addchild($$, $5);
                                        else addchild($$, newnode(Block, NULL) );
                                        }
         | RETURN ExprOpt SEMICOLON {   $$ = newnode(Return, NULL); 
                                        if($2 != NULL) addchild($$, $2); 
                                        }
         | ExprStmt SEMICOLON       {   $$ = $1 ; }

         | PRINT LPAR Expr RPAR SEMICOLON
                                    {   $$ = newnode(Print, NULL); 
                                        addchild($$, $3); 
                                        }
         | PRINT LPAR STRLIT RPAR SEMICOLON
                                    {   $$ = newnode(Print, NULL); 
                                        addchild($$, newnode(StrLit, $3) ); 
                                        }
          | error SEMICOLON         { $$ = newnode(Dummy, NULL) ;}
    ;

StmtList: StmtList Statement        { $$ = $1;
                                      if($2 != NULL) addchild($$, $2); }
        | /* vazio */               { $$ = newnode(Block, NULL); }
    ;


IfStmt: IF LPAR Expr RPAR Statement ELSE Statement
                                    {
                                        $$ = newnode(If, NULL);
                                        addchild($$, $3);
                                        if($5 != NULL) addchild($$, $5);
                                        else addchild($$, newnode(Block, NULL) );
                                        if($7 != NULL) addchild($$, $7);
                                        else addchild($$, newnode(Block, NULL) );
                                    }
        | IF LPAR Expr RPAR Statement  %prec WITHOUT_ELSE
                                    {
                                        $$ = newnode(If, NULL);
                                        addchild($$, $3);
                                        if($5 != NULL) addchild($$, $5);
                                        else addchild($$, newnode(Block, NULL) );
                                        addchild($$, newnode(Block, NULL) );
                                    }
    ;


ExprOpt: Expr                       {   $$ = $1 ; 
                                        }
       | /* vazio */                {   $$ = NULL;
                                        }
    ;

ExprStmt: IDENTIFIER LPAR ArgListOpt RPAR
                                    {   $$ = newnode(Call, NULL) ;
                                        addchild($$, newnode(Identifier, $1) );
                                       if($3 != NULL) addchild($$, $3);
                                    }
        | IDENTIFIER LPAR error RPAR { $$ = newnode(Dummy, NULL); }
        | IDENTIFIER ASSIGN Expr    {   $$ = newnode(Assign, NULL);
                                        addchild($$, newnode(Identifier, $1) );
                                        addchild($$, $3);
                                        }
        | PARSEINT LPAR IDENTIFIER LSQ Expr RSQ RPAR
                                    {   $$ = newnode(ParseArgs, NULL);
                                        addchild($$, newnode(Identifier, $3) );
                                        addchild($$, $5 );
                                        }

        | PARSEINT LPAR error RPAR  { $$ = newnode(Dummy, NULL); }
    ;

/* === EXPRESSÕES === */
Expr: AssignExpr                    {   $$ = $1 ;
                                        }
          |  LPAR error RPAR               { $$ = newnode(Dummy, NULL); }
    ;

AssignExpr: IDENTIFIER ASSIGN AssignExpr
                                    {   $$ = newnode(Assign, NULL); 
                                        addchild($$, newnode(Identifier, $1) ); 
                                        addchild($$, $3);
                                        }
          | OrExpr                  {   $$ = $1;}
    ;

OrExpr: OrExpr OR AndExpr           {   $$ = newnode(Or, NULL); 
                                        addchild($$, $1);
                                        addchild($$, $3);
                                        }
      | AndExpr                     {   $$ = $1; }
    ;

AndExpr: AndExpr AND XorExpr        {   $$ = newnode(And, NULL); 
                                        addchild($$, $1);
                                        addchild($$, $3);
                                        }
       | XorExpr                    {   $$ = $1; }
    ;

XorExpr: XorExpr XOR EqExpr         {   $$ = newnode(Xor, NULL); 
                                        addchild($$, $1);
                                        addchild($$, $3);
                                        }
       | EqExpr                     {   $$ = $1; }
    ;

EqExpr: EqExpr EQ RelExpr           {   $$ = newnode(Eq, NULL) ;
                                        addchild($$, $1);
                                        addchild($$, $3);
                                        }
      | EqExpr NE RelExpr           {   $$ = newnode(Ne, NULL) ;
                                        addchild($$, $1);
                                        addchild($$, $3);
                                        }
      | RelExpr                     {   $$ = $1; }
    ;

RelExpr: RelExpr LT ShiftExpr       {   $$ = newnode(Lt, NULL) ;
                                        addchild($$, $1);
                                        addchild($$, $3);
                                        }
       | RelExpr LE ShiftExpr       {   $$ = newnode(Le, NULL) ;
                                        addchild($$, $1);
                                        addchild($$, $3);
                                        }
       | RelExpr GT ShiftExpr       {   $$ = newnode(Gt, NULL) ;
                                        addchild($$, $1);
                                        addchild($$, $3);
                                        }
       | RelExpr GE ShiftExpr       {   $$ = newnode(Ge, NULL) ;
                                        addchild($$, $1);
                                        addchild($$, $3);
                                        }
       | ShiftExpr                  {   $$ = $1;
                                        }
    ;

ShiftExpr: ShiftExpr LSHIFT AddExpr {   $$ = newnode(Lshift, NULL) ;
                                        addchild($$, $1);
                                        addchild($$, $3);
                                        }
         | ShiftExpr RSHIFT AddExpr {   $$ = newnode(Rshift, NULL) ;
                                        addchild($$, $1);
                                        addchild($$, $3);
                                        }
         | AddExpr                  {   $$ = $1; }
    ;

AddExpr: AddExpr PLUS MulExpr       {   $$ = newnode(Add, NULL) ;
                                        addchild($$, $1);
                                        addchild($$, $3);
                                        }
       | AddExpr MINUS MulExpr      {  $$ = newnode(Sub, NULL) ;
                                        addchild($$, $1);
                                        addchild($$, $3);
                                        }
       | MulExpr                    {   $$ = $1 ;
                                        }
    ;

MulExpr: MulExpr STAR UnaryExpr     {   $$ = newnode(Mul, NULL) ;
                                        addchild($$, $1);
                                        addchild($$, $3);
                                        }
       | MulExpr DIV UnaryExpr      {   $$ = newnode(Div, NULL) ;
                                        addchild($$, $1);
                                        addchild($$, $3);
                                        }
       | MulExpr MOD UnaryExpr      {   $$ = newnode(Mod, NULL) ;
                                        addchild($$, $1);
                                        addchild($$, $3);
                                        }
       | UnaryExpr                  {   $$ = $1; 
                                        }
    ;

UnaryExpr: MINUS UnaryExpr          {   $$ = newnode(Minus, NULL);
                                        addchild($$, $2); 
                                        }
         | NOT UnaryExpr            {   $$ = newnode(Not, NULL);
                                        addchild($$, $2); 
                                        }
         | PLUS UnaryExpr           {   $$ = newnode(Plus, NULL);
                                        addchild($$, $2); 
                                        }
         | PostfixExpr              {   $$ = $1; }
    ;

PostfixExpr: IDENTIFIER DOTLENGTH   {   $$ = newnode(Length, NULL) ;
                                        addchild($$, newnode(Identifier, $1) );
                                        }
           | IDENTIFIER LPAR ArgListOpt RPAR
                                    {   $$ = newnode(Call, NULL);
                                        addchild($$, newnode(Identifier, $1) ); 
                                        if($3 != NULL) addchild($$, $3);
                                        }

           | IDENTIFIER LPAR error RPAR { $$ = newnode(Dummy, NULL); }
            
           | PARSEINT LPAR IDENTIFIER LSQ Expr RSQ RPAR
                                    {   $$ = newnode(ParseArgs, NULL);
                                        addchild($$, newnode(Identifier, $3) );
                                        addchild($$, $5 );
                                        }
           | PARSEINT LPAR error RPAR
                                    { $$ = newnode(Dummy, NULL); }

           | LPAR Expr RPAR         {   $$ = $2; }
           
           | IDENTIFIER             {   $$ = newnode(Identifier, $1); }
           | NATURAL                {   $$ = newnode(Natural, $1); }
           | DECIMAL                {   $$ = newnode(Decimal, $1); }
           | BOOLLIT                {   $$ = newnode(BoolLit, $1); }
    ;

/* === ARGUMENTOS === */
ArgListOpt: ArgList                 {   $$ = $1; }
          | /* vazio */             {   $$ =NULL; }
    ;

ArgList: Expr                       { $$ = newnode(Args, NULL);
                                      addchild($$, $1); }
       | ArgList COMMA Expr         { $$ = $1;
                                      addchild($$, $3); }
    ;

%%