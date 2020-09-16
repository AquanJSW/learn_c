#include <stdio.h>

int main(void) {
	int m[2][2] = {1, 2, 3, 4};
	int *p = *m;
	printf("%d\n", *(p));
	printf("%d\n", *(p+=2));
}
