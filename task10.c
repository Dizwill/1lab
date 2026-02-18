#include <stdio.h>
#include <string.h>

void concatString(char *firstString, const char *stringToAdd) {
    int indexFirstString = 0;
    while (firstString[indexFirstString] != '\0') {
        indexFirstString++;
    }
    int indexStringToAdd = 0;
    while (stringToAdd[indexStringToAdd] != '\0') {
        firstString[indexFirstString] = stringToAdd[indexStringToAdd];
        indexFirstString++;
        indexStringToAdd++;
    }
    firstString[indexFirstString] = '\0';
}
int main() {
    char firstString[50];
    char secondString[50];

    printf("Enter the first string(maximum 49 characters): ");
    fgets(firstString, sizeof(firstString), stdin);
    firstString[strcspn(firstString, "\n")] = '\0';
    if (strlen(firstString) == 49 && firstString[48] != '\n') {
        printf("Input too long.Only 49 characters taken.\n");
        int clear;
        while ((clear = getchar()) != '\n' && clear != EOF);
    }

    printf("Enter the second string (maximum 49 characters): ");
    fgets(secondString, sizeof(secondString), stdin);
    secondString[strcspn(secondString, "\n")] = '\0';
    if (strlen(secondString) == 49 && secondString[48] != '\n') {
        int clear;
        while ((clear = getchar()) != '\n' && clear != EOF);
        printf("Input too long.Only 49 characters taken.\n");
    }

    concatString(firstString, secondString);

    printf("The result of merging strings: %s\n", firstString);
    return 0;
}
