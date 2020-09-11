/* line, word and character counter */

#include <stdio.h>

#define IN   1  // inside a word
#define OUT  2  // outside a word

int main() {
    printf("Input string:\n");
    int lc, wc, cc; // counters
    int c;
    int state;
    lc = wc = cc = 0;
    state = OUT;

    while ((c = getchar()) != EOF) {
        ++cc;
        if (c == '\n')
            ++lc;
        
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++wc;
        }
    }
    putchar('\n');
    printf("line\tword\tcharacter\n");
    printf("%4d\t%4d\t%9d\n", lc, wc, cc);
}

