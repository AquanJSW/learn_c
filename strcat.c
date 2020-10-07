/* Exercise 5-3. Write a pointer version of the function strcat that we showed
 * in Chapter 2: strcat_(s,t) copies the string t to the end of s. */

#include "stdio.h"

void strcat_(char *s, char *t);

int main(void) {
	char s[] = "Hello, ";
	char t[] = "World!";

	printf("s: %s\n", s);
	strcat_(s, t);
	printf("t: %s\nconcatenated: %s\n", t, s);

	return 0;
}

void strcat_(char *s, char *t) {
	// go to the end of s
	while (*s++)
		;
	--s;
	// copy t to the end of s
	while (*s++ = *t++)
		;
}