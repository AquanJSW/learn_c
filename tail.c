/* Exercise 5-13. Write the program tail, which prints the last n lines of its
 * input. By default, n is set to 10, let us say, but it can be changed by an
 * optional argument so that
 * tail -n
 * prints the last n lines. The program should behave rationally no matter how
 * unreasonable the input or the value of n. Write the program so it makes the
 * best use of available storage; lines should be stored as in the sorting
 * program of Section 5.6, not in a two-dimensional array of fixed size. */

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define MAXLINES 10000    // max lines

int getline_(char **line);
char *alloc(int n);

int main(int argc, char *argv[]) {
	int n = 10; // the number of lines to be printed
	int nlines; // total lines of input
	char *lines[MAXLINES];  // for storing input
	const char *usage = "Printing the last n lines of input.\n"
    "Usage: tail OPTIONS\n"
    "OPTIONS:\n"
    "-n\n\tthe number of lines to be printed.\n";

	while (--argc){
		if (**++argv == '-')
			n = atoi(++*argv);
		else {
			printf("error: invalid argument\n%s", usage);
			return 0;
		}
	}

	if (n < 1) {
		printf("error: n should be a positive integer.");
		return 0;
	}

	nlines = 0;
	while (getline_(lines + nlines) > 0 && nlines < MAXLINES - 1)
		nlines++;

	if (nlines == MAXLINES - 1)
		printf("warning: not enough input lines buffer.\n");

	for (int i = (nlines - n < 0 ? 0 : nlines - n); i < nlines; i++)
		printf("%s\n", lines[i]);

	return 0;
}

#define MAXLEN 10000    // max line length for buffer

int getline_(char **line) {
	static char linebuf[MAXLEN];
	char *lineptr;
	int c, i;

	i = 0;
	while (i < MAXLEN && (linebuf[i++] = c = getchar()) != '\n' && c != EOF)
		;
	if (i == MAXLEN)
		printf("warning: too small line length limit.\n");
	linebuf[--i] = '\0';

	if ((lineptr = alloc(i + 1))) {
		strncpy(lineptr, linebuf, i + 1);
		*line = lineptr;
		return i;
	} else
		return 0;
}

#define STKSIZE 10000

char *alloc(int n) {
	static char stack[STKSIZE];
	static char *p = stack;

	if (n > 0 && p - stack < STKSIZE) {
		p += n;
		return p - n;
	} else {
		printf("error: invalid allocation.\n");
		return NULL;
	}
}
