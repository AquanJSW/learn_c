/* Exercise 4-10. An alternate organization uses getline to read an entire input
 * line; this makes getch and ungetch unnecessary. Revise the calculator to use
 * this approach. */

#include "stdio.h"
#include "stdlib.h"
#include "calc.h"

#define LINELEN 1000

int main(void) {
	char s[LINELEN];
	char d[LINELEN];
	unsigned char type;
	double op;

	while (getline_(s, LINELEN) > 0) {
		while ((type = getop(s, d)) != END) {
			switch (type) {
				case NUM:
					push(atof(d));
					break;
				case '+':
					push(pop() + pop());
					break;
				case '-':
					op = pop();
					push(pop() - op);
					break;
				case '*':
					push(pop() * pop());
					break;
				case '/':
					op = pop();
					if (op) {
						push(pop() / op);
						break;
					}
					printf("error: zero divisor\n");
					break;
				default:
					printf("error: unclear operator\n");
					break;
			}
			if (type == NONE || (type == '/' && op == 0))
				break;
		}
		printf("%g\n", pop());
	}
}
