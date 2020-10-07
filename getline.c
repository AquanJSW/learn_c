#include "stdio.h"

void getline_(char *s, size_t lim);

int main(void) {
	char s[100];

	getline_(s, 100);
	printf("\n\n%s\n", s);

	return 0;
}

void getline_(char *s, size_t lim) {
	char *sp;
	int c;

	sp = s;
	while ((*s++ = c = getchar()) != '\n' && c != EOF && s - sp <= lim)
		;

	if (c == EOF)
		*--s = '\0';
}
