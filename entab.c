/* Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to achi
 * eve the same spacing. Use the same tab stops as for detab. 
 *
 * Warning: Not perfectly implemented*/

#include <stdio.h>

#define MAXLEN	1000	// max length of input
#define TABSTOP	4
#define IN		0		// inside a block of blanks
#define OUT		1		// outside a block of blanks

int checkout(char s[], int *i, int nspace);


int main(void) {
	int i;
	int nspace;			// count the spaces in a block of blanks
	char c, s[MAXLEN];
	char blank = OUT;

	for (nspace = i = 0; (c=getchar())!=EOF && i<MAXLEN-1;) {
		if (c == '\t') {
			s[i++] = '\t';
			blank = IN;
		}
		else if (c == ' ') {
			++nspace;
			blank = IN;
		}
		else if (blank == IN) {
			checkout(s, &i, nspace);
			s[i++] = c;
			nspace = 0;
			blank = OUT;
		}
		else
			s[i++] = c;
	}

	printf("\n\nReplaced:\n%s", s);
}


/* Replace the spaces in one block of blanks by minimus number tabs and spaces to achieve to same
 * spacing */
int checkout(char s[], int *i, int nspace) {
	int ntab = nspace / TABSTOP;
	int nsp  = nspace % TABSTOP;
	int j;

	for (j = 0; j < ntab; ++j)
		s[(*i)++] = '\t';

	for (j = 0; j < nsp; ++j)
		s[(*i)++] = ' ';

	return 0;
}
