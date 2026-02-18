#include <stdio.h>


void swap(int *num1, int *num2) {
    int temporary = *num1;
    *num1 = *num2;
    *num2 = temporary;
}
int main() {
    int firstNumber, secondNumber;
    int scanfresult;

    while (1) {
        printf("Enter First Number: ");
        scanfresult = scanf("%d", &firstNumber);
        if (scanfresult == 1) {
            while (getchar() != '\n');
            break;
        } else {
            printf("Error. Enter First Number.\n");
            while (getchar() != '\n');
        }
    }
    while (1) {
        printf("Enter Second Number: ");
        scanfresult = scanf("%d", &secondNumber);
        if (scanfresult == 1) {
            break;
        } else {
            printf("Error. Enter Second Number.\n");
            while (getchar() != '\n'); // очистка буфера ввода
        }
    }
    printf("Before exchange: first number = %d, second number = %d\n", firstNumber, secondNumber);
    swap(&firstNumber, &secondNumber);
    printf("After exchange: first number = %d, second number = %d\n",firstNumber, secondNumber);
    return 0;
}
