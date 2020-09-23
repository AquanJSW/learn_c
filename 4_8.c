/* Exercise 4-8. Suppose that there will never be more than one character of
 * pushback. Modify getch and ungetch accordingly. */

#include "stdio.h"

int buf;
char buflag;

int getch(void) {
	if (buflag) {
		buflag = 0;
		return buf;
	}
	return getchar();
}

char ungetch(int c) {
	if (buflag) {
		printf("error: no more space for `ungetch`\n");
		return 0;
	}
	buf = c;
	buflag = 1;
	return 1;
}