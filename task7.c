#include <stdio.h>
#include <ctype.h>
#include <string.h>

int prime(int number) {
    if (number < 2) {
        return 0;
    }
    int divisor;
    for (divisor = 2; divisor < number; divisor++) {
        if (number % divisor == 0) {
            return 0;
        }
    }
    return 1;
}
int vowel (char character) {
    character = tolower(character);
    if (character == 'a' || character == 'e' || character == 'i' || character == 'o' || character == 'u' || character == 'y') {
        return 1;
    }
    return 0;
}
void processString(char *inputString) {
    for (int position = 0; inputString[position] != '\0'; position++) {
        if (position % 2 == 0 && vowel(inputString[position])) {
            inputString[position] = toupper(inputString[position]);
        }
        else if (prime(position) && !vowel(inputString[position])) {
            inputString[position]=tolower(inputString[position]);
        }
    }
}
int main() {
    char userInput[256];
    while (1) {
        printf("Please enter a string(up to 255 characters): ");
        if (fgets(userInput, sizeof(userInput), stdin) == NULL) {
            printf("Error: Unable to read the string. Try again.\n");
            continue;
        }
        int length = strlen(userInput);
        if (length > 0 && userInput[length-1] == '\n') {
            userInput[length-1] = '\0';
        }
        if (strlen(userInput) == 0) {
            printf("Error: Empty input.\n");
            continue;
        }
        break;
    }
    processString(userInput);
    printf("Processed string: %s\n", userInput);
    return 0;
}
