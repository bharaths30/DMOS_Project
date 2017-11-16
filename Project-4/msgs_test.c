/*
Assignment #4:
Student 1: Bharath Kumar Suresh (ASU ID: 1211182086)
Student 2: Vamsi Krishna Godavarthi (ASU ID: 1210933825)

Task:
Test the message passing system by writing one (or more) servers and having several clients talk to the servers.

Server 1 takes the array of size 10 and multiplies by 2
Server 2 takes the array of size 10 and multiplies by -1
How to Compile:
    gcc msgs_test.c
    
How to Run:  
    ./a.out

*/
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

void server1()
{
	int receive_port_no = 43;
	printf("\nServer1 receives messages in port %d, takes each element in the array sent and multiplies by 2 and sends it back to client", receive_port_no);
	while(1)
	{
		data *rcvd_msg = (data *)malloc(sizeof(data));
		receive(receive_port_no, rcvd_msg);

		printf("\n\tServer1 received request message in port %d: ", receive_port_no);
        printArr(rcvd_msg->message);

		//Server side computation
		data *result_data = (data *)malloc(sizeof(data));
		int i;
		for(i=0; i<10; i++)
		{
			result_data->message[i] = rcvd_msg->message[i]*2;
		}

		int send_port_no = rcvd_msg->replyPortNo;
		printf("\n\tServer1 sending computed result to port %d: ", send_port_no);
		printArr(result_data->message);
		result_data->replyPortNo = receive_port_no;
		send(send_port_no, result_data);
		sleep(1);
	}
}

void server2()
{
	int receive_port_no = 44;
	printf("\nServer2 receives messages in port %d, takes each element in the array sent and multiplies by -1 and sends it back to client", receive_port_no);
	while(1)
	{
		data *rcvd_msg = (data *)malloc(sizeof(data));
		receive(receive_port_no, rcvd_msg);

		printf("\n\tServer2 received request message in port %d: ", receive_port_no);
        printArr(rcvd_msg->message);

		//Server side computation
		data *result_data = (data *)malloc(sizeof(data));
		int i;
		for(i=0; i<10; i++)
		{
			result_data->message[i] = rcvd_msg->message[i]*-1;
		}

		int send_port_no = rcvd_msg->replyPortNo;
		printf("\n\tServer2 sending computed result to port %d: ", send_port_no);
		printArr(result_data->message);
		result_data->replyPortNo = receive_port_no;
		send(send_port_no, result_data);
		sleep(1);
	}
}

void clientOp(int id, int send_port_no, int receive_port_no)
{
	while(1)
	{
		data *request_data = (data *)malloc(sizeof(data));

		int i;
		request_data->replyPortNo = receive_port_no;
		for (i = 0; i < 10; i++) 
		{
    			request_data->message[i] = rand() % 512;
		}

		printf("\n\tClient%d sending request message to port %d: ", id, send_port_no);
		printArr(request_data->message);
		send(send_port_no, request_data);

		data *result = (data *)malloc(sizeof(data));
		receive(receive_port_no, result);
		printf("\n\tClient%d received result message in port %d: ", id, receive_port_no);
		printArr(result->message);	
	}
}

void client1()
{
	int send_port_no = 43;
	int receive_port_no = 80;
	int id = 1;
	printf("\nClient%d sends messages to port %d and receives replies from port %d", id, send_port_no, receive_port_no);
	clientOp(id, send_port_no, receive_port_no);
}

void client2()
{
	int send_port_no = 43;
    int receive_port_no = 81;
    int id = 2;
	printf("\nClient%d sends messages to port %d and receives replies from port %d", id, send_port_no, receive_port_no);
    clientOp(id, send_port_no, receive_port_no);
}

void client3()
{
	int send_port_no = 44;
    int receive_port_no = 90;
    int id = 3;
	printf("\nClient%d sends messages to port %d and receives replies from port %d", id, send_port_no, receive_port_no);
    clientOp(id, send_port_no, receive_port_no);
}

void client4()
{
	int send_port_no = 44;
    int receive_port_no = 91;
    int id = 4;
	printf("\nClient%d sends messages to port %d and receives replies from port %d", id, send_port_no, receive_port_no);
    clientOp(id, send_port_no, receive_port_no);
}

int main()
{
	setReadyQueue();
	init_ports();
	start_thread(client1);
	start_thread(client2);
	start_thread(client3);
	start_thread(client4);
	start_thread(server1);
	start_thread(server2);
	run();
	while (1) {
	}
}
