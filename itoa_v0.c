/* Exercise 3-6. Write a version of itoa that accepts three arguments instead
 * of two. The third argument is a minimum field width; the converted number
 * must be padded with blanks on the left if necessary to make it wide enough.*/

#include "stdio.h"
#include "string.h"
#include "limits.h"

#define MAX 512
#define MIN 64

void itoa(int n, char s[], unsigned lim);
void strrev(char s[]);

int main(void) {
	int n = INT_MAX;
	char s[MAX];

	itoa(n, s, MIN);
	printf("%d:\n%s\n", n, s);

	return 0;
}


void itoa(int n, char s[], unsigned lim) {
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
	if (i <= MIN)
		for (; i < MIN; i++)
			s[i] = ' ';
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
