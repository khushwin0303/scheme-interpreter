#include "listFunctions.h"
#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// all functions
ListCell car(ListCell cell) {
	if (cell->car != NULL) return cell->car;
	else {
		return NULL;
	}
}

ListCell cdr(ListCell cell) {
	if (cell->cdr != NULL) return cell->cdr;
	else {
    if (isSymbol(cell)) return NULL;
		else if (isEmptyList(cell)) return NULL;
		else return createListCell();
	}
}	

ListCell quote(ListCell cell) {
	return car(cdr(cell));
}

ListCell symbol(ListCell cell) {
	ListCell x = createListCell();
	if (isSymbol(cell)) {
		x = putSymbol(x, "#t");
	}
	else {
		x = putSymbol(x, "#f");
	}
	return x;	
}

ListCell isList(ListCell cell) {
	ListCell x = createListCell();
	if (!isSymbol(cell)) {
		x = putSymbol(x, "#t");
	}
	else {
		x = putSymbol(x, "#f");
	}
	return x;	
}


// should modify it into two cells for arguments. It's easy.
ListCell cons(ListCell cell1, ListCell cell2) {


	// create the list to be returned
	ListCell ret = createListCell();

	ret = firstElement(ret, cell1);
  ret = restElement(ret, cell2);


	return ret;
	
}

ListCell firstElement(ListCell list, ListCell element) {
	// first element to return
	list->car = element;
	return list;
}

ListCell restElement(ListCell list, ListCell element) {
	// I added that to get a proper output
	// I noticed that in DrRacket the output would be
  // e.g (cons (quote (a b)) (quote c)) = ((a b). c)
  // with this output will be ((a b))
	if (isSymbol(element)) {
		list->cdr = NULL;
	}
	// if is empty list.
	else if (isEmptyList(element)) {
    return list;
	}
	else list->cdr = element;
  return list;
}


ListCell append(ListCell list1, ListCell list2) {
	return appendHelper(list1, list2);	
}

ListCell appendHelper(ListCell list1, ListCell list2){
  // printf("Doing checks\n");
  if (list1 != NULL) {
		if (isEmptyList(list1)) {
			return list2;
		}
		else {
		//  printf("car is evaluated\n");
			ListCell first = car(list1);
		 // printf("cdr is evaluated\n");
			ListCell rest = cdr(list1);
			return cons(first, appendHelper(rest, list2));
  	}
	}
  else {
		return list2;
	}
}

ListCell null(ListCell cell) {
  if (isEmptyList(cell)) {
		return True();
	}
	else {
		return False();
	}
}

ListCell equal(ListCell list1, ListCell list2) {
	// base cases
	// if both empty
	if (isEmptyList(list1) && isEmptyList(list2)) return True();
	// if both are symbols
	else if (isSymbol(list1) && isSymbol(list2)) {
		if (!strcmp(list1->symbol, list2->symbol)) return True();
		else return False();
	}
	// if both are lists
  else {
		// identify the first elements and the rests of both lists;
		ListCell first1 = car(list1);
  	ListCell first2 = car(list2);
    ListCell rest1 = cdr(list1);
  	ListCell rest2 = cdr(list2);
		// if one of the first is NULL return False
		if (first1 == NULL || first2 == NULL) {
			return False();
		}
		else {
				// if both the rests are null recur on the firsts;
				if ((rest1 == NULL) && (rest2 == NULL)) return equal(first1, first2);
				// if both are not null, we should recur on both the firsts and the 				//	rests
				else {
				// check if the firsts are equal
				ListCell cmp = equal(first1, first2);
				if(!strcmp(cmp->symbol, "#f")) return False();
				else {
					// both might be equal, but we don't know about the rests
					return equal(rest1, rest2);
				}
			}
		}
	}
}

int equalInt(ListCell list1, ListCell list2) {
	ListCell temp = equal(list1, list2);
  char* sym;
  sym =  (char *) malloc(sizeof(temp->symbol));
	strcpy(sym, temp->symbol);
	if (!strcmp(sym, "#t")) return 1;
	else return 0;
}

ListCell cond(ListCell args, ListCell env) {
	ListCell pair = car(args);
	ListCell condition = car(pair);
	ListCell evalCondition = evalHelper(condition, env); 
  if (!strcmp(evalCondition->symbol, "#t") || !strcmp(evalCondition->symbol, "else")) {
		return evalHelper(car(cdr(pair)), env);
	}
	else return cond(cdr(args), env);
}


ListCell assoc(ListCell key, ListCell list) {
	if (equalInt(null(list), True())) return False();
	else if (equalInt(key, car(car(list)))) return car(list);
	else {
		return assoc(key, cdr(list));
	}
}
