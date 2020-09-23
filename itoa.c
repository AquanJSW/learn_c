/* Exercise 3-4. In a two’s complement number representation, our version of
 * itoa does not handle the largest negative number, that is, the value of n
 * equal to -(2^(wordsize-1)). Explain why not. Modify it to print that value
 * correctly, regardless of the machine on which it runs. */

#include "stdio.h"
#include "string.h"
#include "limits.h"

#define MAX 512

void itoa(int n, char s[]);
void strrev(char s[]);

int main(void) {
	int n = INT_MAX;
	char s[MAX];

	itoa(n, s);
	printf("%d:\n%s\n", n, s);

	return 0;
}


void itoa(int n, char s[]) {
	enum signs {POS, NEG};
	int sign = n < 0 ? NEG : POS;
	size_t i;
	unsigned un = n==INT_MIN || n>0 ? n : -n;

	i = 0;
	do {
		s[i++] = un % 2 + '0';
	} while ((un >>= 1) > 0);

	if (sign == NEG)
		s[i++] = '-';
	s[i] = '\0';

	strrev(s);
}


/* String reverser */
void strrev(char s[]) {
	size_t i, j;
	char temp;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}
}