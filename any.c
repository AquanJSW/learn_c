/* Write the function any(s1,s2), which returns the first location in a string s1 where any character from the
 * string s2 occurs, or -1 if s1 contains no characters from s2. (The standard library function strpbrk does the same
 * job but returns a pointer to the location. */

#include "stdio.h"
#include "string.h"

int any(const char *s1, const char *s2);

int main(void) {
	char s1[] = "Family Huihu: Huihu Ling, Huihu Lan, etc.";
	char s2[] = " :Ht";

	printf("Target string: '%s'\n", s1);
	printf("Characters to search: '%s'\n", s2);
	printf("First occurrence location: %d\n", any(s1, s2));
}


int any(const char *s1, const char *s2) {
	size_t i;
	for (i = 0; s1[i] != '\0'; ++i)
		if (strchr(s2, s1[i]))
			return i;
	return -1;
}