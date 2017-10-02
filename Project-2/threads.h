#include "q.h"

TCB_t *ReadyQ;
TCB_t *Curr_Thread;
int stack_size = 8192;
int threadID = 0;

void start_thread(void *func)
{
	void  *stackP = malloc(stack_size);
	TCB_t *tcb    = (TCB_t *)malloc(sizeof(TCB_t *));
	init_TCB(tcb, func, stackP, stack_size);
	threadID++;
	tcb->thread_id = threadID;
	AddQueue(ReadyQ, tcb);
}

void run()
{
	Curr_Thread = DelQueue(ReadyQ)
    	ucontext_t parent;     // get a place to store the main context, for faking
	getcontext(&parent);   // magic sauce
	swapcontext(&parent, &(Curr_Thread->context));  // start the first thread
}	

void yield() // similar to run
{
	TCB_t *Prev_Thread;
	AddQueue(Ready_Q, Curr_Thread);
	Prev_Thread = Curr_Thread;
   	Curr_Thread = DelQueue(ReadyQ);
   	//swap the context, from Prev_Thread to the thread pointed to Curr_Thread
	swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));
}

void setReadyQueue()
{
	ReadyQ = NewQueue();
}
