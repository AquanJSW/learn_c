/* Write a program detab that replaces tabs in the input with the proper number of blanks to space to the
 * next tab stop.
 *
 * Exercise 5-11. Modify the program entab and detab (written as exercises in
 * Chapter 1) to accept a list of tab stops as arguments. Use the default tab
 * settings if there are no arguments.*/

#include "stdio.h"
#include "stdlib.h"

#define TS 4    // default tab stop
#define RB '#'  // symbol of blank

int main(int argc, char *argv[]) {
	const char *usage = "usage: detab TABSTOP\n";
	unsigned char ts;    // tab stop
	int c, p, nb;

	if (argc == 1)
		ts = TS;
	else if (argc == 2)
		ts = atoi(*++argv);
	else {
		printf("error: too many arguments\n%s", usage);
		return 1;
	}

	p = 0;  // current position in a line
	nb = 0; // number of blanks for replacing tab
	while ((c = getchar()) != EOF) {
		switch (c) {
			case '\t':
				nb = ts * (1 + (p+1) / ts) - p;
				while (nb--)
					putchar(RB);
				break;
			default:
				putchar(c);
				break;
		}
		p++;
	}
	return 0;
}

