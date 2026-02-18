#include <stdio.h>
#include <string.h>

int compare_strings(const char *first_string, const char *second_string) {
    while (*first_string != '\0' && *second_string != '\0') {
        if (*first_string != *second_string) {
            return (unsigned char)*first_string - (unsigned char)*second_string;
        }
        first_string++;
        second_string++;
    }
    return (unsigned char)*first_string - (unsigned char)*second_string;
}
void remove_newline(char *input_string) {
    int i = 0;
    while (input_string[i] != '\0') {
        if (input_string[i] == '\n') {
            input_string[i] = '\0';
            break;
        }
        i++;
    }
}
int main() {
    char first_input[100];
    char second_input[100];
    printf("Enter first string: ");
    if (fgets(first_input, sizeof(first_input), stdin) == NULL) {
        printf("Error entering first string.\n");
        return 1;
    }
    if (strchr(first_input, '\n') == NULL) {
        int clear;
        while ((clear = getchar()) != '\n' && clear != EOF);
    }
    remove_newline(first_input);
    printf("Enter second string: ");
    if (fgets(second_input, sizeof(second_input), stdin) == NULL) {
        printf("Error entering second string.\n");
        return 1;
    }
    if (strchr(second_input, '\n') == NULL) {
        int clear;
        while ((clear = getchar()) != '\n' && clear != EOF);
    }
    remove_newline(second_input);

    int comparison_result = compare_strings(first_input, second_input);

    if (comparison_result == 0) {
        printf("The strings are the same.\n");
    } else if (comparison_result < 0) {
        printf("The first string is smaller than the second string.\n");
    }else {
        printf("The first string is bigger than the second string.\n");
    }
    return 0;
}
