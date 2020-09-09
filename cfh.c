/* Print a histogram of the frequency of different characters in inputs
 * For convenience, we only count alphabets */

#include <stdio.h>

#define STYLE '_' // histogram style
#define DIST  3   // group distance of histogram
#define NPIECE 200 // total pieces of histogram, not special meaning, just for visualization

int main() {
    int nchar[26];
    int freq[26];
    int piece[26];
    int i, j, k;
    int c;
    int nc = 0;
    int maxfc;

    for (i = 0; i < 26; ++i) {
        nchar[i] = 0;
    }

    /* count characters */
    printf("Inputs:\n");
    while ((c = getchar()) != EOF) {
        if (c >= 'a' && c <= 'z') {
            ++nchar[c-'a'];
            ++nc;
        }
    }

    /* find the alphabet of the max frequency */
    maxfc = 0;
    for (i = 0; i < 26; ++i) {
        if (nchar[i] > nchar[maxfc]) {
            maxfc = i;
        }
    }

    /* calculate frequency and piece of each alphabet */
    for (i = 0; i < 26; ++i) {
        freq[i] = nchar[i] * 100 / nc;
        piece[i] = nchar[i] * NPIECE / nc;
    }

    /* plot histogram */
    for (i = piece[maxfc]; i > 0; --i) {
        for (j = 0; j < 26; ++j) {
            if (piece[j] == i) {
                putchar(STYLE);
                for (k = 1; k < DIST; ++k) {
                    putchar(' ');
                }
                --piece[j];
            }
            else {
                for (k = 0; k < DIST; ++k) {
                    putchar(' ');
                }
            }
        }
        putchar('\n');
    }
    for (i = 0; i < DIST * 26; ++i) {
        putchar('-');
    }
    printf(">\n");
    for (i = 0; i < 26; ++i) {
        printf("%-3d", freq[i]);
    }
    printf("frequency(%%)\n");
    for (i = 0; i < 26; ++i) {
        printf("%-3c", (char)('a'+i));
    }
    printf("alphabet\n");
}
