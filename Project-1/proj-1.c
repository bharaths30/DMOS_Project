/*
Assignment #1:

Student 1: Bharath Kumar Suresh (ASU ID: 1211182086)
Student 2: Vamsi Krishna Godavarthi (ASU ID: 1210933825) 

Task: 
Write a program that does the following.
1.       The main (parent) thread initializes an array of 3 integers to zero.
2.       The parent creates 3 children. Child i adds 1 to array[i], where i = 0, 1, 2.
3.       The parent waits for the children to finish adding, and then prints the values in the array.
4.       The children wait for the parent to finish printing and then repeats (adds 1 to an an element of the array)
5.       Continues forever

How to Compile:
    gcc -lpthread proj-1.c  (or) gcc -pthread proj-1.c

How to Run:  
    ./a.out

*/

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
        printf("\n\nValues of elements present in the array are:");
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