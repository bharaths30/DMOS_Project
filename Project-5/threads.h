/*
Assignment #5:
Student 1: Bharath Kumar Suresh (ASU ID: 1211182086)
Student 2: Vamsi Krishna Godavarthi (ASU ID: 1210933825) 

Task:
Contains two global variables: ReadyQ and Curr_Thread.
ReadyQ points to a queue of TCBs and Curr_Thread points to the thread under execution (one TCB)

Routines to “start thread” and “yield” and the “run” routine which cranks up the works.
q.h needs to be included for the working of the functions

*/

#include "q.h"

TCB_t *ReadyQ;
TCB_t *Curr_Thread;
int stack_size = 8192;
int threadID = 0;

void start_thread(void *func)
{
	void  *stackP = malloc(stack_size);
	TCB_t *tcb    = (TCB_t *)malloc(sizeof(TCB_t));
	init_TCB(tcb, func, stackP, stack_size);
	threadID++;
	tcb->thread_id = threadID;
	AddQueue(ReadyQ, tcb);
	printf("Thread created\n");
}

void run()
{
	Curr_Thread = DelQueue(ReadyQ);
    	ucontext_t parent;     // get a place to store the main context, for faking
	getcontext(&parent);   // magic sauce
	swapcontext(&parent, &(Curr_Thread->context));  // start the first thread
}	

void yield() // similar to run
{
	TCB_t *Prev_Thread;
	AddQueue(ReadyQ, Curr_Thread);
	Prev_Thread = Curr_Thread;
   	Curr_Thread = DelQueue(ReadyQ);
   	//swap the context, from Prev_Thread to the thread pointed to Curr_Thread
	swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));
}

int getThreadID()
{
	return Curr_Thread->thread_id;
}

void setReadyQueue()
{
	ReadyQ = NewQueue();
}
