/* write a calculator program that provides the operators +, -, and /. Because
 * it is easier to implement, the calculator will use reverse Polish notation
 * instead of infix. */

#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "math.h"
#include "stdlib.h"

#define MAX 100     // max length of operators

enum TYPE {NONE, NUMBER, SIN, EXP, POW};    // flags

int getop(char s[]);
void push(double op);
double pop(void);
void clrstk(void);
int getch(void);
void ungetch(int c);
void strsqz(char s[], size_t dist);


int main(void) {
	int type;
	char s[MAX], varflag[26];
	double op, op0, varval[26];
	size_t i;

	// zero varflag
	for (i = 0; i < 26; i++)
		varflag[i] = 0;

	while ((type=getop(s)) != EOF) {
		switch (type) {
			case NONE:
				printf("Error: wrong operators\n");
				return 0;
			case NUMBER:
				push(atof(s));
				break;
			case SIN:
				push(sin(pop()));
				break;
			case EXP:
				push(exp(pop()));
				break;
			case POW:
				op = pop();
				push(pow(op, pop()));
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
				if (op == 0)
					printf("Error: zero divisor.\n");
				else
					push(pop() / op);
				break;
			case '%':
				op = pop();
				if (op == 0)
					printf("Error: zero divisor.\n");
				else
					push((int)pop() % (int)op);
				break;
			case '=':
				op = pop();
				if (!(op >= 'a' && op <= 'z')) {
					printf("error: use a variable before defining\n");
					return 0;
				}
				varval[(char)op - 'a'] = pop();
				break;
			case 't':   // print the top element of the stack
				printf("top element of the stack: %g\n", pop());
				return 0;
			case 'd':   // duplicate the top element of the stack
				op = pop();
				push(op);
				push(op);
				break;
			case 's':   // swap the top 2 elements of the stack
				op = pop();
				op0 = pop();
				push(op);
				push(op0);
				break;
			case 'c':   // clear operator stack
				clrstk();
				break;
			case 'v':
				if (strlen(s) == 1 && s[0] >= 'a' && s[0] <= 'z') {
					if (varflag[s[0] - 'a'] == 0) {
						varflag[s[0] - 'a'] = 1;
						push(s[0]);
					} else
						push(varval[s[0] - 'a']);
				} else {
					printf("invalid variable\n");
					return 0;
				}
				break;
			case '\n':
				printf("result: %g\n", pop());
				return 0;
			default:
				printf("Error: abnormal operators.\n");
				return 0;
		}
	}

	return 0;
}


/* get operations */
int getop(char s[]) {
	size_t i;
	char c;

	// skip blanks
	for (i = 0; isblank(s[i] = c = getch());)
		;

	// the character after '\n' is unclear, so return in advance.
	if (c == '\n')
		return '\n';

	// get non-blank characters
	for (i++; !isblank(s[i] = c = getch()) && c!='\n'; i++)
		;

	// only for the situation "<some character>\n\000"
	ungetch(s[i]);
	s[i] = '\0';

	// usage of variables: 'value v+<one lowercase> ='
	// example: 2 va = 5 vb = va vb *
	if (isdigit(s[0]))
		return NUMBER;
	else if (strcmp(s, "sin") == 0 || strcmp(s, "SIN") == 0)
		return SIN;
	else if (strcmp(s, "exp") == 0 || strcmp(s, "EXP") == 0)
		return EXP;
	else if (strcmp(s, "pow") == 0 || strcmp(s, "POW") == 0)
		return POW;
	else if (s[0]=='v' && strlen(s)>1) {
		strsqz(s, 1);
		return 'v';
	} else if (strlen(s) == 1)
		return s[0];
	else
		return NONE;
}


/* push operators */
double stack[MAX];
size_t sh;

void push(double op) {
	if (sh < MAX)
		stack[sh++] = op;
	else
		printf("No more space to store.\n");
}


/* pop operators */
double pop(void) {
	if (sh > 0)
		return stack[--sh];
	else
		printf("Stack is empty.\n");
	return 0;
}


/* clear stack */
void clrstk(void) {
	sh = 0;
}

/* `getch`与`ungetch`函数对实质上是带有缓存的文本流处理工具 */
int buffer[MAX];
size_t bh;

int getch(void) {
	return bh > 0 ? buffer[--bh] : getchar();
}


void ungetch(int c) {
	buffer[bh++] = c;
}


/* squeeze a string */
void strsqz(char s[], size_t dist) {
	size_t i;

	for (i = dist; s[i] != '\0'; i++)
		s[i-dist] = s[i];
	s[i] = '\0';
}
