#include <stdio.h>

long long power_fast(int base, unsigned int exponent) {
    long long result = 1;
    long long current_base = base;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= current_base;
        }
        current_base *= current_base;
        exponent /= 2;
    }
    return result;
}
int main(void) {
    int base;
    int temp_exponent;
    unsigned int exponent;
    long long result;
    printf("Enter an integer: ");
    if (scanf("%d", &base) != 1) {
        printf("Error: invalid integer input!\n");
        return 1;
    }
    while (getchar() != '\n');
    printf("Enter a non-negative power: ");
    if (scanf("%d", &temp_exponent) != 1) {
        printf("Error: invalid power input!\n");
        return 1;
    }
    if (temp_exponent < 0) {
        printf("Error: power cant be negative!\n");
        return 1;
    }
    while (getchar() != '\n');

    exponent = (unsigned int) temp_exponent;
    result = power_fast(base, exponent);
    printf("%d ^ %u = %lld\n", base, exponent, result);

    return 0;
}
