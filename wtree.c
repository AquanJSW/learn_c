/* tree to count words */

#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"

#define LENWORD 100

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

int getword(char *word);
int getch(void);
void ungetch(int c);
void error(const char *msg);
struct tnode *addtree(struct tnode *node, const char *word);
char *stralloc(const char *str);
void treeprint(struct tnode *node);

int main(void) {
	char word[LENWORD];
	struct tnode *root;

	root = NULL;
	while (getword(word) > 0)
		root = addtree(root, word);

	treeprint(root);
	return 0;
}

/* return word length */
int getword(char *word) {
	int c;
	char *wordp;

	wordp = word;
	while ((c=getch()) != EOF)
		if (isalpha(c)) {
			ungetch(c);
			while ((c=getch()) != EOF && isalpha(c))
				*word++ = c;
			*word = '\0';
			ungetch(c);
			break;
		}
	return word - wordp; // 0 no word but EOF is encountered
}

#define SIZESTKCH 1000
int stkch[SIZESTKCH];
int pstkch;

int getch(void) {
	return pstkch ? stkch[--pstkch] : getchar();
}

void ungetch(int c) {
	if (pstkch < SIZESTKCH)
		stkch[pstkch++] = c;
	else
		error("no more stack space for ungetch.");
}

void error(const char *msg) {
	printf("error: %s\n", msg);
	exit(1);
}

struct tnode *addtree(struct tnode *node, const char *word) {
	int cond;

	if (node == NULL) {
		node = (struct tnode *)malloc(sizeof(struct tnode));
		node->word = stralloc(word);
		node->count = 1;
		node->right = NULL;
		node->left = NULL;
	} else {
		/* save smaller word to left */
		if ((cond=strcmp(node->word, word)) > 0)
			node->left = addtree(node->left, word);
		/* save greater word to right */
		else if (cond < 0)
			node->right = addtree(node->right, word);
		else
			node->count++; // same word
	}
	return node;
}

char *stralloc(const char *str) {
	char *p;

	p = malloc(strlen(str)+1);
	if (p)
		strcpy(p, str);
	return p;
}

void treeprint(struct tnode *node) {
	if (node) {
		treeprint(node->left);
		printf("%4d %s\n", node->count, node->word);
		treeprint(node->right);
	}
}
