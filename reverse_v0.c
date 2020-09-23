/* Exercise 4-13. Write a recursive version of the function reverse(s), which
 * reverses the string s in place. */

#include "stdio.h"
#include "string.h"

void swap(char s[], size_t i, size_t j);
void reverse(char s[]);

int main(void) {
	char s[] = "Nice";
	printf("Origin:\t\t%s\n", s);
	reverse(s);
	printf("Reversed:\t%s\n", s);
	return 0;
}

void reverse(char s[]) {
	static size_t i;

	if (i <= strlen(s)/2) {
		swap(s, i, strlen(s) - i - 1);
		i++;
		reverse(s);
	}
}

void swap(char s[], size_t i, size_t j) {
	char tmp;
	tmp = s[i];
	s[i] = s[j];
	s[j] = tmp;
}