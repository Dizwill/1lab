#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int charToNumber(char onechar) {
    if (onechar >= '0' && onechar <= '9') {
        return onechar - '0';
    }
    if (onechar >= 'A' && onechar <= 'Z') {
        return onechar - 'A' + 10;
    }
    if (onechar >= 'a' && onechar <= 'z') {
        return onechar - 'a' + 10;
    }
    return -1;
}

int validNumber(const char *stringWnumber) {
    int thereDigit = 0;
    int charIndex = 0;
    if (stringWnumber[0] == '+' || stringWnumber[0] == '-') { // скип знака
        charIndex++;
    }
    while (stringWnumber[charIndex] != '\0') {
        char currentChar = stringWnumber[charIndex];
        if (!((currentChar >= '0' && currentChar <= '9') || (currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= 'a' && currentChar <= 'z'))) {
            return 0;
        }
        thereDigit = 1; // хоть один символ нашли
        charIndex++;
    }
    return thereDigit;
}
int searchMinBase (const char *stringWnumber) {
    int maxNumber = -1;
    for (int charIndex = 0; stringWnumber[charIndex]; charIndex++) {
        int digitValue = charToNumber(stringWnumber[charIndex]);
        if (digitValue >= 0 && digitValue > maxNumber) {
            maxNumber = digitValue;
        }
    }
    int minBase = maxNumber + 1;
    if (minBase < 2) minBase = 2;
    return minBase;
}
int conversionDecimal(const char *stringWnumber, int base) {
    int  result = 0;
    int  negative = 0;
    int index = 0;
    if (stringWnumber[0] == '-') {
        negative = 1;
        index++;
    }
    else if (stringWnumber[0] == '+') {
        index++;
    }
    while (stringWnumber[index] != '\0') {
        int digitValue = charToNumber(stringWnumber[index]);
        if (digitValue < 0 ) {
            index++;
            continue;
        }
        result = result * base + digitValue;
        index++;
    }
    if (negative) {
        result = -result;
    }
    return result;
}
FILE* openSafely(const char *fileName, const char *userMessage) {
    char filePath[250];
    FILE *filePointer = NULL;
    while (1) {
        printf("%s", userMessage);
        if (!fgets(filePath, sizeof(filePath), stdin)) {
            exit(1);
        }
        filePath[strcspn(filePath,"\n")] = '\0';
        filePointer = fopen(filePath, fileName);
        if (filePointer) {
            return filePointer;
        }
        printf("Failed to open file '%s'. Try again.\n", filePath);
    }
}
int main(int numberArguments, char *arrayArguments[]) {
    FILE *inputFile = NULL;
    FILE *outputFile = NULL;
    if (numberArguments < 3) {
        printf("You have not specified any files.\n");
        inputFile = openSafely("r", "Enter the path to the input file: ");
        outputFile = openSafely("w", "Enter the path to the output file: ");
    } else {
        inputFile = fopen(arrayArguments[1], "r");
        while (!inputFile) {
            printf("Error: failed to open output file '%s'\n", arrayArguments[1]);
            inputFile = openSafely("r", "Enter the path to the output file: ");
        }
        outputFile = fopen(arrayArguments[2], "w");
        while (!outputFile) {
            printf("Error: failed to open output file '%s'\n", arrayArguments[2]);
            outputFile = openSafely("w", "Enter the path to the output file: ");
        }
    }
    char buffer[100];
    while (fscanf(inputFile, "%99s", buffer) == 1) {
        if (!validNumber(buffer)) {
            printf("Error: invalid number '%s'\n", buffer);
            continue;
        }
        int minBase = searchMinBase(buffer);
        int decimalValue = conversionDecimal(buffer, minBase);
        fprintf(outputFile, "%s => base %d => %d\n", buffer, minBase, decimalValue);
    }
    fclose(inputFile);
    fclose(outputFile);
    printf("The results are written to the output file.\n");
}
