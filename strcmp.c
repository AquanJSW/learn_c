/* using numeric value based string comparison to sort input lines
 *
 * Exercise 5-14. Modify the sort program to handle a -r flag, which indicates
 * sorting in reverse (decreasing) order. Be sure that -r works with -n.
 *
 * Exercise 5-15. Add the option -f to fold upper and lower case together, so
 * that case distinctions are not made during sorting; for example, a and A
 * compare equal.
 *
 * Exercise 5-16. Add the -d (‘‘directory order’’) option, which makes
 * comparisons only on letters, numbers and blanks. Make sure it works in
 * conjunction with -f.
 *
 * Exercise 5-17. Add a field-searching capability, so sorting may bee done on
 * fields within lines, each field sorted according to an independent set of
 * options. (The index for this book was sorted with -df for the index category
 * and -n for the page numbers.) */

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

#define MAXLINES 10000

int getline_(char **line);
void *alloc(int n, int size);
void qsort_(void **v, int left, int right,
			int (*cmp)(void *, void *, char, char), char fold, char dir);
void swap(void **v, int p0, int p1);
int numcmp(const char *s, const char *t, char, char);
int strcmp_(const char *s, const char *t, char fold, char dir);
void showlines(void **v, int nlines, char reverse);

int main(int argc, char *argv[]) {
	char *lines[MAXLINES]; // storing input
	char numeric = 0; // numeric sort switch
	char reverse = 0; // print in reverse
	char fold = 0; // fold lowercase and uppercase
	char dir = 0; // directory order
	int start = 0, stop = 0; // only sort lines between start and stop
	const char *usage = "Sort input.\n"
    "Usage: strcmp [OPTIONS] [-START] [+STOP]\n"
    "OPTIONS:\n"
	"-h\n\thelp.\n"
    "-n\n\tnumeric sort.\n"
	"-r\n\treverse sort.\n"
    "-f\n\tfold lowercase and uppercase together.\n"
	"-d\n\tdirectory sort (only consider alphabet, digit and blank).\n"
	"\n"
    "START & STOP:\n"
    "\tonly sort lines between start and stop line.\n";
	int nlines; // #lines

	while (--argc) {
		if (**++argv == '-') {
			if (isdigit(*++*argv)) {
				start = atoi(*argv);
				continue;
			}
			while (**argv)
				switch (*(*argv)++) {
					case 'n':
						numeric = 1;
						break;
					case 'r':
						reverse = 1;
						break;
					case 'f':
						fold = 1;
						break;
					case 'd':
						dir = 1;
						break;
					case 'h':
						printf("%s", usage);
						return 0;
					default:
						printf("error: invalid argument.\n%s", usage);
						return 0;
				}
		} else if (**argv == '+')
			stop = atoi(*argv);
	}

	nlines = 0;
	while (getline_(lines + nlines) > 0 && nlines < MAXLINES)
		nlines++;

	if (nlines == MAXLINES) {
		printf("warning: too many input lines.\n");
		return 0;
	}

	qsort_((void **)lines, start, stop ? stop : nlines-1,
		(int (*)(void *, void *, char, char))(numeric ? numcmp : strcmp_),
		fold, dir);

	showlines((void **)lines, nlines, reverse);
	return 0;
}

#define MAXLEN 10000

int getline_(char **line) {
	static char linebuf[MAXLEN];
	char *lineptr;
	int i, c;

	i = 0;
	while (i < MAXLEN && (linebuf[i]=c=getchar()) != '\n' && c != EOF)
		i++;
	if (i == MAXLEN) {
		printf("warning: too long line length.\n");
		linebuf[--i] = '\0';
	} else
		linebuf[i] = '\0';

	if ((lineptr = (char *)alloc(i+1, sizeof(char)))) {
		strncpy(lineptr, linebuf, i+1);
		*line = lineptr;
		return i;
	}
	printf("error: stack used up.\n");
	return 0;
}

#define STKSIZE 10000

void *alloc(int n, int size) {
	static char stack[STKSIZE];
	static char *p = stack;

	if (n > 0 && p + n*size - stack < STKSIZE) {
		p += n * size;
		return p - n * size;
	}
	printf("error: allocate memory failed.\n");
	return NULL;
}

void qsort_(void **v, int left, int right,
			int (*cmp)(void *, void *, char, char), char fold, char dir){
	if (left >= right)
		return;
	swap(v, left, (left+right) / 2);
	int last = left;
	for (int i = left+1; i <= right; i++) {
		if ((*cmp)(v[left], v[i], fold, dir) > 0)
			swap(v, ++last, i);
	}
	swap(v, left, last);
	qsort_(v, left, last, cmp, fold, dir);
	qsort_(v, last+1, right, cmp, fold, dir);
}

void swap(void **v, int p0, int p1) {
	void *temp;

	temp = v[p0];
	v[p0] = v[p1];
	v[p1] = temp;
}

int numcmp(const char *s, const char *t, char fold, char dir) {
	return atoi(s) - atoi(t);
}

#define isdirchar(c) (isblank(c) && isdigit(c) && isalpha(c))

int strcmp_(const char *s, const char *t, char fold, char dir) {
	int i;

	i = 0;
	while (s[i] != '\0' && t[i] != '\0' &&
	(dir ? isdirchar(t[i]) && isdirchar(s[i]) : 1) &&
	(fold ? tolower(s[i]) == tolower(t[i]) : s[i] == t[i]))
		i++;

	return fold ? tolower(s[i]) - tolower(t[i]) : s[i] - t[i];
}

void showlines(void **v, int nlines, char reverse) {
	if (reverse)
		for (int i = nlines-1; i >= 0; i--)
			printf("%s\n", (char *)v[i]);
	else
		for (int i = 0; i < nlines; i++)
			printf("%s\n", (char *)v[i]);
}