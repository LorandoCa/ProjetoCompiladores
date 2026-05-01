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
    BoolLit,
    Decimal,
    Natural,
    StrLit,
    Identifier,
};

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_BOOL,
    TYPE_VOID,
    TYPE_STRING_ARRAY,
    TYPE_UNDEF,
    TYPE_CLASS, // auxiliar para ignorar o tipo de class
    TYPE_DECL, // auxiliar para ignorar o tipo de class
    TYPE_NULL, // aux
    
} sem_type;

// "int", "double", "boolean", "void", "String[]", "undef"
#define type_name(t) ( \
    (t) == TYPE_INT          ? "int"       : \
    (t) == TYPE_DOUBLE       ? "double"    : \
    (t) == TYPE_BOOL         ? "boolean"   : \
    (t) == TYPE_VOID         ? "void"      : \
    (t) == TYPE_STRING_ARRAY ? "String[]"  : \
                               "undef"       \
)

// Converte category da AST para tipo semântico
#define category_to_type(c) ( \
    (c) == Int         ? TYPE_INT          : \
    (c) == Double      ? TYPE_DOUBLE       : \
    (c) == Bool        ? TYPE_BOOL         : \
    (c) == Void        ? TYPE_VOID         : \
    (c) == StringArray ? TYPE_STRING_ARRAY : \
                         TYPE_UNDEF          \
)

// Converte category de um NÓ DE EXPRESSÃO (literais, identificadores anotados, etc.)
#define expr_category_to_type(c) ( \
    (c) == Natural     ? TYPE_INT          : \
    (c) == Decimal     ? TYPE_DOUBLE       : \
    (c) == BoolLit     ? TYPE_BOOL         : \
    (c) == Int         ? TYPE_INT          : \
    (c) == Double      ? TYPE_DOUBLE       : \
    (c) == Bool        ? TYPE_BOOL         : \
    (c) == Void        ? TYPE_VOID         : \
    (c) == StringArray ? TYPE_STRING_ARRAY : \
                         TYPE_UNDEF          \
)


struct node {
    enum category category;
    char *token;
    char *args;
    sem_type type;
    int line;    
    int column; 
    int visit; // flag used to mark a method as a duplicated method
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
int is_operation(enum category c);
int ignore(sem_type c);
int ignoreOp(enum category c);
#endif