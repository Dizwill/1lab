#include <stdio.h>
#include <math.h>

#define MAX_SIZE 128

int isPrime(int x) {
    if (x < 2) return 0;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}
int main() {
    char filename[100];
    printf("Enter a file name: ");
    scanf("%99s", filename);
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    int arr[MAX_SIZE];
    int count = 0;
    while (count < MAX_SIZE && fscanf(f, "%d", &arr[count]) == 1) {
        count++;
    }
    fclose(f);
    if (count == 0) {
        printf("File is empty.\n");
        return 1;
    }
    int primePos[MAX_SIZE];
    int oddNum[MAX_SIZE];
    int primeCount = 0, oddCount = 0;
    double sum = 0.0;
    double product = 1.0;
    double harmonicSum = 0.0;
    int max = arr[0], min = arr[0];
    int sumPrimeElements = 0;
    int sumEvenPositive = 0;
    for (int i = 0; i < count; i++) {
        sum += arr[i];
        product *= arr[i] == 0 ? 1 : arr[i];
        if (arr[i] != 0) harmonicSum += 1.0 / arr[i];
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];

        if (isPrime(i)) {
            primePos[primeCount++] = arr[i];
        }
        if (arr[i] % 2 != 0) {
            oddNum[oddCount++] = arr[i];
        }
        if (isPrime(arr[i])) sumPrimeElements += arr[i];
        if (arr[i] > 0 && arr[i] % 2 == 0) sumEvenPositive += arr[i];
    }
    int hasNegative = 0;
    for (int i = 0; i < count; i++) {
        if (arr[i] < 0) {
            hasNegative = 1;
            break;
        }
    }
    double meanArith = sum / count;
    double geom = 0.0;
    if (!hasNegative) {
        geom = pow(product, 1.0/count);
    }
    double harmonic = count / harmonicSum;
    int range = max - min;
    int difference = sumPrimeElements - sumEvenPositive;
    printf("\nArray of numbers in prime positions: ");
    for (int i = 0; i < primeCount; i++) printf("%d ", primePos[i]);
    printf("\nOdd numbers: ");
    for (int i = 0; i < oddCount; i++) printf("%d ", oddNum[i]);
    printf("\nArithmetic mean: %.3f\n", meanArith);
    if (hasNegative) {
        printf("Geometric mean: cant be calculated for negative numbers.\n");
    }else {
        printf("Geometric mean: %.3f\n", geom);
    }
    printf("Harmonic mean: %.3f\n", harmonic);
    printf("Scope: %d\n", range);
    printf("The difference between the sums of prime and even positive elements: %d\n", difference);
    return 0;
}