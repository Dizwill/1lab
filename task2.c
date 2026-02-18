#include <stdio.h>
#include <string.h>

int main() {
    int inputNumber, divider, simple;
    char inputLine[100];

    while (1) {
        printf("Enter a natural number (>1): ");
        if (fgets(inputLine, sizeof(inputLine), stdin) == NULL) {
            printf("Error reading input.\n");
            return 1;
        }
        inputLine[strcspn(inputLine, "\n")] = 0;
        if (strlen(inputLine) == 0) {
            printf("Error: Empty input. Enter a natural number(>1).\n");
            continue;
        }
        if (sscanf(inputLine, "%d", &inputNumber) != 1 || inputNumber <= 1) {
            printf("Error: Invalid input. Enter a natural number (>1).\n");
            continue;
        }
        break;

    }

    simple = 1;
    for (divider = 2; divider * divider <= inputNumber; divider++) {
        if (inputNumber % divider == 0) {
            simple = 0;
            break;
        }
    }
    if (simple == 1) {
        printf("%d - This is a prime number.\n", inputNumber);
    } else {
        printf("%d - This is a composite number.\n", inputNumber);
    } return 0;
}
