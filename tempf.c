/* Funtion version of Fahrenheit-Centigrade Tables */

#include <stdio.h>

#define LOWER   0
#define UPPER   300
#define STEP    20

int table(int fahr);

int main() {
    int fahr = LOWER;
    table(fahr);
    return 0;
}


int table(int fahr) {
    printf("Fahrenheit\tCentigrade\n");
    while (fahr <= UPPER) {
        printf("%10d\t%10d\n", fahr, 5*(fahr-32)/9);
        fahr += STEP;
    }
    return 0;
}
