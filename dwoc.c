/* digit, white space, others counter */

#include <stdio.h>

int main() {
    int nd[10], nw, noth;
    int i, c;

    for (i = 0; i < 10; ++i)
        nd[i] = 0;
    nw = noth = 0;
    
    while ((c = getchar()) != EOF) {
        if (c >= '0' && c <= '9')
            ++nd[c - '0'];
        else if (c == ' ' || c == '\n' || c == '\t')
            ++nw;
        else
            ++noth;
    }

    printf("Digit: ");
    for (i = 0; i < 10; ++i)
        printf("%d ", nd[i]);
    putchar('\n');

    printf("White space: %d\nOthers: %d\n", nw, noth);
}
