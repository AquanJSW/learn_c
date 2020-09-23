#include "stdio.h"

#define STKSIZE 100

double stack[STKSIZE];
size_t stkp;    // stack's top position

double pop(void) {
	if (stkp > 0)
		return stack[--stkp];
	printf("error: empty stack\n");
	return 0;
}

char push(double d) {
	if (stkp < STKSIZE) {
		stack[stkp++] = d;
		return 1;   // success
	}
	printf("error: no more space in stack\n");
	return 0;   // failed
}
