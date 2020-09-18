/* Write a program to check a C program for rudimentary syntax errors like unmatched parentheses, brackets
 * and braces. Don’t forget about quotes, both single and double, escape sequences, and comments. (This program is
 * hard if you do it in full generality.) */

#include "stdio.h"
#include "string.h"

int c;
int paren, brack, brace, sinquo, douquo, slcmt, mlcmt;
const char ESCAPE[] = "?abfbrtv";
enum legal {LEGAL, ILLEGAL};

void inslcmt(void);
void inmlcmt(void);
void checkout(void);
void search(void);
int chkescape(void);
int insinquo(void);
int indouquo(void);

int main(void) {
	while ((c = getchar()) != EOF) {
		if (c == '/') {
			if ((c = getchar()) == '/') {
				++slcmt;
				inslcmt();
			} else if (c == '*') {
				++mlcmt;
				inmlcmt();
			} else {
				printf("Illegal use of '/'.\n");
				checkout();
				return 0;
			}
		} else if (c == '\'') {
			++sinquo;
			if (insinquo() == ILLEGAL) {
				checkout();
				return 0;
			}
		} else if (c == '"') {
			++douquo;
			if (indouquo() == ILLEGAL) {
				checkout();
				return 0;
			}
		} else
			search();
		if (c == EOF)
			return 0;
	}

	checkout();
	return 0;
}


/* In single-line comment */
void inslcmt(void) {
	while ((c = getchar()) != '\n' && c != EOF);
	--slcmt;
}


/* In multi-line comment */
void inmlcmt(void) {
	while ((c = getchar()) != EOF) {
		if (c == '*' && (c = getchar()) == '/') {
			--mlcmt;
			return;
		}
		if (c == EOF)
			break;
	}
	printf("Unterminated multi-line comment.\n");
}


/* Print error message */
void checkout(void) {
	if (paren != 0)
		printf("Containing unmatched parentheses.\n");
	if (brace != 0)
		printf("Containing unmatched braces.\n");
	if (brack != 0)
		printf("Containing unmatched brackets.\n");
	if (sinquo != 0)
		printf("Containing unmatched single quotes.\n");
	if (douquo != 0)
		printf("Containing unmatched double quotes.\n");
	if (slcmt != 0)
		printf("Containing unterminated single-line comment.\n");
	if (mlcmt != 0)
		printf("Containing unterminated multi-line comment.\n");
}


/* Check escape character */
int chkescape(void) {
	if (c == '\\')
		if (!strchr(ESCAPE, c=getchar()))
			return ILLEGAL;
	return LEGAL;
}


/* In single quote */
int insinquo(void) {
	while ((c = getchar()) != '\'' && c != EOF) {
		if (chkescape() == ILLEGAL) {
			printf("Illegal escape character.\n");
			return ILLEGAL;
		}
	}

	if (c == '\'') {
		--sinquo;
		return LEGAL;
	}
	return ILLEGAL;
}


/* In double quote. */
int indouquo(void) {
	while ((c = getchar()) != '"' && c != EOF) {
		if (chkescape() == ILLEGAL) {
			printf("Illegal escape character.\n");
			return ILLEGAL;
		}
	}

	if (c == '"') {
		--douquo;
		return LEGAL;
	}
	return ILLEGAL;
}


/* Searching for parentheses, brackets and braces. */
void search(void) {
	switch (c) {
		case '(':
			++paren;
			break;
		case ')':
			--paren;
			break;
		case '[':
			++brack;
			break;
		case ']':
			--brack;
			break;
		case '{':
			++brace;
			break;
		case '}':
			--brace;
			break;
		default:
			;
	}
}