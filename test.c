#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>

#define frand() (double) rand() / (RAND_MAX+1.0)
int main(void) {
	printf("%f\n", frand());
}
