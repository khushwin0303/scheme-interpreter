#ifndef LISTFUNCTIONS
#define LISTFUNCTIONS
#include <stdlib.h>
#include "parser.h"

/*get the first element of a list*/
ListCell car(ListCell);

/*get the rest of the elements of a list*/
ListCell cdr(ListCell);

/*output every element of a list*/
ListCell quote(ListCell);

/*check if the consCell structure is a symbol*/
ListCell symbol(ListCell);

/*check if the consCell structure is a symbol*/
ListCell isList(ListCell);

/*do the cons function on scheme*/
ListCell cons(ListCell, ListCell);

/*do the append function on scheme*/
ListCell append(ListCell, ListCell);

/*Helper function for append*/
ListCell appendHelper(ListCell, ListCell);

/*check if the consCell is null*/
ListCell null(ListCell);

/*check if two lists or symbols are equal*/
ListCell equal(ListCell, ListCell);

/*it does the equal function but returns a number instead, 1 if equal and 0 if not*/
int equalInt(ListCell, ListCell);

/*do the cond function on scheme*/
ListCell cond(ListCell, ListCell);

/*do the assoc function on scheme*/
ListCell assoc(ListCell, ListCell);

/*place a new element at the start of an existing list, with the first parameter being the element and the second one being the list. It works with cons*/
ListCell firstElement(ListCell, ListCell);

/*place a new element at the "cdr" of an existing list, with the first parameter being the element and the second one being the list. It works with cons*/
ListCell restElement(ListCell, ListCell);

#endif
