// (c) Partha Dasgupta 2009
// permission to use and distribute granted.

#include <stdio.h>
#include <stdlib.h>
#include "sem.h"

#define N 3
semaphore_t empty[N];
semaphore_t full[N];

int buffer[N];


void updateArray(int *arg)
{
    while(1)
    {
        P(&empty[*arg]);
        // printf("Updating value of Buffer array index %d", *arg );
        buffer[*arg]++;
        printf("Thread %d incremented the value of array[%d] to %d\n", *arg+1, *arg, buffer[*arg]);
        V(&full[*arg]);
        sleep(1);
    }
}

void displayArray()
{
    while(1)
    {
        for(int i=0;i<N;i++)
        {
            P(&full[i]);
        }
        printf("\n\n\tValues of elements present in the array are:");
        for(int i=0;i<N;i++)
        {
            printf("%d ", buffer[i]);
        }
        printf("\n\n");
        for(int i=0;i<N;i++)
        {
            V(&empty[i]);
        }
        sleep(1);
    }
}

int main()
{
    /* code */
    int id[N];
    for (int i=0;i<N;i++)
    {
        buffer[i] = 0;
        init_sem(&empty[i],1);
        init_sem(&full[i],0);
        id[i] = i;
    }
    for (int i=0;i<N; i++)
    {
        start_thread(updateArray, &id[i]);
    }
    displayArray();
    return 0;
}




