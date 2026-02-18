#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 65

void convertToBase(int decimalNumber, int base, char *convertString) {
    char symbols[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char reversed[MAX_DIGITS];
    int index = 0;
    int negative = 0;

    if (decimalNumber == 0) {
        strcpy(convertString, "0");
        return;
    }
    if (decimalNumber < 0) {
        negative = 1;
        decimalNumber = -decimalNumber;
    }
    while (decimalNumber > 0) {
        int remainder = decimalNumber % base;
        reversed[index++] = symbols[remainder];
        decimalNumber = decimalNumber / base;
    }
    if (negative) {
        reversed[index++] = '-';
    }
    reversed[index]='\0';
    int length = strlen(reversed);
    for (int i =0; i < length; i++) {
        convertString[i] = reversed[length-i-1];
    }
    convertString[length] = '\0';
}

void clearInput() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}
int main() {
    int decimalNumber;
    int base;
    char convertedString[MAX_DIGITS];
    while (1) {
        printf("Please enter a decimal number: ");
        if (scanf("%d", &decimalNumber) == 1) {
            clearInput();
            break;
        } else {
            printf("Error: You must enter a decimal number!\n");
            clearInput();
        }
    }
    while (1) {
        printf("Enter the base of the number system (from 2 to 36): ");
        if (scanf("%d", &base) == 1 && base >= 2 && base <= 36) {
            clearInput();
            break;
        } else {
            printf("Error: You must enter a valid base!\n");
            clearInput();
        }
    }
    convertToBase(decimalNumber, base, convertedString);
    printf("Result: %s\n", convertedString);
    return 0;
}
