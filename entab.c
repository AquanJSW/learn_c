/* Write a program entab that replaces strings of blanks by the minimum number
 * of tabs and blanks to achieve the same spacing. Use the same tab stops as for
 * detab.
 *
 * Exercise 5-11. Modify the program entab and detab (written as exercises in
 * Chapter 1) to accept a list of tab stops as arguments. Use the default tab
 * settings if there are no arguments.*/

#include "stdio.h"
#include "stdlib.h"

#define RB  '#' // for replacing of blank
#define RT  '@' // for replacing of tab

int main(int argc, char *argv[]) {
	const char *usage = "usage: entab TABSTOP\n";
	unsigned char ts;   // tab stop
	int c, bep, p, nb, nt;
	enum STATUS {IN, OUT};
	char status;
	// default tab stop
	if (argc == 1)
		ts = 4;
	else if (argc == 2)
		ts = atoi(*++argv);
	else {
		printf("error: invalid argument\n%s", usage);
		return 1;
	}

	bep = 0;    // blank entrance position
	p = 0;  // current position in a line
	nb = 0; // the number of blanks
	nt = 0; // the number of tabs
	status = OUT;   // outside blank block
	while ((c = getchar()) != EOF) {
		switch (status) {
			case IN:
				switch (c) {
					case ' ':
						break;
					case '\t':
						p += ts - 1;
						break;
					case '\n':
						putchar('\n');
						nb = 0;
						nt = 0;
						p = -1;
						status = OUT;
						break;
					default:    // non-blank
						bep -= bep % ts;
						nb = (p - bep) % ts;
						nt = (p - bep) / ts;
						while (nt--)
							putchar(RT);
						while (nb--)
							putchar(RB);
						nt = 0;
						nb = 0;
						putchar(c);
						status = OUT;
						break;
				}
				break;
			case OUT:
				switch (c) {
					case ' ':
						bep = p;
						status = IN;
						break;
					case '\t':
						bep = p;
						p += ts - 1;
						status = IN;
						break;
					case '\n':
						putchar('\n');
						p = -1;
						break;
					default:
						putchar(c);
						break;
				}
				break;
		}
		++p;
	}
}
