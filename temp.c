/* Fahrentheit-Centigrade Tables */

#include <stdio.h>

int main(){
    const int LOWER = 0;
    const int UPPER = 300;
    const int STEP  = 20;
    int fahr = LOWER;
    int cent;

    printf("Fahrenheit\tCentigrade\n");
    while (fahr <= UPPER) {
        cent = 5 * (fahr-32) / 9;
        printf("%10d\t%10d\n", fahr, cent);
        fahr += STEP;
    }

    cent = LOWER;
    printf("Centigrade\tFahrenheit\n");
    while (cent <= UPPER) {
        fahr = cent * 9 / 5 + 32;
        printf("%10d\t%10d\n", cent, fahr);
        cent += STEP;
    }
}
