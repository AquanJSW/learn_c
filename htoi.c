/* Hexadecimal to integer. */

#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"

void str2lower(char *dst);
unsigned long long power(unsigned long long base, unsigned long long exp);


int main(void) {
	char hex[] = "0xX0xD0x80x60x70x80x80x80x70x90x20xA0x10x40x3";
	char h;
	unsigned long long len = strlen(hex) / 3;
	unsigned long long dec;
	size_t i = i;

	str2lower(hex);

	dec = 0;
	for (i = 0; i < len; ++i) {
		h = *(hex + (i + 1) * 3 - 1);
		if (h >= '0' && h <= '9')
			dec += (h - '0') * power(16, len - i - 1);
		else if (h >= 'a' && h <= 'f')
			dec += (h - 'a' + 10) * power(16, len - i - 1);
		else {
			perror("invalid hexadecimal");
			exit(EXIT_FAILURE);
		}
	}
	printf("%llu\n", dec);

}


/* Convert string to lowercase version. */
void str2lower(char *dst) {
	size_t i;
	for (i = 0; dst[i] != '\0'; ++i)
		dst[i] = tolower(dst[i]);
}


/* Power */
unsigned long long power(unsigned long long base, unsigned long long exp) {
	unsigned long long out;

	out = 1;
	for (; exp > 0; exp--) {
		out *= base;
	}
	return out;
}