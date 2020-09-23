/* Types' size or range */

#include "stdio.h"
#include <limits.h>
#include "float.h"

#define SAME 0
#define DIFF 1
#define tprintf(type) printf(#type "\t%d\n", type)

int range(char s[]);
int strcmp_(const char s[], const char d[]);
long unsigned int power(long unsigned int base, long unsigned int exp);

int main(void) {
	tprintf(CHARCLASS_NAME_MAX);
	printf("CHAR_BIT\t%d\n", CHAR_BIT);
	printf("CHAR_MAX\t%d\n", CHAR_MAX);
	printf("CHAR_MIN\t%d\n", CHAR_MIN);
	printf("SCHAR_MAX\t%d\n", SCHAR_MAX);
	printf("SCHAR_MIN\t%d\n", SCHAR_MIN);
	printf("SHRT_MAX\t%d\n", SHRT_MAX);
	printf("SHRT_MIN\t%d\n", SHRT_MIN);
	printf("INT_MAX\t\t%d\n", INT_MAX);
	printf("INT_MIN\t\t%d\n", INT_MIN);
	printf("LONG_MAX\t%ld\n", LONG_MAX);
	printf("LONG_MIN\t%ld\n", LONG_MIN);
	printf("UCHAR_MAX\t%d\n", UCHAR_MAX);
	printf("USHRT_MAX\t%d\n", USHRT_MAX);
	printf("UINT_MAX\t%ld\n", UINT_MAX);
	printf("ULONG_MAX\t%lu\n", ULONG_MAX);
	putchar('\n');
	printf("FLT_RADIX\t\t%d\n", FLT_RADIX);
	printf("FLT_ROUND\t\t%d\n", FLT_ROUNDS);
	printf("FLT_DIG\t\t\t%d\n", FLT_DIG);
	printf("FLT_EPSILON\t\t%e\n", FLT_EPSILON);
	printf("FLT_MANT_DIG\t%d\n", FLT_MANT_DIG);
	printf("FLT_MAX\t\t\t%e\n", FLT_MAX);
	printf("FLT_MAX_EXP\t\t%d\n",FLT_MAX_EXP);
	printf("FLT_MIN\t\t\t%e\n", FLT_MIN);
	printf("FLT_MAX_EXP\t\t%d\n", FLT_MIN_EXP);
	printf("DBL_DIG\t\t\t%d\n", DBL_DIG);
	printf("DBL_EPSILON\t\t%e\n", DBL_EPSILON);
	printf("DBL_MANT_DIG\t%d\n", DBL_MANT_DIG);
	printf("DBL_MAX\t\t\t%e\n", DBL_MAX);
	printf("DBL_MAX_EXP\t\t%d\n",DBL_MAX_EXP);
	printf("DBL_MIN\t\t\t%e\n", DBL_MIN);
	printf("DBL_MAX_EXP\t\t%d\n", DBL_MIN_EXP);
	putchar('\n');
	putchar('\n');
	printf("Compute the range of char, short, int and long variables, both signed and unsigned\n");
	/* Suppose that we known the bit of which: 8, 16, 32, 64 */
	range("char");
	range("short");
	range("int");
	range("long");
}


/* Print the range of given bits, both signed and unsigned. */
int range(char s[]) {
	if (strcmp_(s, "char") == SAME) {
		printf("Range of signed char: [%ld, %lu]\n", -power(2, 7), power(2, 7) - 1);
		printf("Range of unsigned char: [0, %lu]\n", power(2, 8) - 1);
	} else if (strcmp_(s, "short") == SAME) {
		printf("Range of signed short: [%ld, %lu\n", -power(2, 15), power(2, 15) - 1);
		printf("Range of unsigned short: [0, %lu]\n", power(2, 16) - 1);
	} else if (strcmp_(s, "int") == SAME) {
		printf("Range of signed int: [%ld, %lu]\n", -power(2, 31), power(2, 31) - 1);
		printf("Range of unsigned int: [0, %lu]\n", power(2, 32) - 1);
	} else if (strcmp_(s, "long") == SAME) {
		printf("Range of signed long: [%ld, %lu]\n", -power(2, 63), power(2, 63) - 1);
		printf("Range of unsigned long: [0, %lu]\n", power(2, 64) - 1);
	} else {
		printf("Unsupported type\n");
	}
}


/* String compare
 * Return 0 if same, 1 otherwise. */
int strcmp_(const char s[], const char d[]) {
	int i;
	for (i = 0; s[i] == d[i] && s[i] != '\0' && d[i] != '\0'; i++)
		;
	if (s[i] == d[i] && s[i] == '\0')
		return SAME;
	else
		return DIFF;
}


/* Power, only positive integers */
long unsigned int power(const long unsigned int base, long unsigned int exp) {
	long unsigned int r;
	for (r = 1; exp > 0; --exp) {
		r *= base;
	}
	return r;
}