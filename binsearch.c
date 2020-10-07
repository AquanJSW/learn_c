/* Exercise 3-1. Our binary search makes two tests inside the loop, when one
 * would suffice (at the price of more tests outside.) Write a version with
 * only one test inside the loop and measure the difference in run-time. */

#include "stdio.h"

#define ENABLE_ORIGIN  0

int binsearch(int x, const int v[], int n);

int main(void) {
	int x = 1;
	int v[] = {1, 2, 3, 4, 5, 6, 7, 8};

	printf("Position of %d: %d\n", x, binsearch(x, v, 8));
	return 0;
}


/* Binary search. */
int binsearch(int x, const int v[], int n) {
	int low, mid, high;

	low = 0;
	high = n - 1;
#if ENABLE_ORIGIN == 1
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;
#else
	while (low < high) {
		mid = (low + high) / 2;
		if (x <= v[mid])
			high = mid;
		else
			low = mid + 1;
	}
	if (x == v[high])
		return high;
	return -1;
#endif
}