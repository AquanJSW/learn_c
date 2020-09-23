/* get operator one by one in a line src, then save to dst, return operator type
 * */

#include "stdio.h"
#include "ctype.h"
#include "calc.h"

unsigned char getop(char src[], char dst[]) {
	size_t i, j;

	j = 0;
	// skip spaces
	for (i = 0; isblank(dst[j] = src[i]); i++)
		;

	// current operator isn't a number
	if (!isdigit(dst[j])) {
		switch (dst[j]) {
			case '+':
			case '-':
			case '/':
			case '*':
				strsqz(src, i+1);
				return dst[j];
			case '\0':
				return END;
			default:
				return NONE;
		}
	}

	// current operator is a number
	// deliver non-blank characters
	for (j++, i++; !isblank(dst[j] = src[i]) && dst[j] != '\0'; j++, i++)
		;

	strsqz(src, i); // keep the blank or '\0' alive
	dst[j] = '\0';
	return NUM;
}
