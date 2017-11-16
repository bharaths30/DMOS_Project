/*
Assignment #4:
Student 1: Bharath Kumar Suresh (ASU ID: 1211182086)
Student 2: Vamsi Krishna Godavarthi (ASU ID: 1210933825)

Task: 
The queue must be a circular doubly linked consisting of q-elements. 
The first q-element in the queue is a header, and this is a dummy element. 
The head pointer points to the dummy element.
A queue consists of a head-pointer and a set of q-elements. 
A q-element is a structure, consisting of a prev and next pointer, and a payload consisting of 1 integer.


The functions that are implemented :

1.     item = NewItem(); // returns a pointer to a new q-element, uses memory allocation

2.     head = newQueue() // creates a empty queue, consisting of one dummy element, returns the head pointer.

3.     AddQueue(head, item) // adds a queue item, pointed to by “item”, to the queue pointed to by head.

4.     item = DelQueue(head) // deletes an item from head and returns a pointer to the deleted item. If the queue is already empty, flag error.

*/

#include "TCB.h"
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>


TCB_t *NewItem()
{
	TCB_t *item_ptr;
	item_ptr = (TCB_t *)malloc(sizeof(TCB_t));
	return item_ptr;
}

TCB_t *NewQueue()
{
	//printf("Creating new queue\n");
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
	if (head->next == head)
	{	
		errno = EBADR;
		perror("Queue is Empty");
		return NULL;
	}

	TCB_t *firstItem = head->next;
	head->next = firstItem->next;
	firstItem->next->previous = head;
	
	return firstItem;
}

void FreeItem(TCB_t *item)
{
	free(item);
}
