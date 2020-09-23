/* print an integer in decimal */

#include "stdio.h"

#define INT 123456

void printd(int n);

int main(void) {
	printd(INT);
	putchar('\n');
	return 0;
}

void printd(int n) {
	if (n < 0) {
		putchar('-');
		n *= -1;
	}

	if (n / 10)
		printd(n / 10);
	printf("%d", n % 10);
}
