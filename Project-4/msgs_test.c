#include<stdio.h>
#include "msgs.h"

void printArr(int *arr)
{
	int i;
	for(i = 0; i<10; i++)
	{
		printf("%d ",arr[i]); 
	}
	printf("\n");
}

void server()
{
	while(1)
	{
		int data[10];
		int receive_port_no = 43;
		int send_port_no = 80;
		receive(receive_port_no, data);
		printf("\nServer received request message from port %d: ", receive_port_no);
        	printArr(data);
		int result[10];
		int i;
		for(i=0; i<10; i++)
		{
			result[i] = data[i]*2;
		}
		printf("\nServer sending computed result to port %d: ", send_port_no);
		printArr(result);
		send(send_port_no, result);
		sleep(1);
	}
}

void client()
{
	while(1)
	{
		int request_data[10];
		int send_port_no = 43;
		int receive_port_no = 80;
		//srand(0);
		int i;
		for (i = 0; i < 10; i++) 
		{
    			request_data[i] = rand() % 512;
			//printf("\t%d", request_data[i]);
		}
		printf("\nClient sending request message to port %d: ", send_port_no);
		printArr(request_data);
		send(send_port_no, request_data);
		int result[10];
		receive(receive_port_no, result);
		printf("\nClient received result message from port %d: ", receive_port_no);
		printArr(result);	
	}
}

int main()
{
	setReadyQueue();
	init_ports();
	start_thread(client);
	start_thread(server);
	run();
	while (1) {
	}
}
