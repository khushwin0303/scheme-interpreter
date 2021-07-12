#include <stdio.h>
#include "parser.h"
#include <string.h>

int main() {
    init();
    while (1) {
		startTokens(20);
		strcpy(token, getToken());
		S_Exp s_expression = createS_Exp();
		s_expression->head = S_Expression(0);
		printf("scheme> ");
		printSExp(eval(s_expression));
	}
}
