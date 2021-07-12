#ifndef PARSER
#define PARSER
#include <stdlib.h>
#include "lexer.h"

/* Create consCell */
struct consCell {
	char* symbol;
    struct consCell* car;
	struct consCell* cdr;	
};
/* Use this to initialize a variable of type ListCell*/
/* e.g ListCell x; */
typedef struct consCell *ListCell;
struct s_exp {
	ListCell head;
};
typedef struct s_exp *S_Exp;

/*creates a new S_Exp*/
S_Exp createS_Exp(void);

/*Create a new ListCell with all items Null*/
ListCell createListCell(void);
/* Build the list of ListCell structure */
ListCell S_Expression (int);
/*creates a referencing environment, empty at first*/
void init(void);
/* Build printSExp with an SExp as a variable */
void printSExp(S_Exp);
/*Helper function of printSExp*/
void print(ListCell, int);

/*insert symbol in a cell*/
ListCell putSymbol(ListCell, char*);

/*check if ListCell is a symbol. Return 1 if true, else return 0*/
int isSymbol(ListCell);
/*check if ListCell is empty. Return 1 if true, else return 0*/
int isEmptyList(ListCell);

/*global variable to store the tokens*/
char token[20];

/*A consCell symbol containing #t*/
ListCell True();

/*A consCell symbol containing #f*/
ListCell False();

/*add symbols and functions definitions to global referencing envrionment*/
void addToRefEnvi(ListCell, ListCell);

/*build the augmented environment for pre-defined functions*/
ListCell augEnv(ListCell, ListCell, ListCell);


/*evaluate scheme code*/
S_Exp eval(S_Exp);

/*function helper of eval, takes function as first argument and referencing environment as second environment*/
ListCell evalHelper(ListCell, ListCell);
#endif
