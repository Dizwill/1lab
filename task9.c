#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LENGTH 256

bool is_palindrome(const char *text) {
    int start_index = 0;
    int end_index = strlen(text) - 1;

    while (start_index < end_index) {
        if (tolower((unsigned char)text[start_index]) != tolower((unsigned char)text[end_index])) {
            return false;
        }
        start_index++;
        end_index--;
    }
    return true;
}
int main() {
    char user_input[MAX_LENGTH];
    while (1) {
        printf("Please enter a string to check if its a palindrome: ");
        if (fgets(user_input,sizeof(user_input), stdin) == NULL) {
            printf("Input error.\n");
            return 1;
        }
        size_t input_length = strlen(user_input);
        if (input_length > 0 && user_input[input_length - 1] == '\n') {
            user_input[input_length - 1] = '\0';
        }
        if (strlen(user_input) == 0) {
            printf("You entered an empty string. Try again.\n");
        } else {
            break;
        }
    }
    if (is_palindrome(user_input)) {
        printf("Your input is a palindrome.\n");
    }else {
        printf("Your input is not a palindrome.\n");
    }
    return 0;
}
