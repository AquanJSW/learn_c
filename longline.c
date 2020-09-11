/* Find the longest line in inputs */

#include <stdio.h>

#define MAXLEN 1000 // max length of line

int getline_(char s[], int lim);
int copy(char src[], char dst[]);


int main() {
    char s[MAXLEN];
    char slongest[MAXLEN];
    int len;
    int max;

    max = 0;
    printf("Inputs:\n");
    while ((len = getline_(s, MAXLEN)) > 0) {
        if (len > max) {
            copy(s, slongest);
            max = len;
        }
    }

    if (max > 0) {
        printf("\nlongest line:\n%s", slongest);
    }
    return 0;
}


/* Inputs captor. Return line's length */
int getline_(char s[], int lim) {
    int c, i;
    
    for (i = 0; ((c=getchar())!=EOF) && (c!='\n') && (i<lim-1); ++i)  // `i<lim-1` guarantees that there are at least 2 positions in `s` that haven't been used
        s[i] = c;
    if (c == '\n') {
        s[i] = '\n';
        ++i;
    }
    s[i] = '\0';
    return i;   // cause '\0' shouldn't be count as a part of the length of a string,so `i+1 - 1 = i`
}


/* String copy */
int copy(char src[], char dst[]) {
    int i;
    for (i = 0; (dst[i]=src[i]) != '\0'; ++i)
        ;
    dst[i] = '\0';
    return 0;
}
