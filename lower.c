/* Rewrite the function lower, which converts upper case letters to lower case, with a conditional expression
 * instead of if-else. */

#include "stdio.h"

void lower(char s[]);

int main(void) {
	char s[] = "Huihu Ling";
	printf("Origin: '%s'\n", s);
	lower(s);
	printf("After: '%s'\n", s);
	return 0;
}


void lower(char s[]) {
	size_t i;
	for (i = 0; s[i] != '\0'; ++i)
		s[i] = s[i] >= 'A' && s[i] <= 'Z' ? s[i] + 32 : s[i];
}