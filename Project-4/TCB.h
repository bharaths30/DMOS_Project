/*
Assignment #4:
Student 1: Bharath Kumar Suresh (ASU ID: 1211182086)
Student 2: Vamsi Krishna Godavarthi (ASU ID: 1210933825) 

Task:
All the built-in types and functions used in this step come from a library named ucontext
The queue items used for handling the threads is the TCB_t. A TCB_t is a structure that contains a next pointer,
a previous pointer. 
A thread_id (int)  and a data item called context, of the type “ucontext_t”.

It is initialized as:

*/

#include <ucontext.h> 
#include <string.h>

typedef struct TCB_t {
	struct TCB_t *next;
	struct TCB_t *previous;
	int thread_id;
	ucontext_t context;
} TCB_t;

void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)
{
    memset(tcb, '\0', sizeof(TCB_t));       // wash, rinse
    getcontext(&tcb->context);              // have to get parent context, else snow forms on hell
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t) stack_size;
    makecontext(&tcb->context, function, 0);// context is now cooked
}
