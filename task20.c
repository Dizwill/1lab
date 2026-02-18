#include <stdio.h>
#include <stdlib.h>

void matrixAdd(int rows, int cols, double **first, double **second, double **result) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = first[i][j] + second[i][j];
}
void matrixMultiply(int rowsFirst, int colsFirst, int colsSecond, double **first, double **second, double **result) {
    for (int i = 0; i < rowsFirst; i++)
        for (int j = 0; j < colsSecond; j++) {
            result[i][j] = 0;
            for (int k = 0; k < colsFirst; k++)
                result[i][j] += first[i][k] * second[k][j];
        }
}
double **matrixAllocate(int rows, int cols) {
    double **matrix = malloc(rows * sizeof(double *));
    if (!matrix) return NULL;
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(double));
        if (!matrix[i]) {
            for (int j = 0; j < i; j++) free(matrix[j]);
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}
void freeMatrix(double **matrix, int rows) {
    if (!matrix) return;
    for (int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);
}
int inputMatrix(int rows, int cols, double **matrix) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            printf("Enter the element [%d][%d]: ", i, j);
            if (scanf("%lf", &matrix[i][j]) != 1) {
                printf("Input error.\n");
                return 1;
            }
        }
    return 0;
}
void printMatrix(int rows, int cols, double **matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%8.2lf ", matrix[i][j]);
        printf("\n");
    }
}
int main() {
    int rowsFirst, colsFirst, rowsSecond, colsSecond;
    printf("Dimensions of the first matrix (rows, columns): ");
    if (scanf("%d %d", &rowsFirst, &colsFirst) != 2 || rowsFirst <= 0 || colsFirst <= 0) {
        printf("Error: matrix dimensions must be positive numbers.\n");
        return 1;
    }
    printf("Dimensions of the second matrix (rows, columns): ");
    if (scanf("%d %d", &rowsSecond, &colsSecond) != 2 || rowsSecond <= 0 || colsSecond <= 0) {
        printf("Error: matrix dimensions must be positive numbers.\n");
        return 1;
    }
    double **firstMatrix = matrixAllocate(rowsFirst, colsFirst);
    if (!firstMatrix) {
        printf("Error allocating memory for the first matrix.\n");
        return 1;
    }
    double **secondMatrix = matrixAllocate(rowsSecond, colsSecond);
    if (!secondMatrix) {
        printf("Error allocating memory for the second matrix.\n");
        freeMatrix(firstMatrix, rowsFirst);
        return 1;
    }
    printf("Enter the elements of the first matrix:\n");
    if (inputMatrix(rowsFirst, colsFirst, firstMatrix)) {
        freeMatrix(firstMatrix, rowsFirst);
        freeMatrix(secondMatrix, rowsSecond);
        return 1;
    }
    printf("Enter the elements of the second matrix:\n");
    if (inputMatrix(rowsSecond, colsSecond, secondMatrix)) {
        freeMatrix(firstMatrix, rowsFirst);
        freeMatrix(secondMatrix, rowsSecond);
        return 1;
    }
    if (rowsFirst == rowsSecond && colsFirst == colsSecond) {
        double **sumMatrix = matrixAllocate(rowsFirst, colsFirst);
        if (!sumMatrix) {
            printf("Memory allocation error.\n");
        } else {
            matrixAdd(rowsFirst, colsFirst, firstMatrix, secondMatrix, sumMatrix);
            printf("The result of addition:\n");
            printMatrix(rowsFirst, colsFirst, sumMatrix);
            freeMatrix(sumMatrix, rowsFirst);
        }
    } else {
        printf("Addition is impossible, the sizes of the matrices do not match.\n");
    }
    if (colsFirst == rowsSecond) {
        double **productMatrix = matrixAllocate(rowsFirst, colsSecond);
        if (!productMatrix) {
            printf("Memory allocation error.\n");
        } else {
            matrixMultiply(rowsFirst, colsFirst, colsSecond, firstMatrix, secondMatrix, productMatrix);
            printf("The result of multiplication:\n");
            printMatrix(rowsFirst, colsSecond, productMatrix);
            freeMatrix(productMatrix, rowsFirst);
        }
    } else {
        printf("Multiplication is impossible, the number of columns of the first matrix is not equal to the number of rows of the second.\n");
    }
    freeMatrix(firstMatrix, rowsFirst);
    freeMatrix(secondMatrix, rowsSecond);
    return 0;
}