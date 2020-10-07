/* Exercise 5-12. Extend entab and detab to accept the shorthand
 * entab -m +n
 * to mean tab stops every n columns, starting at column m. Choose convenient
 * (for the user) default behavior. */

#include "stdio.h"
#include "stdlib.h"

#define RB  '#' // for replacing of blank
#define RT  '@' // for replacing of tab

int main(int argc, char *argv[]) {
	unsigned char sc = 0;    // starting column, index starts at 0
	unsigned char ts = 4;    // tab stop
	char status;
	const char *usage = "usage: entab OPTIONS\n"
    "OPTIONS:\n"
    "-m\n\ttab starts at column m\n"
    "-n\n\ttab stops every n column\n";
	int bep, p, nb, nt, c;
	enum STATUS {IN, OUT};

	while (--argc) {
		switch (**++argv) {
			case '-':
				sc = atoi(++*argv);
				break;
			case '+':
				ts = atoi(++*argv);
				break;
			default:
				printf("error: invalid arguments\n%s", usage);
				return 0;
		}
	}

	bep = 0;    // blank entrance position
	p = -sc - 1;  // current position in a line
	nb = 0; // the number of blanks
	nt = 0; // the number of tabs
	status = OUT;   // outside blank block
	while ((c = getchar()) != EOF) {
		if (p >= 0)
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
							p = -sc - 2;
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
							p = -sc - 2;
							break;
						default:
							putchar(c);
							break;
					}
					break;
				default:
					break;
			}
		else
			putchar(c);
		++p;
	}
	return 0;
}