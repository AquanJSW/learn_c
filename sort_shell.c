/* Shell sort */

#include "stdio.h"

void shellsort(int v[], int n);

int main(void) {
	int v[] = {13, 14, 94, 33, 82, 25, 59, 94, 65, 23, 45, 27, 73, 25, 39, 10};
	int i;

	shellsort(v, 11);
	for (i = 0; i < 11; ++i)
		printf("%d ", v[i]);
	putchar('\n');

	return 0;
}


void shellsort(int v[], int n) {
	int step, i, j;
	int temp;

	for (step = n/2; step > 0; step /= 2) { // step continuously decreases until to be 1
		for (i = step; i < n; ++i) {
			/* 每次换位后都要按步长反向传播以保证较小值可以以当前所能达到的最快速度，尽可能恢复原位 */
			for (j = i-step; v[j] > v[j+step] && j >= 0; j -= step) {
				temp = v[j];
				v[j] = v[j+step];
				v[j+step] = temp;
			}
		}
	}
}