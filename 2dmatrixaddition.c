#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main()
{
    int i, j, n;
    int threads;
    printf("Enter matrix size: ");
    scanf("%d", &n);
    printf("Enter number of threads: ");
    scanf("%d", &threads);
    omp_set_num_threads(threads);
    // Dynamic allocation
    double **A = (double **)malloc(n * sizeof(double *));
    double **B = (double **)malloc(n * sizeof(double *));
    double **C = (double **)malloc(n * sizeof(double *));
    for(i = 0; i < n; i++)
    {
        A[i] = (double *)malloc(n * sizeof(double));
        B[i] = (double *)malloc(n * sizeof(double));
        C[i] = (double *)malloc(n * sizeof(double));
    }
    // Initialize matrices
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
        {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    double start = omp_get_wtime();
    // Parallel Matrix Addition
    #pragma omp parallel for private(j)
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    double end = omp_get_wtime();
    printf("Execution Time = %f seconds\n", end - start);
    return 0;
}