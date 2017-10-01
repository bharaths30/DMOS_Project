#include "TCB.h"
#include<stdlib.h>
#include<errno.h>

typedef struct node 
{
	int payload;
	node *prev;
	node *next;
} node;

node *NewItem()
{
	node *item_ptr;
	item_ptr = (node *)malloc(sizeof(node));
	return item_ptr;
}

node *NewQueue()
{
	node *head    =NewItem();
	head->payload =-1;
	head->prev    =null;
	head->next    =null;
	return hdr;
}

void AddQueue(node *head, node *item)
{
	if (head->prev == null)	//only the dummy element is present
	{
		head->prev = item;
		head->next = item;
		item->next = head;
		item->prev = next;	
	}
	else 
	{
		node *curr_tail = head->prev;
		curr_tail->next = item;
		item->prev 	= curr_tail;
		item->next	= head;
		head->prev	= item;			
	}	
}

node *DelQueue(node *head)
{
	//need to return head->next
	if (head->next == null)
	{
		perror("Queue is Empty");
		exit(EXIT_FAILURE);
	}
	node *firstItem = head->next;
	if (firstItem->next->payload == -1) //Pointing to dummy head, based on -1 payload
	{	
		head->prev = null;
		head->next = null;	
	}
	else
	{
		head->next            = firstItem->next;
		firstItem->next->prev = head;
	}
	return firstItem;
}

void FreeItem(node *item)
{
	free(item); //Deallocate memory
}
