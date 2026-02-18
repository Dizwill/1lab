#include <stdio.h>
#include <math.h>

int main() {
    int side1, side2, side3;
    double epsilon = 1e-9;
    while (1) {
        printf("Enter three non-negative integers (for triangle, progression and Fibonacci checks): ");
        int inputCount = scanf("%d %d %d", &side1, &side2, &side3);

        if (inputCount != 3) {
            printf("Error: You must enter exactly three numbers. \n");
            while (getchar() != '\n');
            continue;
        }

        if (side1 < 0 || side2 < 0 || side3 < 0) {
            printf("Error: Numbers must be non-negative. \n");
            continue;
        }
        break;
    }


    // (пункт а)
    if (side1 + side2 > side3 && side1+side3 > side2 && side2 + side3 > side1)
        printf("1) Triangle sides: Yes\n");
    else
        printf("1) Triangles side: No\n");

    // (пункт б)
    int leg1, leg2, hypotenuse;
    if (side1 >= side2 && side1 >= side3) {
        hypotenuse = side1;
        leg1 = side2;
        leg2 = side3;
    } else if (side2 >= side1 && side2 >= side3) {
        hypotenuse = side2;
        leg1 = side1;
        leg2 = side3;
    } else {
        hypotenuse = side3;
        leg1 = side1;
        leg2 = side2;
    }
    if (fabs((double)leg1*leg1 +(double)leg2*leg2 - (double)hypotenuse*hypotenuse) < epsilon)
        printf("2) Right triangle: Yes\n");
    else
        printf("2) Right triangle: No\n");

    // (пункт с)
    if (2*side2 == side1 + side3)
        printf("3) Arithmetic progression: Yes\n");
    else
        printf("3) Arithmetic progression: No\n");

    // 4. (пункт d)
    if (side1 > 0 && side3 > 0 && side2*side2 == side1*side3)
        printf("4) Geometric progression: Yes\n");
    else
        printf("4) Geometric progression: No\n");

    // (пункт e)
    int fib[47];
    fib[0] = 0;
    fib[1] = 1;
    int fibCount = 2;

    while (fib[fibCount-1] < 10000) {
        fib[fibCount] = fib[fibCount-1] + fib[fibCount-2];
        fibCount++;
    }
    int Side1fib = 0, Side2fib = 0, Side3fib = 0;
    for (int i = 0; i < fibCount; i++) {
        if (fib[i] == side1) Side1fib = 1;
        if (fib[i] == side2) Side2fib = 1;
        if (fib[i] == side3) Side3fib = 1;
    }
    if (Side1fib && Side2fib && Side3fib)
        printf( "5) Fibonacci numbers: Yes\n");
    else
        printf("5) Fibonacci numbers: No\n");

    // (пункт f)
    int Consecutive = 0; // 0 = нет, 1 = да
    for (int i = 0; i < fibCount-2; i++) {
        if (fib[i] == side1 && fib[i+1] == side2 && fib[i+2] == side3)
            Consecutive = 1;
    }
    if (Consecutive)
        printf("6) Consecutive Fibonacci numbers: Yes\n");
    else
        printf("6) Consecutive Fibonacci numbers: No\n");

    return 0;

}
