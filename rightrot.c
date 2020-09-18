/* Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n positions. */

#include "stdio.h"

unsigned rightrot(unsigned x, unsigned n);
void binprint(unsigned x);

int main(void) {
	unsigned x = 19987;
	unsigned n = 5;

	printf("Before right rotate %u positions:\t", n);
	binprint(x);
	putchar('\n');
	printf("After right rotate %u positions:\t\t", n);
	binprint(rightrot(x, n));
	putchar('\n');

	return 0;
}


unsigned rightrot(unsigned x, unsigned n) {
	for (; n > 0; n--) {
		if (x % 2) {
			x >>= 1;
			x |= ~(~(unsigned)0 >> 1);
		}
		else
			x >>= 1;
	}
	return x;
}


/* Print an unsigned integer in binary */
void binprint(unsigned x) {
	char bin[512];
	int i;

	i = 0;
	for (; x / 2 != 0 || x % 2 != 0;) {
		bin[i++] = (char)(x % 2) + '0';
		x /= 2;
	}

	for (--i; i >= 0; --i) {
		printf("%c", bin[i]);
		if (i % 4 == 0)
			printf(" ");
	}
}