/* Exercise 6-2. Write a program that reads a C program and prints in
 * alphabetical order each group of variable names that are identical in the
 * first 6 characters, but different somewhere thereafter. Don’t count words
 * within strings and comments. Make 6 a parameter that can be set from the
 * command line. */

#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"

#define NEXCEPT_MAX 100 // max number of keys
#define LENWORD_MAX 200 // max word length
#define NVAR_MAX 10000

char *var[NVAR_MAX];
int pvar;
char *except[NEXCEPT_MAX] = {
		"static",
		"extern",
		"int",
		"char",
		"long",
		"size_t",
		"double",
		"float",
		"unsigned",
		"signed",
		"auto",
		"register",
		"volatile",
		"short",
		"void",
		"const",
		"if",
		"break",
		"for",
		"case",
		"struct",
		"return"
};
int pexcept;
struct tnode {
	char *word;
	struct tnode *left;
	struct tnode *right;
};
char nidchar = 6; // the number of identical character

void argread(int argc, char **argv);
char getword(char *word);
int getch(void);
void ungetch(int c);
void error(const char *msg);
void addexcept(const char *name);
char *stralloc(const char *str);
struct tnode *addtree(struct tnode *node, const char *word);
void savevar(struct tnode *node);
void qsort_v(char **v, int left, int right);
void swap(char **v, int p0, int p1);
void vprint(void);
int findstr(const char **v, const char *str);

int main(int argc, char *argv[]) {
	struct tnode *root;
	char word[LENWORD_MAX];

	argread(argc, argv);
	/* calculate pexcept */
	while (except[pexcept])
		pexcept++;

	root = NULL;
	while (getword(word) > 0)
		root = addtree(root, word);
	savevar(root);
	qsort_v(var, 0, pvar - 1);
	qsort_v(except, 0, pexcept - 1);
	vprint();
	return 0;
}

void argread(int argc, char **argv) {
	if (argc > 1)
		nidchar = atoi(*++argv);
	if (argc > 2)
		printf("warning: too many arguments.\n");
}

/* get word.
 * supposing word length < LENWORD_MAX, so no length checking
 * skip:
 * - function name (following a '(');
 * - preprocessing line, but meantime add the defined name in exception list;
 * - comment;
 * - const string;
 * - words in '[]';*/
char getword(char *word) {
	int c, i;

	i = 0;
	while ((c=getch()) != EOF) {
		if (c == '/')
			/* single-line comment */
			if ((c=getch()) == '/') {
				while ((c=getch()) != EOF && c != '\n');
				ungetch(c);
			/* multi-line comment */
			} else if (c == '*')
				while (1) {
					/* find terminator */
					while ((c=getch()) != EOF && c != '*');
					if (c == EOF)
						error("endless comment.");
					else // c == '*'
						if ((c=getch()) == '/')
							break;
				}
			else
				error("unrecognised '/'.");
		/* skip single quote.
		 * do not care about the escape character's legality */
		else if (c == '\'') {
			while ((c = getch()) != EOF && c != '\'');
			if (c == EOF)
				error("endless single quote.");
		/* skip double quote */
		} else if(c == '\"') {
			while ((c = getch()) != EOF && c!= '\"');
			if (c == EOF)
				error("endless double quote.");
		/* skip characters in bracket */
		} else if (c == '[') {
			while ((c = getch()) != EOF && c != ']');
			if (c == EOF)
				error("endless bracket.");
		/* preprocessor */
		} else if (c == '#') {
			while ((c = getch()) != EOF && isalpha(c))
				word[i++] = c;
			ungetch(c);
			word[i] = '\0';
			/* add the name in #define into exception list */
			if (!strcmp(word, "define")) {
				/* skip spaces */
				while ((c = getch()) != EOF && isspace(c));
				if (c == EOF)
					error("invalid use of #define.");
				ungetch(c);
				/* validate the name */
				if (!(isalpha(c) || c == '_'))
					error("invalid variable name.");
				i = 0;
				/* get name */
				while ((c = getch()) != EOF && (isalnum(c) || c == '_'))
					word[i++] = c;
				ungetch(c);
				word[i] = '\0';
				addexcept(word);
			/* skip other preprocessor */
			} else {
				while ((c = getch()) != EOF && c != '\n');
				ungetch(c);
			}
		/* validate the word leading by alphabet or '_' */
		} else if (isalpha(c) || c == '_') {
			ungetch(c);
			i = 0;
			/* get word */
			while ((c = getch()) != EOF && (isalnum(c) || c == '_'))
				word[i++] = c;
			ungetch(c);
			word[i] = '\0';
			/* word == "struct".
			 * except structure tag */
			if (!strcmp(word, "struct")) {
				/* skip spaces */
				while ((c = getch()) != EOF && isspace(c));
				/* have tag */
				if (isalpha(c) || c == '_') {
					ungetch(c);
					i = 0;
					while ((c = getch()) != EOF && (isalnum(c) || c == '_'))
						word[i++] = c;
					if (c == EOF)
						error("invalid structure.");
					ungetch(c);
					word[i] = '\0';
					addexcept(word);
				}
			} else {
				/* skip spaces */
				while ((c = getch()) != EOF && isspace(c));
				ungetch(c);
				/* if next non-space character is '(',
				 * then current word is a function name, skip it. */
				if (c != '(') {
					return i;
				}
			}
		}
	}
	return 0; // EOF
}

#define STKCH_SIZE 1000
int stkch[STKCH_SIZE];
int pstkch;

int getch(void) {
	return pstkch ? stkch[--pstkch] : getchar();
}

void ungetch(int c) {
	if (pstkch < STKCH_SIZE)
		stkch[pstkch++] = c;
	else
		error("no more stack space for ungetch.");
}

void error(const char *msg) {
	printf("error: %s\n", msg);
	exit(1);
}

/* add name to exception list */
void addexcept(const char *name) {
	except[pexcept++] = stralloc(name);
}

char *stralloc(const char *str) {
	char *p;

	p = (char *)malloc(strlen(str) + 1);
	/* if memory is used up */
	if (p)
		strcpy(p, str);
	else
		error("memory is used up.");
	return p;
}

struct tnode *addtree(struct tnode *node, const char *word) {
	int cond;

	if (!node) {
		node = (struct tnode *)malloc(sizeof(struct tnode));
		node->word = stralloc(word);
		node->left = NULL;
		node->right = NULL;
	} else {
		if ((cond = strcmp(node->word, word)) > 0)
			node->left = addtree(node->left, word);
		else if (cond < 0)
			node->right = addtree(node->right, word);
	}
	return node;
}

void savevar(struct tnode *node) {
	if (node) {
		var[pvar++] = node->word;
		savevar(node->left);
		savevar(node->right);
	}
}

void qsort_v(char **v, int left, int right) {
	int last, i, cond;

	if (left >= right)
		return;

	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left+1; i <= right; i++) {
		if ((cond = strcmp(v[left], v[i])) > 0)
			swap(v, ++last, i);
	}
	swap(v, left, last);
	qsort_v(v, left, last);
	qsort_v(v, last + 1, right);
}

void swap(char **v, int p0, int p1) {
	void *temp;

	temp = v[p0];
	v[p0] = v[p1];
	v[p1] = temp;
}

void vprint(void) {
	int i;

	i = 0;
	if (pvar) {
		/* print the first variable that isn't in exception list */
		for (; i < pvar && findstr((const char **)except, var[i]) >= 0; i++);
		printf("\n%s ", var[i++]);
		for (; i < pvar; i++)
			if (findstr((const char **)except, var[i]) < 0) {
				/* long enough to use strncmp */
				if (strlen(var[i]) >= nidchar && strlen(var[i - 1]) >= nidchar)
					printf(strncmp(var[i], var[i - 1], nidchar) ?
					       "\n%s " : "%s ", var[i]);
				else
					printf("\n%s ", var[i]);
			}
		putchar('\n');
	} else
		error("empty variables.");
}

int findstr(const char **v, const char *str) {
	int i;

	for (i = 0; v[i]; i++)
		if (!strcmp(v[i], str))
			return i;
	return -1;
}