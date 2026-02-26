#include <stdio.h>
#include <omp.h>
#define MAX 1000000

int main()
{
    static float A[MAX], B[MAX];
    float scalar = 5.0;
    int i, n, threads;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter number of threads: ");
    scanf("%d", &threads);

    omp_set_num_threads(threads);

    // Initialize vector
    for(i = 0; i < n; i++)
    {
        A[i] = i * 1.0;
    }
    double start = omp_get_wtime();

    // Parallel Vector Scalar Addition
    #pragma omp parallel for
    for(i = 0; i < n; i++)
    {
        B[i] = A[i] + scalar;
    }
    double end = omp_get_wtime();
    printf("Execution Time: %f seconds\n", end - start);
    return 0;
}