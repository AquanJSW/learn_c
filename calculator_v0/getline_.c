#include "stdio.h"

size_t getline_(char line[], size_t lim) {
	size_t i;
	int c;

	for (i = 0; i < lim && (line[i]=c=getchar()) != '\n' && c != EOF; i++)
		;

	if (c == '\n' || c == EOF) {
		line[i] = '\0';
		return i;
	}
	printf("warning: out of length limit\n");
	line[--i] = '\0';
	return lim - 2;
}
