/* Exercise 4-1. Write the function strindex(s,t) which returns the position of
 * the rightmost occurrence of t in s, or -1 if there is none */

#include "stdio.h"
#include "string.h"

int strindex(const char s[], const char t[]);


int main(void) {
	char s[] = "Real world, hello world.";
	char t[] = "world";

	printf("%s\n", s);
	printf("Position of the last occurrence of '%s': %d\n",
		t, strindex(s, t));

	return 0;
}

int strindex(const char s[], const char t[]) {
	size_t i, j;
	int pos;

	pos = -1;   // if not found
	for (i = 0; s[i] != '\0'; ++i) {
		for (j = 0; t[j] != '\0'; ++j)
			;
		if (t[j] == '\0')
			pos = i;
	}

	if (pos != -1)
		pos += 1 - strlen(t);

	return pos;
}
