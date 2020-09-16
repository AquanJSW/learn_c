/* Write a program to check a C program for rudimentary syntax errors like unmatched parentheses, brackets
 * and braces. Don’t forget about quotes, both single and double, escape sequences, and comments. (This program is
 * hard if you do it in full generality.)
 *
 * Result: Not OK. */

#include "stdio.h"

#define STACK   100
#define TABSTOP 4
#define NONE    -1
#define QUOSI   0
#define QUOBI   1
#define CMTSIN  2
#define CMTMUL  3
#define PARE    4
#define BRAK    5
#define BRAC    6

const unsigned char ESCAPE[] = {'?', 'a', 'b', 'f', 'b', 'r', 't', 'v'};

int findchar(const unsigned char s[], unsigned char c);
int raise(int type, unsigned int row, unsigned int col);
int krcpush(int *krc, int key, int row, int col);

int main(void) {
	int _krc[STACK][3];  // keyword type
	int *krc;
	int c, prec;
	int col, row;

	for (krc = *_krc, col = -1, row = 0, *krc = NONE, *(krc + 1) = *(krc + 2) = 0, prec = '\0';
	(c = getchar()) != EOF; prec = c) {
		if (prec == '\n') {
			++row;
			col = 0;
		} else if (c == '\t') {
			col += TABSTOP;
		} else {
			++col;
		}

		switch (c) {
			case '\'':
				if (*krc == QUOBI || *krc == CMTMUL || *krc == CMTSIN || (*krc == QUOSI && prec == '\\')) { ;
				} else if (*krc == QUOSI && prec != '\\') {
					krc -= 3;
				} else {
					krcpush(krc, QUOSI, row, col);
					krc += 3;
				}
				break;
			case '\"':
				if (*krc == CMTMUL || *krc == CMTSIN || *krc == QUOSI) { ;
				} else if (*krc == QUOBI) {
					if (prec != '\\')
						krc -= 3;
				} else {
					krcpush(krc, QUOBI, row, col);
					krc += 3;
				}
				break;
			case '/':
				if (*krc == QUOBI || *krc == QUOSI || *krc == CMTSIN || (*krc == CMTMUL && prec != '*')) { ;
				} else if (*krc == CMTMUL && prec == '*') {
					krc -= 3;
				} else if (prec == '/') {
					krcpush(krc, CMTSIN, row, col);
					krc += 3;
				}
				break;
			case '*':
				if (*krc != QUOBI && *krc != QUOSI && *krc != CMTMUL && *krc != CMTSIN && prec == '/') {
					krcpush(krc, CMTMUL, row, col);
					krc += 3;
				}
				break;
			case '(':
				if (*krc != QUOSI && *krc != QUOBI && *krc != CMTMUL && *krc != CMTSIN) {
					krcpush(krc, PARE, row, col);
					krc += 3;
				}
				break;
			case ')':
				if (*krc == PARE) {
					krc -= 3;
				}
				break;
			case '[':
				if (*krc != QUOSI && *krc != QUOBI && *krc != CMTMUL && *krc != CMTSIN) {
					krcpush(krc, BRAK, row, col);
					krc += 3;
				}
				break;
			case ']':
				if (*krc == BRAK) {
					krc -= 3;
				}
				break;
			case '{':
				if (*krc != QUOSI && *krc != QUOBI && *krc != CMTMUL && *krc != CMTSIN) {
					krcpush(krc, BRAC, row, col);
					krc += 3;
				}
				break;
			case '}':
				if (*krc == BRAC) {
					krc -= 3;
				}
				break;
			case '\n':
				if (*krc == CMTSIN) {
					krc -= 3;
				}
				break;
			default:
				if ((*krc == QUOSI || *krc == QUOBI) && prec == '\\') {
					if (findchar(ESCAPE, c) == NONE) {
						printf("Escape character error at: %d, %d\n", row, col);
						return 0;
					}
				} else if (*krc != QUOSI && *krc != QUOBI && *krc != CMTSIN && *krc != CMTMUL && prec == '/') {
					printf("Single-line comment error at: %d, %d\n", row, col);
					return 0;
				}
		}
	}

	raise(*krc, row, col);
	return 0;
}


/* Find the position of character `c` in `s`; if not exist, return -1 */
int findchar(const unsigned char s[], unsigned char c) {
	int sc;
	int i;
	for (i = 0; (sc=s[i]) != '\0'; ++i)
		if (sc == c)
			return i;
	return NONE;
}


/* Raise errors */
int raise(int type, unsigned int row, unsigned int col) {
	switch (type) {
		case QUOSI:
			printf("Error with single quotes at: %d, %d\n", row, col);
			break;
		case QUOBI:
			printf("Error with double quotes at: %d, %d\n", row, col);
			break;
		case CMTSIN:
			printf("Error with single-line comment at: %d, %d\n", row, col);
			break;
		case CMTMUL:
			printf("Error with multi-line comment at: %d, %d\n", row, col);
			break;
		case PARE:
			printf("Error with parentheses at: %d, %d\n", row, col);
			break;
		case BRAK:
			printf("Error with brackets at: %d, %d\n", row, col);
			break;
		case BRAC:
			printf("Error with braces at: %d, %d\n", row, col);
		default:
			;
	}
}


/* Push krc */
int krcpush(int *krc, int key, int row, int col) {
	krc += 3;
	*krc = key;
	*(krc + 1) = row;
	*(krc + 2) = col;
}