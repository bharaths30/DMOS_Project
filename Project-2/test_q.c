#include<stdio.h>
#include "q.h"

int main()
{
	TCB_t *hdr = NewQueue();
	int count = 3;
	int i;
	for (i=0; i<count; i++)
	{
		TCB_t *new_item = NewItem();
		new_item->thread_id = i+1;
		AddQueue(hdr, new_item);
	}
	for (i=0; i<count+1; i++)
	{
		TCB_t *first_item = DelQueue(hdr);
		if (first_item == NULL)
		{
			return -1;
		}
		printf("Value: %d\n", first_item->thread_id);
		FreeItem(first_item);
	}
	return 0;
}
