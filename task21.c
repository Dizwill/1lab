#include <stdio.h>
#define MAX_SIZE 100

int main(void) {
    char filename[256];
    int matrix[MAX_SIZE][MAX_SIZE];
    int rows = 0, cols = 0;
    printf("Enter the name of the matrix file: ");
    if (scanf("%255s", filename) != 1) {
        printf("Input error.\n");
        return 1;
    }
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file '%s'\n", filename);
        return 1;
    }
    char line[1024];
    while (fgets(line, sizeof(line), file) && rows < MAX_SIZE) {
        int col = 0;
        char *ptr = line;
        while (*ptr && col < MAX_SIZE) {
            if (sscanf(ptr, "%d", &matrix[rows][col]) == 1) {
                col++;
                while (*ptr && *ptr != ' ' && *ptr != '\t' && *ptr != '\n') ptr++;
            } else {
                ptr++;
            }
            while (*ptr == ' ' || *ptr == '\t') ptr++;
        }
        if (col == 0) continue;
        if (rows == 0) cols = col;
        else if (col != cols) {
            printf("Error: Matrix rows have different lengths.\n");
            fclose(file);
            return 1;
        }
        rows++;
    }
    fclose(file);
    int temp[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            temp[i][j] = matrix[i][j];
    int rank = 0;
    for (int row = 0, col = 0; row < rows && col < cols; col++) {
        int pivot = row;
        while (pivot < rows && temp[pivot][col] == 0) pivot++;
        if (pivot == rows) continue;
        if (pivot != row) {
            for (int j = 0; j < cols; j++) {
                int t = temp[row][j];
                temp[row][j] = temp[pivot][j];
                temp[pivot][j] = t;
            }
        }
        for (int i = row + 1; i < rows; i++) {
            if (temp[i][col] != 0) {
                int factor = temp[i][col] / temp[row][col];
                for (int j = col; j < cols; j++)
                    temp[i][j] -= factor * temp[row][j];
            }
        }
        row++;
        rank++;
    }
    printf("Matrix rank: %d\n", rank);
    int foundSaddle = 0;
    for (int i = 0; i < rows; i++) {
        int rowMin = matrix[i][0], colIndex = 0;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] < rowMin) {
                rowMin = matrix[i][j];
                colIndex = j;
            }
        }
        int isSaddle = 1;
        for (int k = 0; k < rows; k++) {
            if (k != i && matrix[k][colIndex] > rowMin) {
                isSaddle = 0;
                break;
            }
        }
        for (int j = 0; j < cols; j++) {
            if (j != colIndex && matrix[i][j] <= rowMin) {
                isSaddle = 0;
                break;
            }
        }
        if (isSaddle) {
            printf("Saddle point: [%d][%d] = %d\n", i, colIndex, rowMin);
            foundSaddle = 1;
        }
    }
    if (!foundSaddle) printf("There are no saddle points.\n");
    if (rows != cols) {
        printf("The trace of the matrix cannot be calculated (the matrix is not square).\n");
    } else {
        int trace = 0;
        for (int i = 0; i < rows; i++)
            trace += matrix[i][i];
        printf("Trace of the Matrix: %d\n", trace);
    }
    return 0;
}
