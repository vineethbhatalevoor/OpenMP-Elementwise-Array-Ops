#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Populate source arrays with random decimal values
void initialize_arrays(double *A, double *B, int N) {
    for (int i = 0; i < N; i++) {
        A[i] = (rand() % 100) / 10.0;
        B[i] = (rand() % 100) / 10.0;
    }
}

// 1. Sequential Execution Loop (Single-threaded)
void operations_serial(double *A, double *B, double *Add, double *Sub, double *Mul, int N) {
    for (int i = 0; i < N; i++) {
        Add[i] = A[i] + B[i]; // Sequential Addition
        Sub[i] = A[i] - B[i]; // Sequential Subtraction
        Mul[i] = A[i] * B[i]; // Sequential Multiplication
    }
}

// 2. Parallel Execution Loop (Multi-threaded work-sharing)
void operations_parallel(double *A, double *B, double *Add, double *Sub, double *Mul, int N) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++) {
        Add[i] = A[i] + B[i]; // Parallel Addition
        Sub[i] = A[i] - B[i]; // Parallel Subtraction
        Mul[i] = A[i] * B[i]; // Parallel Multiplication
    }
}

int main() {
    // Array size scales to test system scalability
    int sizes[] = {1000000, 2000000, 5000000, 10000000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("=========================================================================\n");
    printf("  Array Size (N)  | Serial Time (s) | Parallel Time (s) | Speedup Factor \n");
    printf("=========================================================================\n");

    for (int s = 0; s < num_sizes; s++) {
        int N = sizes[s];

        // Allocate dynamic memory on the heap
        double *A   = (double *)malloc(N * sizeof(double));
        double *B   = (double *)malloc(N * sizeof(double));
        double *Add = (double *)malloc(N * sizeof(double));
        double *Sub = (double *)malloc(N * sizeof(double));
        double *Mul = (double *)malloc(N * sizeof(double));

        initialize_arrays(A, B, N);

        // Benchmark sequential processing runtime
        double start_serial = omp_get_wtime();
        operations_serial(A, B, Add, Sub, Mul, N);
        double end_serial = omp_get_wtime();
        double time_serial = end_serial - start_serial;

        // Benchmark concurrent OpenMP processing runtime
        double start_parallel = omp_get_wtime();
        operations_parallel(A, B, Add, Sub, Mul, N);
        double end_parallel = omp_get_wtime();
        double time_parallel = end_parallel - start_parallel;

        // Compute performance gain factor
        double speedup = time_serial / time_parallel;

        // Output formatted row metrics
        printf("    %12d    |    %9.5f    |     %9.5f     |     %6.2fx\n", 
               N, time_serial, time_parallel, speedup);

        // Deallocate heap arrays to prevent memory leaks
        free(A); free(B); free(Add); free(Sub); free(Mul);
    }
    printf("=========================================================================\n");
    return 0;
}