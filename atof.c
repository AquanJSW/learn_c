/* Exercise 4-2. Extend atof to handle scientific notation of the form
 * 123.45e-6
 * where a floating-point number may be followed by e or E and an optionally
 * signed exponent. */

#include "stdio.h"
#include "ctype.h"

int main(void) {
	double atof(const char s[]);
	char s[] = "123.45e-6";

	printf("Origin: \"%s\"\n", s);
	printf("After: %g\n", atof(s));

	return 0;
}


double atof(const char s[]) {
	double power(double base, double exp);
	size_t i;
	char sign;
	int exp;
	double val, multiple;

	// skip spaces
	for (i = 0; isspace(s[i]); i++)
		;
	// judge sign
	sign = s[i]=='-' ? -1 : 1;
	if (s[i] == '-' || s[i] == '+')
		i++;

	// before dot
	val = 0;
	for (; isdigit(s[i]); i++)
		val = val * 10 + s[i] - '0';

	// decimal part, if exists
	multiple = 1;
	if (s[i] == '.')
		for (i++; isdigit(s[i]); i++) {
			val = val * 10 + s[i] - '0';
			multiple *= 0.1;
		}

	// exponent part, if exists
	if (s[i] == 'E' || s[i] == 'e') {
		exp = 0;
		i++;
		if (s[i] == '-') {
			for (i++; isdigit(s[i]); i++)
				exp = exp * 10 + s[i] - '0';
			exp *= -1;
		} else {
			if (s[i] == '+')
				i++;
			for (i++; isdigit(s[i]); i++)
				exp = exp * 10 + s[i] - '0';
		}
		multiple *= power(10, exp);
	}

	return sign * val * multiple;
}


/* Return base in the power of exp */
double power(double base, double exp) {
	double val;
	size_t i;
	char sign;

	sign = exp < 0 ? -1 : 1;
	exp *= sign;

	val = 1;
	for (i = 0; i < exp; i++) {
		val *= base;
	}

	return sign<0 ? 1/val : val;
}