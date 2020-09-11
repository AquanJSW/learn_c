/* Write a program to print all input lines that are longer than 80 characters */

#include <stdio.h>

#define MAXLEN 1000   // max length of one line

int copy(char src[], char dst[]);
int getline_(char s[], int lim);


int main() {
    int len;
    int i = 0;
    char s[MAXLEN];
    char slong[MAXLEN][MAXLEN];

    printf("Inputs:\n");
    while ((len = getline_(s, MAXLEN)) > 0)
        if (len > 80)
            copy(s, slong[i++]);

    if (i > 0) {
        printf("\n\nLines longer than 80 characters:\n");
        while (i >= 0)
            printf("%s\n", slong[--i]);
    }
}


/* Line captor & Return line's length */
int getline_(char s[], int lim) {
    int c, i;

    for(i = 0; (i<lim-1) && ((c=getchar())!=EOF) && (c!='\n'); ++i)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';

    return i;
}


/* Copy line from `src` to `dst` */
int copy(char src[], char dst[]) {
    int i;

    for (i = 0; (dst[i] = src[i]) != '\0'; ++i)
        ;

    return 0;
}
