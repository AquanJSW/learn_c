/* Write a function expand(s1,s2) that expands shorthand notations like a-z in
 * the string s1 into the equivalent complete list abc...xyz in s2. Allow for
 * letters of either case and digits, and be prepared to handle cases like
 * a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken
 * literally. */

#include "stdio.h"
#include "string.h"

#define MAX 1000
#define TEXT "Full alphabets: a-z, uppercase version: A-Z. Note to distinct "\
"the cases like 'well-prepared' and 'z-b', also `a-b-c`, `a-z0-9`, `-a-z`"

const char EXCEPTION[] = "-+/*.=";
size_t j;

void expand(const char s1[], char s2[]);
void subexpand(char s[], char start, char stop);
int isuppercase(char c);
int islowercase(char c);

int main(void) {
	char s1[] = TEXT;
	char s2[MAX];

	expand(s1, s2);
	printf("Before:\n%s\n", s1);
	printf("After:\n%s\n", s2);
	return 0;
}


void expand(const char s1[], char s2[]) {
	size_t i;

	for (i = 0; s1[i] != '\0'; ++i) {
		if (s1[i] == '-' && i >=1) {
			if ((i == 1 || i > 1 && !islowercase(s1[i-2]) &&
			!isuppercase(s1[i-2]) && !strchr(EXCEPTION, s1[i-2])
			) && (islowercase(s1[i-1]) && islowercase(s1[i+1]) ||
			isuppercase(s1[i-1]) && isuppercase(s1[i+1])
			) && !islowercase(s1[i+2]) && !isuppercase(s1[i+2]) &&
			!strchr(EXCEPTION, s1[i+2]) && s1[i-1] < s1[i+1]) {
				subexpand(s2, s1[i-1], s1[i+1]);
				continue;
			} else
				s2[j++] = s1[i];
		} else
			s2[j++] = s1[i];
	}
}


int isuppercase(char c) {
	return c>='A' && c<='Z' ? 1 : 0;
}


int islowercase(char c) {
	return c>='a' && c<='z' ? 1 : 0;
}


void subexpand(char s[], char start, char stop) {
	j--;
	for (; start < stop; start++)
		s[j++] = start;
}