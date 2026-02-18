#include <stdio.h>

int main(void) {
    printf("Table of powers of numbers (1–6) from 1 to 10.\n");
    printf("Number |");
    for (int exponent = 1; exponent <= 10; exponent++) {
        printf("%5d |", exponent);
    }
    printf("\n");
    for (int number = 1; number <=6; number++) {
        printf("%5d |", number);
        for (int exponent = 1; exponent <= 10; exponent++) {
            int result = 1;
            for (int multiplying = 1; multiplying <= exponent; multiplying++ ) {
                result = result * number;
            }
            printf("%5d |", result);
        }
        printf("\n");
    }
    return 0;
}
