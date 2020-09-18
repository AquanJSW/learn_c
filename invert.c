/* Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted (i.e., 1 changed
 * into 0 and vice versa), leaving the others unchanged */

#include "stdio.h"

unsigned invert(unsigned x, unsigned p, unsigned n);
unsigned digit(unsigned num);


int main(void) {
	unsigned x = 5514;   // 1 0101 1000 1010
	unsigned p = 9;
	unsigned n = 5;
	// expect:              1 0110 0110 1010 = 5738

	printf("%u\n", invert(x, p, n));
	return 0;
}


unsigned invert(unsigned x, unsigned p, unsigned n) {
	if (p < n)
		perror("`p` shall not less than `n`");
	if (digit(x) < p + 1) {
		printf("`x`'s digit: %u\n", digit(x));
		perror("`x`'s digit isn't fit for `p`");
	}
	return x & ~(~(~(unsigned)0 << n) << (p-n+1)) | ~(x | ~(~(~(unsigned)0 << n) << (p-n+1)));
}


/* Return an unsigned integer's digits */
unsigned digit(unsigned num) {
	unsigned i;
	for (i = 0; num % 2 != 0 || num / 2 != 0; ++i)
		num /= 2;
	return i;
}
