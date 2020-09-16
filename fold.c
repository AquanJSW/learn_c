/* Write a program to ‘‘fold’’ long input lines into two or more shorter lines after the last non-blank * character that occurs before the n-th column of input. Make sure your program does something
 * intelligent with very long lines, and if there are no blanks or tabs before the specified column. */

#include <stdio.h>

#define MAXLEN	1000	// max length of a line
#define COLLIM	50		// fold by specified column

int getline_(char s[], int lim);
int copy(char src[], char dst[]);
int fold(const char src[], char *dst, int *dstr, int maxlen, int collim);


int main(void) {
	int len;	// length of a line
	int i, j;
	char line[MAXLEN], lines[MAXLEN][MAXLEN];
	
	for (i = 0; (len=getline_(line,MAXLEN)) > 0;) {
		if (len <= COLLIM)
			copy(line, lines[i++]);
		else
			fold(line, *lines, &i, MAXLEN, COLLIM);
	}

	printf("\n\nFolded:\n");
	for (j = 0; j < i; ++j) {
		printf("%s", lines[j]);
	}
}


/* Line captor;
 * Return length of a line. */
int getline_(char s[], int lim) {
	char c;
	int i;

	for (i = 0; (c=getchar())!=EOF && c!='\n' && i<lim-1; ++i)
		s[i] = c;

	if (c == '\n')
		s[i++] = '\n';

	s[i] = '\0';

	return i;
}


/* Copy lines */
int copy(char src[], char dst[]) {
	int i;

	for (i = 0; (dst[i]=src[i]) != '\0'; ++i)
		;

	return 0;
}


/* Fold a long line to a new array with the following considering:
 * 1. No blanks at the beginning of a new line;
 * 2. No blanks at the ending of a new line;
 * 3. Satisfied the column limit. */
int fold(const char src[], char *dst, int *dstr, int maxlen, int collim) {
	int i;
	int dstc;		// dst's column index
	int nblank;		// count blanks in the last block of blanks
	int entry;      // entry of the last block of blanks

	for (dstc = entry = nblank = i = 0; src[i] != '\0'; i++) {
		if (dstc < collim) {
			if (dstc == 0) {
				if (src[i] != ' ' && src[i] != '\t')
					dst[*dstr * maxlen + dstc++] = src[i];
			} else {
				if (src[i] == ' ' || src[i] == '\t') {
					++nblank;
					if (src[i-1] != ' ' && src[i-1] != '\t') {
						entry = dstc;
						nblank = 0;
					}
				}
				dst[*dstr * maxlen + dstc++] = src[i];
			}
		} else {
			if (src[i-1] != ' ' && src[i-1] != '\t' && (src[i] == ' ' || src[i] == '\t')) {
				dst[*dstr * maxlen + dstc++] = '\n';
				dst[(*dstr)++ * maxlen + dstc] = '\0';
				dstc = nblank = entry = 0;
			} else {
				dst[*dstr * maxlen + entry] = '\n';
				dst[(*dstr)++ * maxlen + entry + 1] = '\0';
				i -= collim - entry - nblank + 1;
				dstc = nblank = entry = 0;
			}
		}
	}

	return 0;
}