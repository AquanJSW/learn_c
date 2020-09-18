/* Exercise 3-2. Write a function escape(s,t) that converts characters like newline and tab charo visible escape
 * sequences like \n and \t as it copies the string t to s. Use a switch. Write a function for the other direction
 * as well, converting escape sequences charo the real characters. */

#include "stdio.h"

#define MAX 1000

void strscan(char t[]);
void escape(char s[], const char t[]);
void compile(char dst[], const char src[]);

int main(void) {
	char t[MAX], s[MAX];

	strscan(t);

	escape(s, t);
	printf("After escape:\n%s\n", s);
	compile(t, s);
	printf("After recompile\n%s\n", t);

	return 0;
}


/* Scan input charo string. */
void strscan(char t[]) {
	size_t i;

	for (i = 0; (t[i] = getchar()) != EOF; ++i);
}


/* Convert newline and tab character into `\n` and `\t` for visibility. */
void escape(char s[], const char t[]) {
	size_t i, j;

	j = 0;
	for (i = 0; t[i] != '\0'; ++i) {
		switch (t[i]) {
			case '\n':
				s[j++] = '\\';
				s[j++] = 'n';
				break;
			case '\t':
				s[j++] = '\\';
				s[j++] = 't';
				break;
			default:
				s[j++] = t[i];
				break;
		}
	}
	s[j] = '\0';
}


/* Compile `\n` and `\t` */
void compile(char dst[], const char src[]) {
	size_t i, j;

	j = 0;
	for (i = 0; src[i] != '\0'; ++i) {
		if (src[i] == '\\') {
			switch (src[i + 1]) {
				case 'n':
					dst[j++] = '\n';
					i++;
					break;
				case 't':
					dst[j++] = '\t';
					i++;
					break;
				default:
					dst[j++] = src[i];
					break;
			}
		} else
			dst[j++] = src[i];
	}

	dst[j] = '\0';
}