#include "parser.h"
#include "listFunctions.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*************

<s_expression> ⟶ ( { <s_expression> } ) | #t | #f | <symbol> | ()

*************/

ListCell refEnvi;


void init() {
	refEnvi = createListCell();
}


S_Exp createS_Exp() {
	S_Exp S_exp = (S_Exp) malloc(sizeof(struct s_exp));
	
	if (S_exp == NULL) { 
		printf("Out of memory!\n");
		exit(1);
	} 
	
	S_exp->head = NULL;
	
	return S_exp;
}


// Creates an empty ConsCEll
ListCell createListCell() {
	ListCell cell = (ListCell) malloc(sizeof(struct consCell));
	if (cell == NULL) { 
		printf("Out of memory!\n");
		exit(1);
	} 
	cell->symbol = NULL;
    cell->car = NULL;
	cell->cdr = NULL;
    return cell;
}

ListCell True() {
	ListCell cell = (ListCell) malloc(sizeof(struct consCell));
	if (cell == NULL) { 
		printf("Out of memory!\n");
		exit(1);
	} 
	cell->symbol = "#t";
  cell->car = NULL;
	cell->cdr = NULL;
  return cell;
}

ListCell False() {
	ListCell cell = (ListCell) malloc(sizeof(struct consCell));
	if (cell == NULL) { 
		printf("Out of memory!\n");
		exit(1);
	} 
	cell->symbol = "#f";
  cell->car = NULL;
	cell->cdr = NULL;
  return cell;
}

ListCell putSymbol(ListCell cell, char* sym) {
	cell->symbol = (char *) malloc(sizeof(sym));
	strcpy(cell->symbol, sym);
	cell->car = NULL;
    cell->cdr = NULL;
    return cell;
}

ListCell S_Expression(int level) {
	ListCell local, temp;
	if (!strcmp(token, "(")) {
		// create a consCell
		local = createListCell();
		// move one level up
		// get next token
		strcpy(token, getToken());
		// recursive for car.
		local->car = S_Expression(level+1);
		temp = local;
		while (strcmp(token, ")")) {
			// allocate a new cell to cdr
			temp->cdr = createListCell();
			// make temp equal to to that new cell
			temp = temp->cdr;
			temp->car = S_Expression(level+1);   
		}
		// once we get out of the list, cdr remains null
		temp->cdr = NULL;
		if (level != 0) {
			strcpy(token, getToken());
		}
		// return local because the links have been made by temp
		return local;
	}
	else if (!strcmp(token, "()")) {  // case ()
		local = createListCell();
		if (level != 0) {
			strcpy(token, getToken());
		}
		return local;
	}
  else if(!strcmp(token, "#t")) {
		local = createListCell();
		local = putSymbol(local, token); 
		if (level != 0) {
				strcpy(token, getToken());
		}
		return local;
  }
  else if(!strcmp(token, "#f")) {
		local = createListCell();
		local = putSymbol(local, token); 
		if (level != 0) {
				strcpy(token, getToken());
		}
		return local;
  }
	else if (!strcmp(token, "\'")) {
		// create empty list;
		local = createListCell();
		// put the quote symbol in car
		local->car = createListCell();
		local->car = putSymbol(local->car,"quote");
		//make the rest of the list with temp
		temp = local;
		// cdr is null at first
		temp->cdr = createListCell();
		// make temp point to its cdr
		temp = temp->cdr;
		strcpy(token, getToken());
		// a new list or symbol will be at it's car
		temp->car = S_Expression(level);
		return local;
	}
  else {
		local = createListCell();
			local = putSymbol(local, token); 
			if (level != 0) {
				strcpy(token, getToken());
			}
			return local;
	}
}

void printSExp(S_Exp s_expression) {
	print(s_expression->head, 1);
	printf("\n");
}		

void print(ListCell cell, int startOfList) {
	// if symbol, car, and cdr are empty, then print "()"
	if (isEmptyList(cell)) {
		printf("%s", "()");
	}
	// else cell is not empty
    else {
		// if it is a symbol
		if (isSymbol(cell)) {
			printf(" %s ", cell->symbol);
		}
		else {
			if(startOfList) {
				printf("%s", "(");
			}
			// even if the car is a symbol, it will print it and not "("
			// however, if the car is another list, then it would mean that
			// car is not a symbol and will hence print "("
			print(cell->car, 1);
			// if cdr is null, then we reached end of list
			if (cell->cdr == NULL) {
				printf("%s", ")");
			}
			else {
				// else now we have to print either a symbol, empty list or a
				// list.
				// startOfList is set to zero because it can be anything
				// printf("%s", " ");
				print(cell->cdr, 0);
			}
		}
	}	
}


int isSymbol(ListCell cell) {
	if (cell->symbol != NULL) {
		return 1;
	}
	else {
		return 0;
	}
}


int isEmptyList(ListCell cell){
	// the symbol, the car, and the cdr should be empty
  // printf("doing checks in isEmptyList Function\n");
	if ((cell->symbol == NULL) && (cell->car == NULL) && 
		(cell->cdr==NULL)) {
		return 1;
	}
	else {
		return 0;
	}
}

// all functions
/*
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
}*/

void addToRefEnvi(ListCell symName, ListCell value) {
	//evaluate the value
	// cons evalVal with empty list to create that format
	// (symName (evalVal))
  ListCell evalCons = cons(symName, cons(value, createListCell()));
	refEnvi = cons(evalCons, refEnvi);
	
}

ListCell augEnv(ListCell actParameters, ListCell funcParameters,
								ListCell env) {

	ListCell augEnvironment = createListCell();
	// initialize environment
	// no parameters, then functions should be executable
	if (funcParameters == NULL) {
		return env;
	}

		
	while (funcParameters != NULL && actParameters != NULL) {
		ListCell key = car(funcParameters);
		ListCell value = evalHelper(car(actParameters), env);
		ListCell evalCons = cons(key, cons(value, createListCell()));
		augEnvironment = cons(evalCons, augEnvironment);
		funcParameters = funcParameters->cdr;
		actParameters = actParameters->cdr;
	}
	return augEnvironment;
}

S_Exp eval(S_Exp s_exp) {
  ListCell temp = s_exp->head;
	s_exp->head = createListCell();
	ListCell x = evalHelper(temp, refEnvi);
	s_exp->head = x;
	return s_exp;
}

ListCell evalHelper(ListCell list, ListCell env) {
	ListCell current = list;
	// if it an empty list
	if(isEmptyList(list)) return list;
  
	// if it is a list
	if (car(list) != NULL && isSymbol(car(list))) {
		ListCell command = car(list);
		char *sym;
		sym =  (char *) malloc(sizeof(command->symbol));
		strcpy(sym, command->symbol);
		if (!strcmp(sym, "exit")) {
			printf("Have a nice day!\n");
			exit(0);
		}
		if (list->cdr == NULL) {
			return list;
		}
		ListCell toEval;
		if (!strcmp(sym, "car")){
			toEval = evalHelper(car(cdr(list)), env);
			return car(toEval);
		}
		else if (!strcmp(sym, "cdr")){
			toEval = evalHelper(car(cdr(list)), env);
			return cdr(toEval);
		}
		else if (!strcmp(sym, "quote")){
			return quote(current);
		}
		else if (!strcmp(sym, "symbol?")){
			toEval = evalHelper(car(cdr(list)), env);
			return symbol(toEval);
		}
		else if (!strcmp(sym, "list?")) {
			toEval = evalHelper(car(cdr(list)), env);
			return isList(toEval);
		}
		else if (!strcmp(sym, "function?")) {
			toEval = car(cdr(list));
			ListCell checkFunc = assoc(toEval, refEnvi);
			if (equalInt(checkFunc, False())) {
				return False();
			}
			else return True();
		}
		else if (!strcmp(sym, "cons")){
			// find its car first
			ListCell list1 = evalHelper(car(cdr(list)), env);
			// find the next list to be added
			ListCell list2 = evalHelper(car(cdr(cdr(list))), env);
			return cons(list1, list2);
		}
		else if (!strcmp(sym, "append")){
			// find its car of the next first
			ListCell list1 = evalHelper(car(cdr(list)), env);
			// find the next list to be added
			ListCell list2 = evalHelper(car(cdr(cdr(list))), env);
			return append(list1, list2);
		}
		else if (!strcmp(sym, "null?")){
			ListCell evalNull = evalHelper(car(cdr(list)), env);
		  return null(evalNull);
		}
		else if (!strcmp(sym, "equal?")){
			// find its car of the next first
			ListCell list1 = evalHelper(car(cdr(list)), env);
			// find the next list to be added
      ListCell list2 = evalHelper(car(cdr(cdr(list))), env);
			
			return equal(list1, list2);
		}
		else if (!strcmp(sym, "cond")){
			// find its args
			ListCell args = cdr(list);
			return cond(args, env);
		}
		else if (!strcmp(sym, "assoc")){
			// find its key
			ListCell key = car(cdr(list));
			ListCell alist = car(cdr(cdr(list)));
      ListCell evalKey = evalHelper(key, env);
      ListCell evalAlist = evalHelper(alist, env);
			return assoc(evalKey, evalAlist);
		}
		else if (!strcmp(sym, "define")){
			// find its key
			ListCell symName = car(cdr(list));
      // if the key is a symbol
			// add to localEnv
      if (isSymbol(symName)) {
				ListCell value = evalHelper(car(cdr(cdr(list))), env);
				printf("value is: ");
				print(value, 1);
				printf("\n");
				addToRefEnvi(symName, value);
				return symName;
			}
			else {
				addToRefEnvi(car(symName), list);
				return car(symName); 
			}
		}
		else {
			ListCell command = car(list);
      // env might be replaced by refEnvi not sur tho
			ListCell checkFunc = assoc(command, refEnvi);
			if (equalInt(checkFunc, False())) {
				return list;
			}
			else {
				// we need to build augmented environment
				// find actual-parameters
				ListCell actParameters = cdr(list);
				// find func parameters
			  ListCell funcParameters = cdr(car(cdr(car(cdr(checkFunc)))));
				// find function-body
				ListCell funcBody = car(cdr(cdr(car(cdr(checkFunc)))));
			  ListCell aug = augEnv(actParameters, funcParameters, env);
				// runEvalHelper again with the new augmented environment
				return evalHelper(funcBody, aug);
			}
		}
	}
  // if it is a symbol
	else {
		ListCell checkSym = assoc(list, env);
		if (equalInt(checkSym, False())) {
			return list;
		}
		else return car(cdr(checkSym));
	}
}
