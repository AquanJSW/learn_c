/* Exercise 7-2. Write a program that will print arbitrary input in a sensible
 * way. As a minimum, it should print non-graphic characters in octal or
 * hexadecimal according to local custom, and break long text lines. */

#include "stdio.h"
#include "ctype.h"

#define BUF_INPUT 10000
#define LINE_STOP 80

struct {
	int enable_hex : 1;
	int enable_oct : 1;
} option;

void scanargs(int argc, char **argv);
void warning(const char *msg);

int main(int argc, char **argv) {
	char input[BUF_INPUT];
	int c, i, j;

	scanargs(argc, argv);

	i = 0;
	/* get input */
	while ((c = getchar()) != EOF && i < BUF_INPUT)
		input[i++] = (char) c;
	if (i == BUF_INPUT) {
		warning("buffer for input is not enough.");
		input[--i] = '\0';
	} else
		input[i] = '\0';

	j = 0;
	for (i = 0; input[i] != '\0'; i++) {
		if (j == LINE_STOP) {
			putchar('\n');
			j = 0;
		}
		if (!isgraph(input[i])) {
			if (j <= LINE_STOP - 2) {
				printf(option.enable_hex ? "%x" : "%o", input[i]);
				j += 2;
			} else {
				putchar('\n');
				printf(option.enable_hex ? "%x" : "%o", input[i]);
				j = 4;
			}
		}
		else {
			putchar(input[i]);
			j++;
		}
	}
	putchar('\n');
	return 0;
}

void scanargs(int argc, char **argv) {
	option.enable_hex = 1;
	while (--argc)
		if (**++argv == '-')
			while (*++*argv != '\0')
				switch (**argv) {
					case 'o':
						option.enable_hex = 0;
						option.enable_oct = 1;
						break;
					case 'x':
						option.enable_hex = 1;
						option.enable_oct = 0;
						break;
					default:
						break;
				}
}

void warning(const char *msg) {
	printf("warning: %s\n", msg);
}