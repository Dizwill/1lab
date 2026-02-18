#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static void swap(void *first, void *second, size_t size) {
    unsigned char *a = first, *b = second, tmp;
    for (size_t i = 0; i < size; i++) {
        tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}
int floatCompare(const void *x_ptr, const void *y_ptr, void *epsilonPtr) {
    float epsilon = *(float*)epsilonPtr;
    float x = *(float*)x_ptr;
    float y = *(float*)y_ptr;

    if (fabsf(x - y) < epsilon) return 0;
    return (x < y) ? -1 : 1;
}
void bubbleSort(void *array, size_t count, size_t size,
                 int (*compare)(const void*, const void*, void*), void *epsilon)
{
    unsigned char *arr = array;
    for (size_t i = 0; i < count; i++)
        for (size_t j = 0; j < count - i - 1; j++)
            if (compare(arr + j*size, arr + (j+1)*size, epsilon) > 0)
                swap(arr + j*size, arr + (j+1)*size, size);
}
void selectionSort(void *array, size_t count, size_t size,
                    int (*compare)(const void*, const void*, void*), void *epsilon)
{
    unsigned char *arr = array;
    for (size_t i = 0; i < count; i++) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < count; j++)
            if (compare(arr + j*size, arr + minIndex*size, epsilon) < 0)
                minIndex = j;
        swap(arr + i*size, arr + minIndex*size, size);
    }
}
void insertionSort(void *array, size_t count, size_t size,
                    int (*compare)(const void*, const void*, void*), void *epsilon)
{
    unsigned char *arr = array;
    for (size_t i = 1; i < count; i++) {
        size_t j = i;
        while (j > 0 && compare(arr + (j-1)*size, arr + j*size, epsilon) > 0) {
            swap(arr + (j-1)*size, arr + j*size, size);
            j--;
        }
    }
}
static void heapify(unsigned char *arr, size_t count, size_t size, size_t rootIndex,
                    int (*compare)(const void*, const void*, void*), void *epsilon)
{
    size_t largest = rootIndex;
    size_t leftChild = 2*rootIndex + 1;
    size_t rightChild = 2*rootIndex + 2;
    if (leftChild < count && compare(arr + leftChild*size, arr + largest*size, epsilon) > 0)
        largest = leftChild;
    if (rightChild < count && compare(arr + rightChild*size, arr + largest*size, epsilon) > 0)
        largest = rightChild;
    if (largest != rootIndex) {
        swap(arr + rootIndex*size, arr + largest*size, size);
        heapify(arr, count, size, largest, compare, epsilon);
    }
}
void heapSort(void *array, size_t count, size_t size,
               int (*compare)(const void*, const void*, void*), void *epsilon)
{
    unsigned char *arr = array;
    for (size_t i = count/2; i > 0; i--)
        heapify(arr, count, size, i - 1, compare, epsilon);

    for (size_t i = count - 1; i > 0; i--) {
        swap(arr, arr + i*size, size);
        heapify(arr, i, size, 0, compare, epsilon);
    }
}
void printArr(float *array, size_t count) {
    for (size_t i = 0; i < count; i++) printf("%.2f ", array[i]);
    printf("\n");
}
int main() {
    float epsilon = 1e-6;
    float arrayBubble[] = {3,1,2,5,4};
    float arraySelect[] = {3,1,2,5,4};
    float arrayInsert[] = {3,1,2,5,4};
    float arrayHeap[] = {3,1,2,5,4};
    size_t count = 5;
    printf("Source array: ");
    printArr(arrayBubble, count);
    bubbleSort(arrayBubble, count, sizeof(float), floatCompare, &epsilon);
    selectionSort(arraySelect, count, sizeof(float), floatCompare, &epsilon);
    insertionSort(arrayInsert, count, sizeof(float), floatCompare, &epsilon);
    heapSort(arrayHeap, count, sizeof(float), floatCompare, &epsilon);
    printf("Bubble:       "); printArr(arrayBubble, count);
    printf("Choice:         "); printArr(arraySelect, count);
    printf("Inserts:       "); printArr(arrayInsert, count);
    printf("Pyramidal: "); printArr(arrayHeap, count);
    return 0;
}
