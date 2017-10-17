/*
Assignment #3:
Student 1: Bharath Kumar Suresh (ASU ID: 1211182086)
Student 2: Vamsi Krishna Godavarthi (ASU ID: 1210933825) 

Task:
Implement the routines 

1. Semaphonre_t CreateSem(int InputValue) mallocs a semaphore structure, initializes it to the InitValue and returns the pointer to the semaphore.

2. void P(Semaphonre_t *sem) takes a pointer to a semaphore and performs P, i.e. decrements the semaphore, and if the value is less than zero
							 then blocks the thread in the queue associated with the semaphore.

3. void V(Semephore_t *sem) increments the semaphore, and if the value is 0 or negative, then takes a PCB out of the semaphore queue 
							and puts it into the ReadyQ.

Note: The V routine also "yields" to the next runnable thread.
*/

#include "threads.h"

typdef struct Semaphore {
	int counter;
	Queue *queue;
} Semaphore_t;

Semaphore_t CreateSem(Semaphore_t *sem,int InputValue)
{
	sem->queue = NewQueue(sem->queue);
	sem->counter = InputValue;
}

void P(Semaphore_t *sem)
{
	TCB_t *previous;
	sem->counter--;
	if (sem->counter < 0)
	{
		AddQueue(sem->queue,Curr_Thread);
		previous = Curr_Thread;
		Curr_Thread = DelQueue(ReadyQ);
		swapcontext(&(previous->context),&(Curr_Thread->context));
	}
}

void V(Semaphore_t *sem)
{
	TCB_t *next;
	sem->counter++;
	if(sem->counter <= 0)
	{
		next = DelQueue(sem->queue);
		AddQueue(ReadyQ,next);

	}
	yeild();
}