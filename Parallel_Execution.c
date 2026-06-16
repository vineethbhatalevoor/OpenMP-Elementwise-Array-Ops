#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

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
    
    // Start parallel benchmarking
    double start = omp_get_wtime();
    
    // Split loop iterations across available CPU threads
    #pragma omp parallel for schedule(static)
    for(int i = 0; i < N; i++) {
        Add[i] = A[i] + B[i]; // Parallel Addition
        Sub[i] = A[i] - B[i]; // Parallel Subtraction
        Mul[i] = A[i] * B[i]; // Parallel Multiplication
    }
    double end = omp_get_wtime();
    
    // Calculate execution time in ms
    printf("Array Size    : %d\n", N);
    printf("Parallel Time : %.3f ms\n", (end - start) * 1000);
    
    // Free allocated memory
    free(A); free(B); free(Add); free(Sub); free(Mul);
    return 0;
}