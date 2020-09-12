/* Write a program to remove trailing blanks and tabs from each line of input, and to delete
 * entirely blank lines.
 * For the situation "\t "，doesn't work. */

#include <stdio.h>

#define MAXLEN 1000 // max length of one line

int copy(char src[], char dst[]);
int getline_(char line[], int lim);


int main() {
    int len;    // use length of one line to judge if the current line is at the EOF
    char line[MAXLEN];
    char lines[MAXLEN][MAXLEN];
    int i, j;

    printf("Inputs:\n");

    for (i = 0; (len = getline_(line, MAXLEN)) > 0;)
        if (len > 1)
            copy(line, lines[i++]);

    printf("\n\nAfter filtering:\n");

    for (j = 0; j < i; ++j)
        printf("%s", lines[j]);
}


/* Line captor.
 * Filtering trailing white characters
 * Return length of a line. */
int getline_(char line[], int lim) {
    char pure;      // flag of blank lines
    int c, prec;    // current character, previous character
    int i;

    for (pure = 1, i = 0; (i<lim-1) && ((c=getchar())!=EOF) && (c!='\n');) {
        if (pure == 1)
            if ((c != ' ') && (c != '\t'))
                pure = 0;
        if (i == 0)
            prec = c;
        if ((prec == ' ' && c == ' ') || (prec == '\t' && c == '\t'))
            ;
        else
            line[i++] = c;
        prec = c;
    }

    if (c == '\n')
        line[i++] = '\n';

    line[i] = '\0';

    return i;
}


/* Copy lines */
int copy(char src[], char dst[]) {
    int i;

    for (i = 0; (dst[i] = src[i]) != '\0'; ++i)
        ;

    return 0;
}
