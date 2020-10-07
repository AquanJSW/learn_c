/* count C keywords */

#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"

#define NKEY (sizeof(keytab) / sizeof(keytab[0]))

struct {
	char *kw;
	int count;
} keytab[] = {
		"auto", 0,
		"sizeof", 0,
		"break", 0,
		"char", 0,
		"int", 0,
		"double", 0,
		"register", 0,
		"const", 0,
		"struct", 0,
		"long", 0,
		"unsigned", 0,
		"continue", 0,
		"return", 0,
		"exit", 0,
		"switch", 0,
		"default", 0,
		"volatile", 0,
		"while", 0,
		"do", 0,
		"goto", 0,
		"for", 0,
		"case", 0,
		"else", 0,
		"void", 0,
		"if", 0
};
enum {KEY=1};

void qsort_key(int left, int right);
void swap(void **, void **);
char *stralloc(const char *s);
void *alloc(int n, int size);
void scankey(void);
int getch(void);
void ungetch(int c);
void error(const char *msg);
int findkey(const char *key);
void checkout(void);

int main(void) {
	qsort_key(0, NKEY-1);
	scankey();
	checkout();
	return 0;
}

void qsort_key(int left, int right) {
	int i, last;

	if (left >= right)
		return;

	swap((void **)&keytab[left].kw, (void **)&keytab[(left+right) / 2].kw);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(keytab[left].kw, keytab[i].kw) > 0)
			swap((void **)&keytab[++last].kw, (void **)&keytab[i].kw);
	swap((void **)&keytab[left].kw, (void **)&keytab[last].kw);
	qsort_key(left, last);
	qsort_key(last+1, right);
}

void swap(void **s, void **t) {
	void *temp;

	temp = *s;
	*s = *t;
	*t = temp;
}

char *stralloc(const char *s) {
	char *p;

	p = alloc(strlen(s) + 1, sizeof(char));
	strncpy(p, s, strlen(s)+1);
	return p;
}

#define ALCSTKSIZE 10000
char alcstk[ALCSTKSIZE];
char *alcstkp = alcstk;

void *alloc(int n, int size) {
	if (alcstkp - alcstk + n*size < ALCSTKSIZE) {
		alcstkp += n * size;
		return alcstkp - n * size;
	}
	error("no more stack space for alloc.");
	return NULL;
}

/* keyword separators or not */
#define MAXKEYLEN 20

const char *qualifier = "()*;,:{}[]";

void scankey(void) {
	int c, keyidx;
	char key_[MAXKEYLEN];
	char *key = key_;

	while ((c = getch()) != EOF) {
		switch (c) {
			case '/':
				switch ((c = getch())) {
					case EOF:
						return;
					case '/': // single-line comment
						while ((c = getch()) != EOF && c != '\n')
							;
						if (c == EOF)
							return;
						break;
					case '*': // multi-line comment
						while (1) {
							while ((c = getch()) != EOF && c == '*')
								;
							if (c == '*' && (c = getch()) == '/')
								break;
							else if (c == EOF)
								error("endless comment.");
						}
						break;
					default:
						error("unrecognised '/'.");
				}
				break;
			case '\'': // skip single quote
				while ((c = getch()) != '\'' && c != EOF)
					;
				if (c == EOF)
					error("endless single quote.");
				break;
			case '\"': // skip double quote
				while ((c = getch()) != '\"' && c != EOF)
					;
				if (c == EOF)
					error("endless double quote.");
				break;
			case '#':
				while ((c = getch()) != '\n' && c != EOF)
					;
				if (c == EOF)
					return;
				break;
			default:
				/* skip variables prefixed by '_' */
				if (c == '_') {
					while ((c = getch()) != EOF && isalnum(c))
						;
					if (c == EOF)
						return;
				/* try getting keyword */
				} else if (isalpha(c)) {
					ungetch(c);
					while ((c = getch()) != EOF && isalpha(*key++ = c))
						;
					/* skip variables suffixed by '_' */
					if (c == '_')
						break;
					else if (c == EOF)
						return;
					ungetch(c);
					*--key = '\0';
					/* matched */
					if ((keyidx = findkey(key_)) >= 0)
						keytab[keyidx].count++; // count
				}
				break;
		}
		key = key_;
	}
}

/* binary search */
int findkey(const char *key) {
	int left, right;

	left = 0;
	right = NKEY;
	if (*key == '\0')
		return -1;

	while (left <= right)
		if (strcmp(keytab[(left+right) / 2].kw, key) < 0)
			left = (left+right) / 2 + 1;
		else if (strcmp(keytab[(left+right) / 2].kw, key) > 0)
			right = (left+right) / 2 - 1;
		else
			return (left+right) / 2;
	return -1; // not found
}

void checkout(void) {
	for (int i = 0; i < NKEY; i++) {
		printf("%s", keytab[i].kw);
		printf(strlen(keytab[i].kw)>=8 ? "\t" : "\t\t");
		printf("%d\n", keytab[i].count);
	}
}

#define CHSTKSIZE 1000
int stack[CHSTKSIZE];
int stkp;

int getch(void) {
	return stkp ? stack[--stkp] : getchar();
}

void ungetch(int c) {
	if (stkp < CHSTKSIZE)
		stack[stkp++] = c;
	else
		error("no more stack spaces for `getch` and `ungetch`.");
}

void error(const char *msg) {
	printf("error: %s\n", msg);
	exit(1);
}