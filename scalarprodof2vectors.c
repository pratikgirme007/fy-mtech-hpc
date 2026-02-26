#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 6

int compareAsc(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}
int compareDesc(const void *a, const void *b)
{
    return (*(int*)b - *(int*)a);
}
int main()
{
    int A[N] = {1, 3, 5, 2, 4, 6};
    int B[N] = {6, 4, 2, 5, 1, 3};
    int i;
    int result = 0;
    omp_set_num_threads(4);

    qsort(A, N, sizeof(int), compareAsc);
    qsort(B, N, sizeof(int), compareDesc);

    #pragma omp parallel for reduction(+:result) schedule(static) ordered
    for(i = 0; i < N; i++)
    {
        int temp = A[i] * B[i];
        #pragma omp ordered
        {
            printf("Thread %d: A[%d]=%d B[%d]=%d Product=%d\n",
            omp_get_thread_num(), i, A[i], i, B[i], temp);
        }
        result += temp;
    }
    printf("\nMinimum Scalar Product = %d\n", result);
    return 0;
}