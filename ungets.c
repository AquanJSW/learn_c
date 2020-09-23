/* Exercise 4-7. Write a routine ungets(s) that will push back an entire string
 * onto the input. Should ungets know about buf and bufp, or should it just use
 * ungetch? */

#include "stdio.h"
#include "string.h"

#define BUFSIZE     100
#define STRSIZE     1000
#define STRTARGET   "love"
#define STRAPPND    " Mia"

char getch(void);
char ungetch(char c);
void ungets(const char s[]);

int main(void) {
	char s[STRSIZE];
	char d[] = STRTARGET;
	size_t i, j;

	for (i = 0; (s[i] = getch()) != '\n'; i++) {
		for (j = 0; s[i] == d[j] && j < strlen(d); j++)
			s[++i] = getch();
		if (strlen(d) == j) {
			ungetch(s[i--]);
			ungets(STRAPPND);
		}
	}

	s[i] = '\0';

	printf("%s\n", s);

	return 0;
}

char buf[BUFSIZE];
size_t bufp;

/* `getch` try to get a character from buffer first, then from `getchar` if
 * buffer is empty */
char getch(void) {
	return bufp > 0 ? buf[--bufp] : getchar();
}

/* push a character into buffer */
char ungetch(char c) {
	if (bufp < BUFSIZE) {
		buf[bufp++] = c;
		return 1;   // pushed successfully
	}
	else
		printf("no empty space in buffer\n");

	return 0;
}

/* push a string into buffer */
void ungets(const char s[]) {
	int i;

	for (i = strlen(s) - 1; ungetch(s[i]) && i > 0; i--)
		;
}
