#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5000000

// Initialize arrays with constants
void init(double *A, double *B, int n) {
    for(int i = 0; i < n; i++) {
        A[i] = 1.5;
        B[i] = 2.5;
    }
}

int main() {
    // Allocate memory on heap
    double *A   = (double *)malloc(N * sizeof(double));
    double *B   = (double *)malloc(N * sizeof(double));
    double *Add = (double *)malloc(N * sizeof(double));
    double *Sub = (double *)malloc(N * sizeof(double));
    double *Mul = (double *)malloc(N * sizeof(double));
    
    init(A, B, N);
    
    // Start serial benchmarking
    clock_t start = clock();
    for(int i = 0; i < N; i++) {
        Add[i] = A[i] + B[i]; // Element-wise Addition
        Sub[i] = A[i] - B[i]; // Element-wise Subtraction
        Mul[i] = A[i] * B[i]; // Element-wise Multiplication
    }
    clock_t end = clock();
    
    // Calculate execution time in ms
    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    
    printf("Array Size    : %d\n", N);
    printf("Serial Time   : %.3f ms\n", time_taken);
    
    // Free allocated memory
    free(A); free(B); free(Add); free(Sub); free(Mul);
    return 0;
}