/* Exercise 6-3. Write a cross-referencer that prints a list of all words in a
 * document, and for each word, a list of the line numbers on which it occurs.
 * Remove noise words like ‘‘the,’’ ‘‘and,’’ and so on. */

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"

#define WORDBUF 50

char *noise[] = {
		"the",
		"a",
		"an",
		"and",
		"for",
		"to",
		"with",
		"on",
		"of",
		"in",
		"that",
		"which",
		NULL
};
struct tnumber {
	int number;
	struct tnumber *next;
};
struct tword {
	char *word;
	struct tnumber *refer;
	struct tword *left;
	struct tword *right;
};
int maxwordlen;

int lenv(const char **v);
void qsort_v(char **v, int left, int right);
void swap_v(char **v, int p0, int p1);
int getword(char *word, char maxlen);
int getch(void);
void ungetch(int c);
struct tword *addtword(struct tword *node, const char *word, int lineno);
char *stralloc(const char *str);
int findstr(const char **v, int left, int right, const char *str);
struct tnumber *addtnumber(struct tnumber *node, int lineno);
void tprint(struct tword *node);
void tnprint(struct tnumber *node);
void error(const char *msg);

int main(void) {
	struct tword *root;
	char word[WORDBUF];
	int lineno, nnoise;

	nnoise = lenv((const char **)noise);
	qsort_v(noise, 0, nnoise-1);
	root = NULL;
	while ((lineno = getword(word, WORDBUF)) >= 0) {
		/* word isn't in the list of noise */
		if (findstr((const char **)noise, 0, nnoise-1, word) < 0)
			root = addtword(root, word, lineno);
	}

	printf("%*s references\n", maxwordlen, "word");
	tprint(root);
	return 0;
}

/* determine the length of a 2-D array.
 *
 * supposing that the first unused element is NULL */
int lenv(const char **v) {
	int len;

	len = 0;
	while (*v++)
		len++;
	return len;
}

void qsort_v(char **v, int left, int right) {
	int last, i;

	if (left >= right)
		return;
	swap_v(v, left, (left+right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(v[left], v[i]) > 0)
			swap_v(v, ++last, i);
	swap_v(v, last, left);
	qsort_v(v, left, last);
	qsort_v(v, last+1, right);
}

void swap_v(char **v, int p0, int p1) {
	char *temp;

	temp = v[p0];
	v[p0] = v[p1];
	v[p1] = temp;
}

/* get a word.
 *
 * return line number;
 * casted to lowercase */
int getword(char *word, char maxlen) {
	static int c, lineno;
	static char pw;

	pw = 0;
	while ((c = getch()) != EOF) {
		if (c == '\n')
			lineno++;
		else if (isalpha(c)) {
			ungetch(c);
			while ((c = getch()) != EOF && isalpha(c) && pw < maxlen)
				word[pw++] = (char)tolower(c);
			ungetch(c);
			if (pw == maxlen) {
				printf("warning: word buffer is too small.\n");
				word[--pw] = '\0';
			} else
				word[pw] = '\0';
			maxwordlen = maxwordlen < pw ? pw : maxwordlen;
			return lineno;
		}
	}
	return -1; // EOF
}

#define STKCHSIZE 1000
int stkch[STKCHSIZE];
int pstkch;

int getch(void) {
	return pstkch ? stkch[--pstkch] : getchar();
}

void ungetch(int c) {
	if (pstkch < STKCHSIZE)
		stkch[pstkch++] = c;
	else
		error("no more stack space for ungetch.");
}

struct tword *addtword(struct tword *node, const char *word, int lineno) {
	int cond;

	/* node == NULL */
	if (!node) {
		node = (struct tword *)malloc(sizeof(struct tword));
		node->word = stralloc(word);
		node->refer = addtnumber(node->refer, lineno);
		node->left = NULL;
		node->right = NULL;
	} else {
		if ((cond = strcmp(node->word, word)) < 0)
			node->right = addtword(node->right, word, lineno);
		else if (cond > 0)
			node->left = addtword(node->left, word, lineno);
		else if (node->refer->number != lineno)
			node->refer = addtnumber(node->refer, lineno);
	}
	return node;
}

char *stralloc(const char *str) {
	char *p;

	p = (char *)malloc(strlen(str)+1);
	if (p)
		strcpy(p, str);
	return p;
}

/* find string in v, return index */
int findstr(const char **v, int left, int right, const char *str) {
	int cond;

	while (left <= right) {
		if ((cond = strcmp(v[(left+right)/2], str)) > 0)
			right = (left+right) / 2 - 1;
		else if (cond < 0)
			left = (left+right) / 2 + 1;
		else
			return (left+right) / 2;
	}
	return -1; // not found
}

struct tnumber *addtnumber(struct tnumber *node, int lineno) {
	if (!node) {
		node = (struct tnumber *)malloc(sizeof(struct tnumber));
		node->number = lineno;
		node->next = NULL;
	} else
		node->next = addtnumber(node->next, lineno);
	return node;
}

void tprint(struct tword *node) {
	if (node) {
		tprint(node->left);
		printf("%*s ", maxwordlen, node->word);
		tnprint(node->refer);
		putchar('\n');
		tprint(node->right);
	}
}

void tnprint(struct tnumber *node) {
	if (node) {
		printf("%d ", node->number);
		tnprint(node->next);
	}
}

void error(const char *msg) {
	printf("error: %s\n", msg);
}