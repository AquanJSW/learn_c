/* recursive version of itoa */

#include "stdio.h"

#define STRLIM  100 // string limit
#define BASE    10

void itoa(char s[], size_t lim, char base, int n);

int main(void) {
	char s[STRLIM];
	int n = -82835;

	itoa(s, STRLIM, BASE, n);
	printf("%s\n", s);
	return 0;
}

void itoa(char s[], size_t lim, char base, int n) {
	static size_t i;
	unsigned un;    // to the situation `n` equal to INT_MIN
	char flag = 0;  // the outermost recursion layer identity

	if (!i)
		flag = 1;
	if (i >= lim) {
		printf("error: reach the string length limit\n");
		return;
	}
	if (n < 0) {
		s[i++] = '-';
		un = -n;
	} else
		un = n;

	if (un / base)
		itoa(s, lim, base, un/base);
	s[i++] = un % base + (un%base > 9 ? 'a'-10 : '0');

	if (flag)
		s[i] = '\0';
}