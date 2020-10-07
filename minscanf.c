/* Exercise 7-4. Write a private version of scanf analogous to minprintf from
 * the previous section. */

#include "stdio.h"

int main(void) {
	int iarg;
	double earg;
	char sarg[100];
	char yy[10], mm[10], dd[10];

	while (scanf("%s/%s/%s", yy, mm, dd) != 3);
	printf("%s, %s, %s", yy, mm, dd);
}