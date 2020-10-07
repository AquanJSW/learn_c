/* Exercise 5-5. Write versions of the library functions strncpy, strncat, and
 * strncmp, which operate on at most the first n characters of their argument
 * strings. For example, strncpy(s,t,n) copies at most n characters of t to s.
 * Full descriptions are in Appendix B. */

#include "stdio.h"
#include "string.h"

void strncpy_(char *s, char *t, size_t n);
void strncat_(char *s, char *t, size_t n);
int strncmp_(char *s, char *t, size_t n);

int main(void) {
	char s[] = "Brand New Day";
	char t[] = "Luise";

	printf("before strncat:\ns: %s\nt: %s\n", s, t);
	strncat_(s, t, 4);
	printf("after strncat t to s:\n%s\n", s);

	putchar('\n');
	printf("before strncpy:\ns: %s\nt: %s\n", s, t);
	strncpy_(s, t, 8);
	printf("after strncpy t to s:\n%s\n", s);

	putchar('\n');
	strcpy(s, "Good");
	strcpy(t, "Goot");
	printf("for comparison:\ns: %s\nt: %s\n", s, t);
	printf("%d\n", strncmp_(s, t, 3));
}

void strncpy_(char *s, char *t, size_t n) {
	char *tp = t;

	while ((*s++ = *t++) && t - tp < n)
		;

	if (t - tp == n)
		*s = '\0';
}

void strncat_(char *s, char *t, size_t n) {
	// go to the end of s
	while (*s++)
		;
	s--;

	strncpy_(s, t, n);
}

int strncmp_(char *s, char *t, size_t n) {
	char *tp = t;

	for (; *s == *t && *s && *t && t - tp + 1 < n; s++, t++)
		;

	if (!*s || !*t || t - tp == n && *--s == *--t)
		return 0;

	return *s - *t;
}