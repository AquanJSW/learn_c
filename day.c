#include "stdio.h"

int day_of_year(int year, char month, int day);
char monthday(int year, int day, char *m, char *d);

int main(void) {
	char m, d;
	printf("day of year: %d\n",
		day_of_year(2020, 9, 25));

	monthday(2020, day_of_year(2020, 9, 25), &m, &d);
	printf("month: %d, day: %d\n", m, d);
	return 0;
}


static char daytab[][12] = {
		{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
		{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, char month, int day) {
	char leap, i;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

	if (month < 1 || month > 12)
		return 0;   // wrong month

	// Exercise 5-9. Rewrite the routines day_of_year and month_day with
	// pointers instead of indexing.
	if (day > *(daytab + leap * 12 + month - 1))
		return -1;  // wrong day

	for (i = 0; i < month - 1; i++)
		day += daytab[leap][i];
	return day;
}

char monthday(int year, int day, char *m, char *d) {
	char leap, i;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

	if (day > (leap ? 366 : 365))
		return 0;   // wrong day

	for (i = 0; day > daytab[leap][i]; i++)
		day -= daytab[leap][i];

	*m = i + 1;
	*d = day;
	return 1;   // fin
}

