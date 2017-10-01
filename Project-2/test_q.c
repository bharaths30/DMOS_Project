#include<stdio.h>
#include "q.h"

int main()
{
	node *hdr = NewQueue();
	int count = 3;
	int i;
	for (i=0; i<count; i++)
	{
		node *new_item = NewItem();
		new_item->payload = i+1;
		AddQueue(hdr, new_item);
	}
	for (i=0; i<count+1; i++)
	{
		node *first_item = DelQueue(hdr);
		printf("Value: %d\n", first_item->payload);
	}
	return 0;
}
