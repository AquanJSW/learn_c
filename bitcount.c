/* In a two’s complement number system, x &= (x-1) deletes the rightmost 1-bit in x. Explain why. Use this
 * observation to write a faster version of bitcount, that is, counting the number of bit 1.
 *
 * Suppose that `x` has n bit 1s, it's easy to get that n-- every time after x&=(x-1) */

#include "stdio.h"

unsigned bitcount(unsigned x);
void binprint(unsigned x);

int main(void) {
	unsigned x = 19999;

	binprint(x);
	putchar('\n');
	printf("The number of bit 1: %u\n", bitcount(x));
}


unsigned bitcount(unsigned x) {
	unsigned c;

	c = 0;
	for (; x != 0; x &= (x-1))
		++c;

	return c;
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
