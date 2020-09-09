#include <stdio.h>

int main() {
    int c;
    printf("Input a char: ");
    c = getchar();
    printf("Your input: ");
    putchar(c);
    putchar('\n');

    printf("Input a string: ");
    while ((c = getchar()) != EOF) {
        putchar(c);
    }
    putchar('\n');

    // count characters in input
    printf("Count\n");
    int cc = 0;
    while (getchar() != EOF) {
        cc++;
    }
    printf("%d\n", cc);
}
