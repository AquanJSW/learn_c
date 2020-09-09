/* input to one word per line */

#include <stdio.h>

#define OUT 0 // outside one word
#define IN  1 // inside one word

int main() {
    int state = OUT;
    int c;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN)
                putchar('\n');
            state = OUT;
        }
        else if (state == OUT) {
            putchar(c);
            state = IN;
        }
        else if (state == IN) {
            putchar(c);
        }
    }
}
