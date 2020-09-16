/* Write a program to remove all comments from a C program. Don’t forget to handle quoted strings and
 * character constants properly. C comments don’t nest.
 *
 * Works well, but can be improved by following a `delete blank line` program. */

#include "stdio.h"

#define EXIT    0
#define ENTER   1
#define LIM     10000

int main(void) {
	int i;
	int prec, c;
	int quo, cmtsin, cmtmul;    // flag of quote, single-line comment and multi-line comment
	char s[LIM];

	for (i = 0, prec = '\0', quo = cmtmul = cmtsin = EXIT; (c=getchar())!=EOF && i<LIM-1;) {
		if (quo == EXIT) {
			if (cmtsin == EXIT) {
				if (cmtmul == EXIT) {
					if (c == '/') {
						if (prec == '/') {
							cmtsin = ENTER;
						} else {
							prec = '/';
						}
					} else if (c == '*' && prec == '/') {
						cmtmul = ENTER;
						prec = c;
					} else if (c == '\"' && prec != '\\') {
						quo = ENTER;
						s[i++] = prec = c;
					} else {
						s[i++] = prec = c;
					}
				} else if (c == '/' && prec == '*') {
					cmtmul = EXIT;
					prec = c;
				} else {
					prec = c;
				}
			} else if (c == '\n') {
				cmtsin = EXIT;
				s[i++] = prec = c;
			}
		} else if (c == '\"' && prec != '\\') {
			quo = EXIT;
			s[i++] = prec = c;
		} else {
			s[i++] = prec = c;
		}
	}

	printf("\n\nAfter filtering comment:\n%s", s);
}