/* using quick sort to sort lines */

#include "stdio.h"
#include "string.h"

#define MAXLINES    1000

size_t getlines(char *linesptr[], size_t maxlines);
size_t getline_(char *lineptr, size_t maxlen);
char *alloc(size_t n);
void qsort_lines(char *linesptr[], size_t left, size_t right);
void swapptr(char *p, char *q);
void linesprintf(char *linesptr[], size_t nlines);

int main(void) {
	char *linesptr[MAXLINES];   // pointer array
	size_t nlines;

	if ((nlines = getlines(linesptr, MAXLINES)) > 0) {
		qsort_lines(linesptr, 0, nlines - 1);
		linesprintf(linesptr, nlines);
		return 0;
	}

	printf("error: lines reading failed\n");
	return 0;
}

#define MAXLEN  1000
/* get multiple lines and return the number of lines */
size_t getlines(char *linesptr[], size_t maxlines) {
	size_t len, nlines;
	// line起到一个缓存区的作用，读取完毕后再存入lineptr
	char *lineptr, line[MAXLEN], warning;

	warning = 0;
	nlines = 0;
	while ((len = getline_(line, MAXLEN))) {
		if (len < 0 && !warning) {
			printf("warning: too small line length limit\n");
			warning = 1;
			len = MAXLEN;
		}

		if ((lineptr = alloc(len)) == NULL) {
			printf("error: alloc buffer is used up\n");
			return 0;
		}

		strcpy(lineptr, line);
		lineptr[len-1] = '\0';
		linesptr[nlines++] = lineptr;
	}

	return nlines;
}

/* get single-line and return its length */
size_t getline_(char *lineptr, size_t maxlen) {
	int c;
	char *p;

	p = lineptr;
	for (; lineptr - p < maxlen && (*lineptr = c = getchar()) != '\n' &&
	c != EOF; lineptr++)
		;

	// exceed length limit
	if (lineptr - p == maxlen && c != '\n' && c != EOF)
		return -1;

	if (lineptr == p && c == EOF)
		return 0;

	return lineptr - p + 1;
}

#define STKSIZE     10000
/* allocate memories and return pointer */
char *alloc(size_t n) {
	static char stack[STKSIZE], *stkp;

	stkp = stack;
	if (stkp - stack + n <= STKSIZE) {
		stkp += n;
		return stkp - n;
	}

	// stack is full
	return NULL;
}

/* quick sort for lines */
void qsort_lines(char *linesptr[], size_t left, size_t right) {
	// stop recursion when no more than 2 elements
	if (left >= right)
		return;

	size_t last, i;

	swapptr(linesptr[left], linesptr[(left+right) / 2]);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (strcmp(linesptr[i], linesptr[left]) > 0)
			swapptr(linesptr[i], linesptr[++last]);
	swapptr(linesptr[left], linesptr[last]);

	qsort_lines(linesptr, left, last);
	qsort_lines(linesptr, last + 1, right);
}

/* swap 2 pointers */
void swapptr(char *p, char *q) {
	char *t;

	t = p;
	p = q;
	q = t;
}

/* print lines */
void linesprintf(char *linesptr[], size_t nlines) {
	for (size_t i = 0; i < nlines; i++)
		printf("%s\n", linesptr[i]);
}
