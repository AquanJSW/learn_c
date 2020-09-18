/* Write an alternative version of squeeze(s1,s2) that deletes each character in s1 that matches any character in
 * the string s2. */

#include "stdio.h"
#include "string.h"

void squeeze(char *s1, char *s2);


int main(void) {
	char s1[] = "Hui, Hu;, Ling!";
	char s2[] = ", ;!";

	printf("Before squeeze: '%s'\n", s1);
	squeeze(s1, s2);
	printf("After squeeze: '%s'\n", s1);
}


/* Squeeze */
void squeeze(char *s1, char *s2) {
	size_t i, j;

	for (i = j = 0; s1[i] != '\0'; ++i)
		if (!strchr(s2, s1[i]))
			s1[j++] = s1[i];

	s1[j] = '\0';
}
