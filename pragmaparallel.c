#include <stdio.h>
#include <omp.h>

int main()
{
    int n, i;
    printf("Enter number of threads: ");
    scanf("%d", &n);
    omp_set_num_threads(n);

    printf("\n--- Sequential Execution ---\n");

    for(i = 0; i < n; i++)
    {
        printf("Hello World (Sequential) - Iteration %d\n", i);
    }

    printf("\n--- Parallel Execution ---\n");

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("Hello World (Parallel) from Thread %d\n", tid);
    }

    printf("\n--- Parallel Execution using for ---\n");

    #pragma omp parallel
    {
        #pragma omp for
        for(i = 0; i < n; i++)
        {
            int tid = omp_get_thread_num();
            printf("Hello World (Parallel For) - Iteration %d by Thread %d\n", i, tid);
        }
    }
    return 0;
}