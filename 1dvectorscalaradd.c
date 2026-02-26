#include <stdio.h>
#include <omp.h>
#define N 200

int main()
{
    int i, chunk, threads;
    double A[N], B[N];
    double scalar = 5.0;
    double start, end;
    double sum = 0;

    printf("Enter number of threads: ");
    scanf("%d", &threads);

    printf("Enter chunk size: ");
    scanf("%d", &chunk);

    omp_set_num_threads(threads);

    // Initialize vector
    for(i = 0; i < N; i++)
        A[i] = i;

    printf("\nSTATIC Schedule:\n");

    start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for schedule(static,chunk) nowait reduction(+:sum)
        for(i = 0; i < N; i++)
        {
            B[i] = A[i] + scalar;
            sum += B[i];
        }

        printf("Thread %d finished STATIC loop\n", omp_get_thread_num());
    }

    end = omp_get_wtime();

    printf("STATIC Time: %f\n", end-start);


    // DYNAMIC SCHEDULE

    sum = 0;

    printf("\nDYNAMIC Schedule:\n");

    start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for schedule(dynamic,chunk) nowait reduction(+:sum)
        for(i = 0; i < N; i++)
        {
            B[i] = A[i] + scalar;
            sum += B[i];
        }

        printf("Thread %d finished DYNAMIC loop\n", omp_get_thread_num());
    }

    end = omp_get_wtime();

    printf("DYNAMIC Time: %f\n", end-start);

    return 0;
}