/* Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments of
 * type t. (Block structure will help.) */

#include "stdio.h"

#define swap(t, x, y) {t tmp = (x); (x) = (y); (y) = tmp;}

int main(void) {
	int x = 1;
	int y = 2;

	printf("Before: (x, y) = (%d, %d)\n", x, y);
	swap(int, x, y);
	printf("After: (x, y) = (%d, %d)\n", x, y);
}