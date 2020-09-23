/* squeeze a string */

#include "stdio.h"

void strsqz(char s[], size_t dist) {
	size_t i;

	for (i = dist; s[i] != '\0'; i++)
		s[i-dist] = s[i];
	s[i-dist] = '\0';
}
