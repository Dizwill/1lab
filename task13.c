#include <limits.h>
#include <stdio.h>

int symbolToDigit(char symbol) {
    if (symbol >= '0' && symbol <= '9') return symbol - '0';
    if (symbol >= 'A' && symbol <= 'Z') return symbol - 'A' + 10;
    if (symbol >= 'a' && symbol <= 'z') return symbol - 'a' + 10;
    return -1;
}
int convertString_toInt (const char *numberStr, int base, int *error) {
    int decimalValue = 0;
    int sign  = 1;
    *error = 0;
    int hasDigit = 0;
    if (*numberStr == '-') {
        sign = -1;
        numberStr++;
    } else if (*numberStr == '+') {
        numberStr++;
    }
    if (*numberStr == '\0') {
        *error = 1;
        return 0;
    }
    while (*numberStr) {
        int digit_value = symbolToDigit(*numberStr);
        if (digit_value < 0 || digit_value >= base) {
            *error = 1;
            return 0;
        }
        if (decimalValue > (INT_MAX - digit_value) / base) {
            *error = 2;
            return 0;
        }
        decimalValue = decimalValue * base + digit_value;
        numberStr++;

        if (digit_value >= 0) {
            hasDigit = 1;
        }
    }
    if (!hasDigit) {
        *error = 1;
        return 0;
    }
    return sign * decimalValue;
}
int main() {
    char inputNumber[50];
    int numberBase;
    int decimalNumber;
    int conversionError;

    while (1) {
        printf("Enter the base of the number system (2-36): ");
        if (scanf("%d", &numberBase) != 1) {
            printf("Please enter a number!\n");
            while (getchar() != '\n');
            continue;
        }
        if (numberBase < 2 || numberBase > 36) {
            printf("Error: Base must be between 2 and 36!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        break;
    }
    while (1) {
        printf("Enter the number in the base system %d: ", numberBase);
        scanf("%s", inputNumber);

        decimalNumber = convertString_toInt(inputNumber, numberBase, &conversionError);
        if (conversionError) {
            printf("Please enter a valid number for base!\n");
            continue;
        }
        break;
    }
    printf("Number in the decimal system: %d\n", decimalNumber);
    return 0;
}
