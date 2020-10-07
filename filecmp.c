/* Exercise 7-6. Write a program to compare two files, printing the first line
 * where they differ. */

#include "stdio.h"
#include "string.h"

#define MAXLINELEN 10000
#define DEBU

int main(int argc, char **argv) {

#ifdef DEBUG
#include "unistd.h"
	argc = 3;
	const char *argv_[3] = {
			"./filecmp",
			"cat.c",
			"cfh.c"
	};
	argv = argv_;

	char buffer[100];
	getcwd(buffer, 100);
	printf("1111111%s", buffer);
#endif

	const char *usage = "usage: filecmp FILE0 FILE1.";
	char line[2][MAXLINELEN];
	char *prog = *argv;
	FILE *fp[2];

	if (argc != 3) {
		fprintf(stderr, "%s\n", usage);
		return 1;
	}
	while (--argc)
		if ( !(fp[2-argc] = fopen(*++argv, "r")) ) {
			fprintf(stderr, "%s: failed to read file %s.\n", prog, *argv);
			return 1;
		}

	while ((fgets(line[0], MAXLINELEN, fp[0])) &&
	(fgets(line[1], MAXLINELEN, fp[1])))
		if (strcmp(line[0], line[1])) {
			printf("First line where they differ:\n%s%s", line[0], line[1]);
			return 0;
		}
	return 0;
}