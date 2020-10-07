/* Exercise 5-10. Write the program expr, which evaluates a reverse Polish
 * expression from the command line, where each operator or operand is a
 * separate argument. For example,
 * expr 2 3 4 + *
 * evaluates 2 * (3+4).
 *
 * Note: operator * should be type as '*' or \* in command-line
 * */

#include "stdio.h"
#include "ctype.h"
#include "stdlib.h"

#define ERRMSG_STK  "stk is full\n"
#define ERRMSG_OP   "invalid operator\n"
#define ERRMSG_0DIV "zero divisor\n"
#define perr(errtype) printf("error: " errtype)
enum ERR {ERROR_OP = 1, ERROR_STK, ERROR_0DIV};

char push(double n);
double pop(void);

int main(int argc, char *argv[]) {
	const char *usage = "usage: expr EXPRESSION\n"
    "valid operators: + - * /\n"
    "i.e.\n"
	"\texpr 2 3 + 6 *, which evaluates 6 * (2 + 3)\n";
	double temp_op;

	if (argc == 1) {
		printf("%s", usage);
		return 0;
	}

	while (argc-- > 1) {
		if (isdigit(**++argv)) {
			if (!push(atof(*argv))) {
				perr(ERRMSG_STK);
				return ERROR_STK;
			}
		} else
			switch (**argv) {
				case '+':
					if (!push(pop() + pop())) {
						perr(ERRMSG_STK);
						return ERROR_STK;
					}
					break;
				case '-':
					temp_op = pop();
					if (!push(pop() - temp_op)) {
						perr(ERRMSG_STK);
						return ERROR_STK;
					}
					break;
				case '*':
					if (!push(pop() * pop())) {
						perr(ERRMSG_STK);
						return ERROR_STK;
					}
					break;
				case '/':
					if (!(temp_op = pop())) {
						perr(ERRMSG_0DIV);
						return ERROR_0DIV;
					}
					if (!push(pop() / temp_op)) {
						perr(ERRMSG_STK);
						return ERROR_STK;
					}
					break;
				default:
					perr(ERRMSG_OP);
					return ERROR_OP;
			}
	}
	printf("%g\n", pop());
	return 0;
}

#define STKSIZE 100
static double stack[STKSIZE];
static int stkp;

char push(double n) {
	if (stkp < STKSIZE) {
		stack[stkp++] = n;
		return 1;
	}
	return 0;   // stack if full
}

double pop(void) {
	if (stkp > 0)
		return stack[--stkp];
	return 0;
}
