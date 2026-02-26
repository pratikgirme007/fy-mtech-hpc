#include <stdio.h>
#include <omp.h>
#define SIZE 10

int buffer[SIZE];
int count = 0;

void producer()
{
    int item;
    for(item = 1; item <= 15; item++)
    {
        int produced = 0;
        while(!produced)
        {
            #pragma omp critical
            {
                if(count < SIZE)
                {
                    buffer[count] = item;
                    printf("Produced: %d by Thread %d\n",
                    item, omp_get_thread_num());

                    count++;
                    produced = 1;
                }
            }
            #pragma omp flush(count)
        }
    }
}

void consumer()
{
    int item;
    for(int i = 1; i <= 15; i++)
    {
        int consumed = 0;
        while(!consumed)
        {
            #pragma omp critical
            {
                if(count > 0)
                {
                    item = buffer[count-1];

                    printf("Consumed: %d by Thread %d\n",
                    item, omp_get_thread_num());

                    count--;
                    consumed = 1;
                }
            }
            #pragma omp flush(count)
        }
    }
}

int main()
{
    omp_set_num_threads(2);
    #pragma omp parallel
    {
        if(omp_get_thread_num() == 0)
            producer();
        else
            consumer();
    }
    return 0;
}