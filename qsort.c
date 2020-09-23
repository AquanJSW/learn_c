/* quick sort */

#include "stdio.h"

void swap(int v[], size_t i, size_t j);
void qsort(int v[], size_t left, size_t right);

int main(void) {
	int v[] = {1, 5, 2, 6, 2, 1, 4, 6, 9, 3, 5, 0};
	size_t left = 0;
	size_t right = sizeof(v)/4 - 1;
	qsort(v, left, right);

	for (size_t i = 0; i <= right; i++)
		printf("%d ", v[i]);
}

void qsort(int v[], size_t left, size_t right) {
	size_t last;   // 最后一个小于参考值的元素的下标，初始值为参考值的下标

	// stop recursion when the set contains less than 2 elements
	if (left >= right)
		return;

	swap(v, left, (left+right)/2);
	last = left;
	for (size_t i = last+1; i <= right; i++)
		if (v[i] < v[left])
			swap(v, i, ++last);

	swap(v, last, left);    // cause v[left] >= v[last], left <= last

	qsort(v, left, last);
	qsort(v, last+1, right);
}

void swap(int v[], size_t i, size_t j) {
	int tmp;

	tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}
