/* Exercise 5-4. Write the function strend(s,t), which returns 1 if the string
 * t occurs at the end of the string s, and zero otherwise. */

#include "stdio.h"

char strend(char *s, char *t);

int main(void) {
	char s[] = "sstrsstrstrr";
	char t[] = "str";

	printf("%s\n", strend(s, t) ? "true" : "false");

	return 0;
}

char strend(char *s, char *t) {
	char *tp = t;

	for (; *s; s++) {

		// compare
		for (; *s == *t && *s && *t; s++, t++)
			;

		// true
		if (!*s && !*t)
			return 1;

		// false
		else if (!*s && *t)
			return 0;

		// continue
		if (t - tp) {
			s--;
			t = tp;
		}
	}
}