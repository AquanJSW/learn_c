/* hint: use UNIX `cat` for testing */

#include "stdio.h"
#include "string.h"

#define MAXLEN  1000    // max line length

int getline_(char *s, unsigned lim);

int main(int argc, char *argv[]) {
	const char *usage = "Usage: grep [OPTION] PATTERN\n"
    "OPTION:\n"
    "-h\n\tshow help\n"
    "-x\n\texcept mode\n"
    "-n\n\tprecede each printed line by its lines number\n";

	char c, except, number;
	char line[MAXLEN];  // line buffer
	int argc_, nfound, lineno;

	except = number = 0;    // flags
	argc_ = argc;
	/* parse options */
	while (--argc > 0 && **++argv == '-') {
		/* 'h'帮助选项必须为唯一的参数、唯一的选项 */
		if (argc == argc_ - 1 == 1 && (c = *++*argv) == 'h') {
			printf("%s", usage);
			return 0;
		}
		if (argc == argc_ - 1 == 1)
			--*argv;

		while ((c = *++*argv))  // each argv[i] is finished with '\0'
			switch (c) {
				case 'x':   // except
					except = 1;
					break;
				case 'n':   // number
					number = 1;
					break;
				default:
					printf("error: wrong options\n%s", usage);
					return -1;
			}
	}

	/* judging the number of left arguments */
	if (argc > 1) {
		printf("error: too many arguments\n%s", usage);
		return -1;
	} else if (argc < 1) {
		printf("error: too few arguments\n%s", usage);
		return -1;
	}

	nfound = 0; // the number of found lines
	lineno = 0; // input line number
	while (getline_(line, MAXLEN) > 0) {
		++lineno;
		if ((strstr(line, *argv) != NULL) != except) {
			++nfound;
			if (number)
				printf("%u ", lineno);
			printf("%s\n", line);
		}
	}
	return nfound;
}

int getline_(char *s, unsigned lim) {
	char *sp = s;
	int c;

	while (s - sp < lim && (*s++ = c = getchar()) != '\n' && c != EOF)
		;
	if (s - sp == lim)
		printf("warning: too long line length\n");
	*--s = '\0';
	return s - sp;
}
