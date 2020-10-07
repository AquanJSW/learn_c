/* Exercise 7-8. Write a program to print a set of files, starting each new one
 * on a new page, with a title and a running page count for each file. */

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

#define WIDTH 80
#define HEIGHT 50
#define TABSTOP 8

const char *usage = "usage: printfiles FILE0 ...\n";
char *prog;

void printfile(const char *filename);
int getword(char *word, int n, FILE *);
void ungetw(const char *word);
void asterisk(int n);
int getch(FILE *);
void ungetch(int c);
char *stralloc(const char *str);


int main(int argc, char **argv) {
	prog = *argv;

	if (argc == 1) {
		fprintf(stderr, "too few arguments.\n%s", usage);
		return 1;
	}

	while (--argc)
		printfile(*++argv);
	return 0;
}

#define BUF_WORD 100

void printfile(const char *filename) {
	FILE *fp;
	int row, col, page, len;
	char word[BUF_WORD];

	if (!(fp = fopen(filename, "r"))) {
		fprintf(stderr, "%s: failed to read file %s.\n", prog, filename);
		exit(1);
	}

	asterisk(WIDTH);
	page = 1;
	printf("%s%*d\n", filename, (int) (WIDTH-strlen(filename)), page);

	row = 2;
	col = 0;
	while ((len = getword(word, BUF_WORD, fp)) > 0) {
		if (row == HEIGHT) {
			asterisk(WIDTH);
			printf("%*d\n", (int) WIDTH, ++page);
			row = 2;
		}
		if (!strcmp(word, "\n")) {
			row++;
			col = 0;
			putchar('\n');
		} else if ((col += len) <= WIDTH) {
			printf("%s", word);
		} else {
			ungetw(word);
			col = 0;
			row++;
			putchar('\n');
		}
	}
	fclose(fp);
}

#define STK_WORD 100
char *stkword[STK_WORD];
int pstkw;

/* Get word from fp.
 *
 * Including non-graph characters.
 * Return: length of word. */
int getword(char *word, int n, FILE *fp) {
	int c, pw;

	if (pstkw) {
		if ((pw = (int) strlen(stkword[--pstkw])) >= n)
			fprintf(stderr, "bigger buffer for word is wanted.\n");
		strcpy(word, stkword[pstkw]);
		return pw;
	}

	pw = 0;
	while ((c = getch(fp)) != EOF) {
		if (isgraph(c)) {
			ungetch(c);
			while (isgraph(c = getch(fp)) && --n > 0)
				word[pw++] = (char) c;
			ungetch(c);
			if (n == 0)
				fprintf(stderr, "bigger buffer for word is wanted.\n");
			word[pw] = '\0';
			return pw;
		} else {
			word[pw++] = (char) c;
			word[pw] = '\0';
			return c == '\t' ? TABSTOP : 1;
		}
	}
	return 0;
}

void ungetw(const char *word) {
	if (pstkw < STK_WORD)
		stkword[pstkw++] = stralloc(word);
	else
		fprintf(stderr, "bigger stack for word is wanted.\n");
}

char *stralloc(const char *str) {
	char *p;

	if ((p = (char *) malloc(sizeof(str)+1))) {
		strcpy(p, str);
		return p;
	}
	fprintf(stderr, "memory is used up.\n");
}

void asterisk(int n) {
	putchar('\n');
	for (; n > 0; n--)
		putchar('*');
	putchar('\n');
}

#define STK_CH 1000
int stkch[STK_CH];
int pstkc;

int getch(FILE *fp) {
	return pstkc ? stkch[--pstkc] : fgetc(fp);
}

void ungetch(int c) {
	if (pstkc < STK_CH)
		stkch[pstkc++] = c;
	else
		fprintf(stderr, "bigger stack for ungetch is wanted.\n");
}
