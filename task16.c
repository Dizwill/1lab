#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 512
#define MAX_DIGITS 65
void convertToBase(int decimalNumber, int base, char *convertString) {
    char symbols[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
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
    reversed[index] = '\0';
    int length = index;
    for (int i = 0; i < length; i++) {
        convertString[i] = reversed[length - i - 1];
    }
    convertString[length] = '\0';
}
void clearInput() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}
void transpositionUsingConvert(const char *input, char *output) {
    char digits[MAX_LENGTH] = "";
    char letters[MAX_LENGTH] = "";
    char others[MAX_LENGTH] = "";
    int digitIndex = 0, letterIndex = 0, otherIndex = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        unsigned char c = input[i];
        if (c >= '0' && c <= '9') {
            digits[digitIndex++] = c;
        }
        else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            letters[letterIndex++] = c;
        }
        else {
            others[otherIndex++] = c;
        }
    }
    digits[digitIndex] = '\0';
    letters[letterIndex] = '\0';
    others[otherIndex] = '\0';
    strcpy(output, digits);
    strcat(output, letters);
    strcat(output, others);
}
int main(void) {
    char inputString[MAX_LENGTH];
    char resultString[MAX_LENGTH];
    char digitCountStr[MAX_DIGITS];
    printf("Enter the string to rearrange: ");
    if (!fgets(inputString, sizeof(inputString), stdin)) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }
    inputString[strcspn(inputString, "\n")] = '\0';
    if (strlen(inputString) == 0) {
        fprintf(stderr, "Input string is empty.\n");
        return 1;
    }
    if (strlen(inputString) >= MAX_LENGTH - 1) {
        clearInput();
        printf("Input too long, it will be truncated to %d characters.\n", MAX_LENGTH - 1);
    }
    int digitCount = 0;
    for (int i = 0; inputString[i] != '\0'; i++)
        if (inputString[i] >= '0' && inputString[i] <= '9')
            digitCount++;
    convertToBase(digitCount, 10, digitCountStr);
    printf("Number of digits in the string: %s\n", digitCountStr);
    transpositionUsingConvert(inputString, resultString);
    printf("Result: %s\n", resultString);
    return 0;
}
