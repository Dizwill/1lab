#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double **createMatrix(size_t rows, size_t cols) {
    double **matrix = malloc(rows * sizeof(double*));
    if (!matrix) return NULL;

    for (size_t row = 0; row < rows; row++) {
        matrix[row] = malloc(cols * sizeof(double));
        if (!matrix[row]) return NULL;
    }
    return matrix;
}
void freeMatrix(double **matrix, size_t rows) {
    for (size_t row = 0; row < rows; row++)
        free(matrix[row]);
    free(matrix);
}
void printMatrix(double **matrix, size_t rows, size_t cols) {
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < cols; col++)
            printf("%10.4f ", matrix[row][col]);
        printf("\n");
    }
}
void multiplyByNumber(double **matrix, size_t rows, size_t cols, double multiplier) {
    for (size_t row = 0; row < rows; row++)
        for (size_t col = 0; col < cols; col++)
            matrix[row][col] *= multiplier;
}
double determinant(double **matrix, size_t size, double eps) {
    double **workMatrix = createMatrix(size, size);
    if (!workMatrix) return -1;
    for (size_t row = 0; row < size; row++)
        for (size_t col = 0; col < size; col++)
            workMatrix[row][col] = matrix[row][col];
    double det = 1.0;
    for (size_t mainRow = 0; mainRow < size; mainRow++) {
        size_t pivotRow = mainRow;
        for (size_t row = mainRow + 1; row < size; row++)
            if (fabs(workMatrix[row][mainRow]) > fabs(workMatrix[pivotRow][mainRow]))
                pivotRow = row;
        if (fabs(workMatrix[pivotRow][mainRow]) < eps) {
            freeMatrix(workMatrix, size);
            return 0.0;
        }
        if (pivotRow != mainRow) {
            double *tmp = workMatrix[mainRow];
            workMatrix[mainRow] = workMatrix[pivotRow];
            workMatrix[pivotRow] = tmp;
            det = -det;
        }
        det *= workMatrix[mainRow][mainRow];
        for (size_t row = mainRow + 1; row < size; row++) {
            double factor = workMatrix[row][mainRow] / workMatrix[mainRow][mainRow];
            for (size_t col = mainRow; col < size; col++)
                workMatrix[row][col] -= workMatrix[mainRow][col] * factor;
        }
    }
    freeMatrix(workMatrix, size);
    return det;
}
double **inverseMatrix(double **matrix, size_t size, double eps) {
    double **extendedMatrix = createMatrix(size, 2 * size);
    if (!extendedMatrix) return NULL;
    for (size_t row = 0; row < size; row++) {
        for (size_t col = 0; col < size; col++)
            extendedMatrix[row][col] = matrix[row][col];
        for (size_t col = 0; col < size; col++)
            extendedMatrix[row][col + size] = (row == col);
    }
    for (size_t mainRow = 0; mainRow < size; mainRow++) {
        size_t pivotRow = mainRow;
        for (size_t row = mainRow + 1; row < size; row++)
            if (fabs(extendedMatrix[row][mainRow]) > fabs(extendedMatrix[pivotRow][mainRow]))
                pivotRow = row;
        if (fabs(extendedMatrix[pivotRow][mainRow]) < eps) {
            freeMatrix(extendedMatrix, size);
            return NULL;
        }
        if (pivotRow != mainRow) {
            double *tmp = extendedMatrix[mainRow];
            extendedMatrix[mainRow] = extendedMatrix[pivotRow];
            extendedMatrix[pivotRow] = tmp;
        }
        double pivot_value = extendedMatrix[mainRow][mainRow];
        for (size_t col = 0; col < 2 * size; col++)
            extendedMatrix[mainRow][col] /= pivot_value;

        for (size_t row = 0; row < size; row++) {
            if (row == mainRow) continue;
            double factor = extendedMatrix[row][mainRow];
            for (size_t col = 0; col < 2 * size; col++)
                extendedMatrix[row][col] -= extendedMatrix[mainRow][col] * factor;
        }
    }
    double **inverse = createMatrix(size, size);
    if (!inverse) return NULL;
    for (size_t row = 0; row < size; row++)
        for (size_t col = 0; col < size; col++)
            inverse[row][col] = extendedMatrix[row][col + size];

    freeMatrix(extendedMatrix, size);
    return inverse;
}
int main() {
    size_t size = 3;
    double eps = 1e-9;
    double **A = createMatrix(size, size);
    if (!A) {
        printf("Memory allocation error.\n");
        return -2;
    }
    printf("Enter the elements of the 3x3 matrix:\n");
    for (size_t row = 0; row < size; row++)
        for (size_t col = 0; col < size; col++) {
            printf("A[%zu][%zu] = ", row, col);
            if (scanf("%lf", &A[row][col]) != 1) {
                printf("Invalid input.\n");
                freeMatrix(A, size);
                return 1;
            }
        }
    printf("\nMatrix A:\n");
    printMatrix(A, size, size);
    double det = determinant(A, size, eps);
    printf("\nDet(A) = %.6f\n", det);
    if (fabs(det) < eps) {
        printf("The matrix is irreversible.\n");
    } else {
        double **inv = inverseMatrix(A, size, eps);
        if (inv) {
            printf("\nA^(-1):\n");
            printMatrix(inv, size, size);
            freeMatrix(inv, size);
        }
    }
    multiplyByNumber(A, size, size, 2.0);
    printf("\n2 * A:\n");
    printMatrix(A, size, size);
    freeMatrix(A, size);
    return 0;
}
