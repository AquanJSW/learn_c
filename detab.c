/* Write a program detab that replaces tabs in the input with the proper number of blanks to space to the
 * next tab stop. */

#include <stdio.h>

#define TABSTOP 4
#define MAXLEN  1000    // max input length

int tabexpand(char s[], int *i);


int main(void) {
    int i;
    char c, s[MAXLEN];

    printf("Input:\n");
    for (i = 0; (c=getchar())!=EOF && i<MAXLEN-1;)
        if (c == '\t')
            tabexpand(s, &i);
        else
            s[i++] = c;

    printf("\n\nAfter tab expand:\n%s", s);
}


/* Expand tab to spaces */
int tabexpand(char s[], int *i) {
    int j;

    for (j = 0; j < TABSTOP; ++j)
        s[(*i)++] = ' ';

    return 0;
}
