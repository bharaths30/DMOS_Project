#include "TCB.h"
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

/*typedef struct TCB_t 
{
	int thread_id;
	struct TCB_t *previous;
	struct TCB_t *next;
} TCB_t;*/

TCB_t *NewItem()
{
	TCB_t *item_ptr;
	item_ptr = (TCB_t *)malloc(sizeof(TCB_t));
	return item_ptr;
}

TCB_t *NewQueue()
{
	TCB_t *head      = NewItem();
	head->thread_id  = -1;
	head->previous   = head;
	head->next       = head;
	return head;
}

void AddQueue(TCB_t *head, TCB_t *item)
{
	TCB_t *curr_tail = head->previous;
	curr_tail->next  = item;
	item->previous 	 = curr_tail;
	item->next	 = head;
	head->previous	 = item;				
}

TCB_t *DelQueue(TCB_t *head)
{
	//need to return head->next
	if (head->next == head)
	{	
		errno = EBADR;
		perror("Queue is Empty");
		return NULL;
		//exit(EXIT_FAILURE);
	}

	TCB_t *firstItem = head->next;
	head->next = firstItem->next;
	firstItem->next->previous = head;
	
	return firstItem;
}

void FreeItem(TCB_t *item)
{
	free(item); //Deallocate memory
}
