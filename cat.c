/* analogy to UNIX cat */

#include "stdio.h"
#include "stdlib.h"

void filecopy(FILE *ofp, FILE *ifp);

int main(int argc, char **argv) {
	FILE *fp;
	char *prog = *argv;

	if (argc == 1) {
		filecopy(stdout, stdin);
		return 0;
	}

	while (--argc) {
		fp = fopen(*++argv, "r");
		if (!fp) {
			fprintf(stderr, "%s: failed to read file %s.\n", prog, *argv);
			exit(1);
		}
		filecopy(stdout, fp);
		fclose(fp);
	}
	return 0;
}

void filecopy(FILE *ofp, FILE *ifp) {
	int c;

	while ((c = getc(ifp)) != EOF)
		putc(c, ofp);
}
