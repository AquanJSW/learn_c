/* Exercise 3-5. Write the function itob(n,s,b) that converts the integer n
 * into a base b character representation in the string s. In particular,
 * itob(n,s,16) formats s as a hexadecimal integer in s. */

#include "stdio.h"
#include "limits.h"
#include "string.h"

#define MAX     100
#define NUM     -234561
#define BASE    20  // max to 36

void itob(int n, char s[], unsigned b);
void strrev(char s[]);

int main(void) {
	int     n = NUM;
	char    s[MAX];
	unsigned b = BASE;

	printf("Decimal: %d\n", n);
	itob(n, s, b);
	printf("Base %u: %s\n", b, s);

	return 0;
}


void itob(int n, char s[], unsigned b) {
	enum signs {POS, NEG};
	int i = 0;
	int sign = n<0 ? NEG : POS;
	unsigned un = n==INT_MIN || n>0 ? n : -n;

	do {
		s[i] = un % b;
		s[i] += s[i]<10 ? '0' : 'a'-10;
		i++;
	} while ((un /= b) > 0);

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
