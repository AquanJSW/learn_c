/* Exercise 5-1. As written, getint treats a + or - not followed by a digit as
 * a valid representation of zero. Fix it to push such a character back on the
 * input.
 *
 * 只判断下一个字符（跳过空字符）是否属于整数，
 * - 是则继续读取直到当前整数结束;
 * - 否则ungetch当前字符
 * 并返回"EOF、0、正数"分别表示当前字符属于"EOF、数字、其他" */

#include "stdio.h"
#include "ctype.h"

#define STKSIZE 100

void ungetch(int c);
int getch(void);
int getfloat(int *pn);

int main(void) {
	int n;

	if (!getint(&n))
		printf("%d\n", n);

	return 0;
}

int getfloat(int *pn) {
	int c;
	char sign;

	// skip spaces
	while (isspace(c = getch()))
		;

	if (c == EOF) {
		ungetch(c);
		return c;
	}

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-')
		// 实现要求
		if (!isdigit(c=getch())) {
			ungetch(c);
			return c;
		}

	if (!isdigit(c)) {
		ungetch(c);
		return c;
	}

	*pn = 0;
	for (;isdigit(c); c = getch())
		*pn = *pn * 10 + c - '0';
	*pn *= sign;
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
