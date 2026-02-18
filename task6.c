#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MIN_VALUE -10000
#define MAX_VALUE 10000

int main(void) {
    int numbers[BUFSIZ];
    int index;
    int min_value = INT_MAX, max_value = INT_MIN;
    int min_index = -1, max_index = -1;
    srand((unsigned int) time(NULL));
    for (index = 0; index < BUFSIZ; index++) {
        numbers[index] = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;

        if (numbers[index] < min_value) {
            min_value = numbers[index];
            min_index = index;
        }
        if (numbers[index] > max_value) {
            max_value = numbers[index];
            max_index = index;
        }
    }
    printf("The minimum value is: %d, index: %d\n", min_value, min_index);
    printf("The maximum value is: %d, index: %d\n", max_value, max_index);

    return 0;
}
