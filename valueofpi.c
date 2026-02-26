#include <stdio.h>
#include <omp.h>

int main()
{
    long num_steps = 100000000;
    double step, x, pi, sum = 0.0;
    int i, threads;

    printf("Enter number of threads: ");
    scanf("%d", &threads);

    omp_set_num_threads(threads);

    step = 1.0 / (double) num_steps;

    double start = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for(i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x*x);
    }

    pi = step * sum;

    double end = omp_get_wtime();

    printf("Value of Pi: %lf\n", pi);
    printf("Execution Time: %f seconds\n", end - start);

    return 0;
}