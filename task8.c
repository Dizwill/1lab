#include <stdio.h>
#include <string.h>


void reverseString(char *text) {
    if (text == NULL) return;

    int startIndex = 0;
    int endIndex = strlen(text) - 1;

    while (startIndex < endIndex) {
        char temporary = text[startIndex];
        text[startIndex] = text[endIndex];
        text[endIndex] = temporary;
        startIndex++;
        endIndex--;
    }
}

int main() {
    char userInput[200]; // буфер для строки
    printf("Please enter a string(no more than 199 characters: ");
    if (fgets(userInput, sizeof(userInput), stdin) == NULL) {
        printf("Input Error!\n");
        return 1;
    }
    int inputLength = strlen(userInput);
    if (inputLength > 0 && userInput[inputLength - 1] == '\n') {
        userInput[inputLength - 1] = '\0';
    }

    printf("Original string: %s\n", userInput);
    reverseString(userInput);
    printf("Reversed string: %s\n", userInput);
    return 0;
}
