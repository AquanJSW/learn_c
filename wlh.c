/* print a histogram of the lengths of words in its inputs */

#include <stdio.h>

#define IN  1 // inside a word
#define OUT 0 // outside a word
#define ML  20  // max length
#define STYLE '_' // histogram style
#define DIST 4  // group distance of histogram
//
// HOW TO PARAMETERIZE THE FROMAT STRING IN `printf`??????????????????????????????????????????
//#define PRINTF0(dist) "%%-%dd", dist
//#define PRINTF(printf0, n) printf(printf0, #n)

int main() {
    int lw[ML];
    int state = OUT;
    int c;
    int l = 0;
    int i, j, k;
    int max;
    int lw_[ML];

    for (i = 0; i < ML; ++i)
        lw[i] = 0;

    /* count lengths of words in inputs */
    printf("Inputs:\n");
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN) {
                if (l >= ML) {
                    ++lw[0];  // count the number of word that the length of which exceed ML
                    l = 0;
                }
                else {
                    ++lw[l];
                    l = 0;
                }
            }
            state = OUT;
        }
        else if (state == OUT) {
            ++l;
            state = IN;
        }
        else if (state == IN)
            ++l;
    }

    /* find the length that has the max frequency of occurrence in inputs */
    max = 0;
    for (i = 1; i < ML; ++i) {
        if (lw[i] > lw[max]) {
            max = i;
        }
    }

    /* print histogram */
    for (i = 0; i < ML; ++i) {
        lw_[i] = lw[i];
    }

    for (i = lw[max]; i > 0; --i) {
        for (j = 0; j < ML; ++j) {
            if (lw_[j] == i) {
                putchar(STYLE);
                for (k = 1; k < DIST; ++k){
                    putchar(' ');
                }
                --lw_[j];
            }
            else {
                for (k = 0; k < DIST; ++k){
                    putchar(' ');
                }
            }
        }
        putchar('\n');
    }

    /* following code not good enough */
    for (i = 0; i < DIST * ML; ++i) {
        putchar('-');
    }
    putchar('>');
    putchar('\n');
    for (i = 0; i < ML; ++i) {
        printf("%-4d", lw[i]);  // waiting for better solution
    }
    printf("count\n");
    for (i = 0; i < ML; ++i) {
        printf("%-4d", i);
    }
    printf("length\n");

}

