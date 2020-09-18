/* Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the rightmost n
 * bits of y, leaving the other bits unchanged. */

#include "stdio.h"

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y);
unsigned digit(unsigned num);


int main(void) {
	unsigned x = 5514;   // 1 0101 1000 1010
	unsigned p = 4;  // right-adjusted, starting at 0
	unsigned n = 19;
	unsigned y = 1885;   //   0111 0101 1101
	/* expect               1 0111 1010 1010 = 6058 */

	printf("%u\n", setbits(x, p, n, y));
}


unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y) {
	if (p < n)
		perror("`p` shouldn't less than `n`");
	if (digit(x) < p + 1) {
		printf("`x`'s digit: %u\n", digit(x));
		perror("`x`'s digit isn't fit for `p`");
	}
	if (digit(y) < n) {
		printf("`y`'s digit: %u\n", digit(y));
		perror("`y`'s digit isn't fit for `n`");
	}
	return x & ~(~(~(unsigned)0 << n) << (p-n+1)) | (y & ~(~(unsigned)0 << n)) << (p-n+1);
}


/* Return an unsigned integer's digits */
unsigned digit(unsigned num) {
	unsigned i;
	for (i = 0; num % 2 != 0 || num / 2 != 0; ++i)
		num /= 2;
	return i;
}