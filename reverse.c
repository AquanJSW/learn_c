/* Write a function reverse(s) that reverses the character string s. Use it to write a program that reverses its input a line at a time. */

#include <stdio.h>

#define MAXLEN 1000     // max length of a line

int getline_(char line[], int lim);
int reverse(char s[]);
int copy(char src[], char dst[]);


int main() {
    char line[MAXLEN];
    char rlines[MAXLEN][MAXLEN];
    int i, j;
    int len;

    printf("Input:\n");
    for (i = 0; (len = getline_(line, MAXLEN)) > 0; ++i) {
        reverse(line);
        copy(line, rlines[i]);
    }

    printf("\n\nReverse line by line:\n");

    for (j = 0; j < i; ++j)
        printf("%s", rlines[j]);
}


/* Line captor.
 * Return length of a line. */
int getline_(char line[], int lim) {
    int c;
    int i;

    for (i = 0; (c=getchar()) != EOF && c!='\n' && i<lim-1; ++i)
        line[i] = c;

    if (c == '\n')
        line[i++] = '\n';

    line[i] = '\0';

    return i;
}


/* Reverse the line, and save to itself */
int reverse(char s[]) {
    int len;

    for (len = 0; s[len++] != '\0';)
        ;

    if (s[len-2] == '\n')
        len -= 2;

    char temp[len];
    int i;

    for (i = 0; i < len; ++i)
        temp[i] = s[i];

    for (i = 0; i < len; ++i)
        s[i] = temp[len - i - 1];

    return 0;
}


/* Copy line */
int copy(char src[], char dst[]) {
    int i;

    for (i = 0; (dst[i] = src[i]) != '\0'; ++i)
        ;

    return 0;
}
