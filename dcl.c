/* convert C declaration into a word description
 *
 * i.e.:
 * char *argv
 *      argv: pointer to char
 * int (*daytab)[13]
 *      daytab: pointer to array[13] of int
 * int *daytab[13]
 *      daytab: array[13] of pointer to int
 * void *comp()
 *      comp: function returning pointer to void
 * void (*comp)()
 *      comp: pointer to function returning void
 * char (*(*x())[])()
 *      x: function returning pointer to array[] of
 *      pointer to function returning char
 * char (*(*x[3])())[5]
 *      x: array[3] of pointer to function returning
 *      pointer to array[5] of char
 *
 * 2 part of crucial routines
 * - dcl:       optional *’s direct-dcl
 * - direct-dcl:name
 *              (dcl)
 *              direct-dcl()
 *              direct-dcl[optional size] */

#include "stdlib.h"
#include "stdio.h"
#include "ctype.h"
#include "string.h"

#define MAXSUBDCLS 50 // max sub-declarations
#define MAXTOKENLEN 50 // max token length

enum TYPE {ERR, FIN, NAME, PARENS, BRACKS};
char *subdcls[MAXSUBDCLS];
char ret[MAXTOKENLEN];
char subdclp; // sub-declaration position
int c;
char type;
char *name;

void skipspaces(void);
int getch(void);
void ungetch(int i);
void error(const char *msg);
void getrettype(void);
void *stralloc(const char *s);
void *alloc(int n, int size);
void dcl(void);
void dirdcl(void);
char gettoken(char *token);
void ungettoken(const char *token);
void printdcl();

int main(void) {
	skipspaces();
	getrettype();
	skipspaces();
	dcl();
	printdcl();
	return 0;
}

/* skip spaces */
void skipspaces(void) {
	while (isspace(c=getch()))
		;
	ungetch(c);
}

/* get returning type */
void getrettype(void) {
	char i;

	i = 0;
	while (isalnum(c=getch()))
		ret[i++] = c;
	ret[i] = '\0';
}

#define CHSTKSIZE 1000 // size of stack that is for getch and ungetch
int chstk[CHSTKSIZE];
int chstkp;

int getch(void) {
	return chstkp ? chstk[--chstkp] : getchar();
}

void ungetch(int i) {
	if (chstkp < CHSTKSIZE)
		chstk[chstkp++] = i;
	else
		error("no more spaces in stack for ungetch.");
}

/* raise error message and exit */
void error(const char *msg) {
	printf("error: %s\n", msg);
	exit(1);
}

/* return a pointer w.r.t. s, also saving memory */
void *stralloc(const char *s) {
	char *ptr = alloc(strlen(s) + 1, sizeof(char));
	strncpy(ptr, s, strlen(s) + 1);
	return ptr;
}

#define ALCSTKSIZE 10000 // size of stack that is for alloc
char alcstk[ALCSTKSIZE];
char *alcstkp = alcstk;

void *alloc(int n, int size) {
	if (alcstkp + n*size - alcstk <= ALCSTKSIZE) {
		alcstkp += n * size;
		return alcstkp - n * size;
	} else
		error("no more stack space for alloc.");
}

void dcl(void) {
	char np; // the number of pointers
	char token[MAXTOKENLEN];

	np = 0;
	while (gettoken(token) == '*')
		np++;
	ungettoken(token);
	dirdcl();
	while (np-- > 0)
		subdcls[subdclp++] = stralloc("pointer to ");
}

void dirdcl(void) {
	char token[MAXTOKENLEN];

	switch (gettoken(token)) {
		case '(':
			dcl();
			if (gettoken(token) != ')')
				error("mismatching '(' exits.");
			break;
		case NAME:
			name = stralloc(token);
			break;
		default:
			break;
	}
	while ((type = gettoken(token)) == BRACKS || type == PARENS)
		if (type == BRACKS) {
			subdcls[subdclp++] = stralloc("array");
			subdcls[subdclp++] = stralloc(token);
			subdcls[subdclp++] = stralloc(" of ");
		} else
			subdcls[subdclp++] = "function returning ";
	ungettoken(token);
}

char gettoken(char *token) {
	int i;

	c = getch();
	i = 0;
	if (isalnum(c)) {
		ungetch(c);
		while (i < MAXTOKENLEN && isalnum(token[i++] = c = getch()))
			;
		if (i == MAXTOKENLEN)
			error("no more token stack space.");
		ungetch(c);
		token[--i] = '\0';
		return NAME;
	}
	switch (c) {
		case '*':
			strcpy(token, "*");
			return '*';
		case ')':
			strcpy(token, ")");
			return ')';
		case '(':
			if ((c = getch()) == ')') {
				strcpy(token, "()");
				return PARENS;
			}
			ungetch(c);
			strcpy(token, "(");
			return '(';
		case '[':
			ungetch(c);
			while (i < MAXTOKENLEN && (token[i++]=c=getch()) != ']' &&
			c != EOF && c != '\n')
				;
			if (i == MAXTOKENLEN)
				error("no more token stack space.");
			if (c == EOF || c == '\n')
				error("mismatching '['.");
			token[i] = '\0';
			return BRACKS;
		case '\n':
		case EOF:
			return FIN;
		default:
			error("unrecognised token.");
	}
}

void ungettoken(const char *token) {
	int i;

	for (i = strlen(token) - 1; i >= 0; i--)
		ungetch(token[i]);
}

void printdcl() {
	printf("%s: ", name);
	for (int i = 0; i < subdclp; i++)
		printf("%s", subdcls[i]);
	printf("%s", ret);
}
