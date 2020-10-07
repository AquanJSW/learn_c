/* Exercise 6-4. Write a program that prints the distinct words in its input
 * sorted into decreasing order of frequency of occurrence. Precede each word
 * by its count. */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#define WORDBUFLEN 50

struct tword {
	char *word;
	int count;
	struct tword *left;
	struct tword *right;
};
int nword;
int maxwordlen;
struct wc {
	char *word;
	int count;
};

int getword(char *word, int buflen);
int getch(void);
void ungetch(int c);
void error(const char *msg);
struct tword *addtword(struct tword *node, const char *word);
char *stralloc(const char *str);
void extract(struct wc **sorted, struct tword *node);
void qsort_(struct wc **sorted, int left, int right);
void swap(void **v, int p0, int p1);
void print(struct wc **sorted);

int main(void) {
	char word[WORDBUFLEN];
	struct tword *root;
	struct wc **sorted;

	root = NULL;
	while (getword(word, WORDBUFLEN) > 0)
		root = addtword(root, word);
	sorted = (struct wc **)malloc(sizeof(struct wc) * nword);
	extract(sorted, root);
	qsort_(sorted, 0, nword-1);
	print(sorted);
	return 0;
}

int getword(char *word, int buflen) {
	int c, pw;

	pw = 0;
	while ((c = getch()) != EOF) {
		if (isalpha(c)) {
			ungetch(c);
			while ((c = getch()) != EOF && isalpha(c) && pw < buflen)
				word[pw++] = (char)tolower(c);
			ungetch(c);
			if (pw == buflen) {
				printf("warning: word buffer is used up.\n");
				pw--;
			}
			word[pw] = '\0';
			maxwordlen = maxwordlen < pw ? pw : maxwordlen;
			return pw;
		}
	}
	return -1;
}

#define CHSTKSIZE 1000
int stkch[CHSTKSIZE];
int pstkch;

int getch(void) {
	return pstkch ? stkch[--pstkch] : getchar();
}

void ungetch(int c) {
	if (pstkch < CHSTKSIZE)
		stkch[pstkch++] = c;
	else
		error("stack for ungetch is used up.");
}

void error(const char *msg) {
	printf("error: %s\n", msg);
	exit(1);
}

struct tword *addtword(struct tword *node, const char *word) {
	int cond;

	if (!node) {
		node = (struct tword *)malloc(sizeof(struct tword));
		node->word = stralloc(word);
		node->count = 1;
		node->left = NULL;
		node->right = NULL;
		nword++;
	} else {
		if ((cond = strcmp(node->word, word)) > 0)
			node->left = addtword(node->left, word);
		else if (cond < 0)
			node->right = addtword(node->right, word);
		else
			node->count++;
	}
	return node;
}

char *stralloc(const char *str) {
	char *p;

	p = (char *)malloc(sizeof(str)+1);
	if (p)
		strcpy(p, str);
	else
		error("memory is used up.");
	return p;
}

/* extract data from node to sorted */
void extract(struct wc **sorted, struct tword *node) {
	static int i;

	if (node) {
		extract(sorted, node->left);
		sorted[i] = (struct wc *)malloc(sizeof(struct wc));
		sorted[i]->word = stralloc(node->word);
		sorted[i++]->count = node->count;
		extract(sorted, node->right);
	}
}

void qsort_(struct wc **sorted, int left, int right) {
	int last, i;

	if (left >= right)
		return;
	swap((void **)sorted, left, (left+right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (sorted[left]->count < sorted[i]->count)
			swap((void **)sorted, ++last, i);
	swap((void **)sorted, last, left);
	qsort_(sorted, left, last);
	qsort_(sorted, last+1, right);
}

void swap(void **v, int p0, int p1) {
	void *temp;

	temp = v[p1];
	v[p1] = v[p0];
	v[p0] = temp;
}

void print(struct wc **sorted) {
	int i;

	printf("%*s count\n", maxwordlen, "word");
	for (i = 0; i < nword; i++)
		printf("%*s %d\n",maxwordlen, sorted[i]->word, sorted[i]->count);
}
