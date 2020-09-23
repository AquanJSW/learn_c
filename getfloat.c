/* Exercise 5-2. Write getfloat, the floating-point analog of getfloat. What type
 * does getfloat return as its function value? */

#include "stdio.h"
#include "ctype.h"
#include "math.h"

#define STKSIZE 100

void ungetch(int c);
int getch(void);
int getfloat(double *pn);

int main(void) {
	double n;

	if (!getfloat(&n))
		printf("%g\n", n);

	return 0;
}

int getfloat(double *pn) {
	int c;

	// skip spaces
	while (isspace(c = getch()))
		;

	if (c == EOF) {
		ungetch(c);
		return c;
	}

	char sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-')
		if (!isdigit(c=getch())) {
			ungetch(c);
			return c;
		}

	if (!isdigit(c)) {
		ungetch(c);
		return c;
	}

	*pn = 0;
	double factor = 1;
	unsigned exp = 0;
	char jumpout = 0;
	for (;isdigit(c); c = getch())
		*pn = *pn * 10 + c - '0';
	while (c == 'e' || c == 'E' || c == '.') {
		switch (c) {
			case '.':
				if (!isdigit(c = getch())) {
					ungetch(c);
					ungetch('.');
					jumpout = 1;
				}
				while (isdigit(c)) {
					*pn = *pn * 10 + c - '0';
					factor *= 0.1;
					c = getch();
				}
				break;
			case 'e':
				if (!isdigit(c = getch()) && c != '+' && c != '-') {
					ungetch(c);
					ungetch('e');
					jumpout = 1;
				}
				switch (c) {
					case '-':
						if (!isdigit(c = getch())) {
							ungetch(c);
							ungetch('-');
							jumpout = 1;
						}
						while (isdigit(c)) {
							exp = exp * 10 + c - '0';
							c = getch();
						}
						factor *= pow(10, -exp);
						break;
					case '+':
						c = getch();
						if (!isdigit(c = getch())) {
							ungetch(c);
							ungetch('+');
							jumpout = 1;
						}
						while (isdigit(c)) {
							exp = exp * 10 + c - '0';
							c = getch();
						}
						factor *= pow(10, exp);
						break;
					default:
						if (!isdigit(c)) {
							ungetch(c);
							jumpout = 1;
						}
						while (isdigit(c)) {
							exp = exp * 10 + c - '0';
							c = getch();
						}
						factor *= pow(10, exp);
						break;
				}
				break;
			case 'E':
				if (!isdigit(c=getch()) && c != '+' && c != '-') {
					ungetch(c);
					ungetch('E');
					jumpout = 1;
				}
				switch (c) {
					case '-':
						if (!isdigit(c = getch())) {
							ungetch(c);
							ungetch('-');
							jumpout = 1;
						}
						while (isdigit(c)) {
							exp = exp * 10 + c - '0';
							c = getch();
						}
						factor *= pow(10, -exp);
						break;
					case '+':
						c = getch();
						if (!isdigit(c = getch())) {
							ungetch(c);
							ungetch('+');
							jumpout = 1;
						}
						while (isdigit(c)) {
							exp = exp * 10 + c - '0';
							c = getch();
						}
						factor *= pow(10, exp);
						break;
					default:
						if (!isdigit(c = getch())) {
							ungetch(c);
							jumpout = 1;
						}
						while (isdigit(c)) {
							exp = exp * 10 + c - '0';
							c = getch();
						}
						factor *= pow(10, exp);
						break;
				}
				break;
			default:
				break;
		}
		if (jumpout)
			break;
		exp = 0;
	}
	if (jumpout == 0)
		ungetch(c);
	*pn *= (sign * factor);

	return 0;
}

int stack[STKSIZE];
size_t stkp;

int getch(void) {
	return stkp > 0 ? stack[--stkp] : getchar();
}

void ungetch(int c) {
	if (stkp < STKSIZE)
		stack[stkp++] = c;
	else
		printf("error: stack is now full\n");
}
