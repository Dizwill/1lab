#include <stdio.h>
#include <math.h>

int doubleEqual(double value1, double value2, double eps) {
    return fabs(value1 - value2) <= eps;
}
size_t copyUniq(const double *sourceArr, size_t sourceSize, double *uniqueArr, double eps) {
    size_t uniqueCount = 0;

    for (size_t i = 0; i < sourceSize; i++) {
        int alreadyExist = 0;
        for (size_t j = 0; j < uniqueCount; j++) {
            if (doubleEqual(sourceArr[i], uniqueArr[j], eps)) {
                alreadyExist = 1;
                break;
            }
        }
        if (!alreadyExist) {
            uniqueArr[uniqueCount++] = sourceArr[i];
        }
    }
    return uniqueCount;
}
int main(void) {
    const double eps = 1e-9;
    double origArr[] = {1.1, 3.7, 1.1, 5.6, 3.7, 9.9, 5.6};
    size_t origSize = sizeof(origArr) / sizeof(origArr[0]);
    double uniqueArr[sizeof(origArr) / sizeof(origArr[0])];
    size_t uniqueCount = copyUniq(origArr, origSize, uniqueArr, eps);
    printf("Source array:\n");
    for (size_t i = 0; i < origSize; i++) {
        printf("%g ", origArr[i]);
    }
    printf("\nArray without duplicates:\n");
    for (size_t i = 0; i < uniqueCount; i++) {
        printf("%g ", uniqueArr[i]);
    }
    printf("\n");
    return 0;
}