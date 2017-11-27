#include<stdio.h>
#include "msgs.h"

void computeReceivedMessage()
{
	if (rcvd_msg.fileName == true)
	{

	}
	else if (rcvd_msg.fileData == true)
	{

	}
	else 
	{

	}
}

void server()
{
	int recieve_port_no = 43;
	printf("\nServer recieves files on port %d",recieve_port_no);
	while(1)
	{
		data *rcvd_msg = (data *)malloc(sizeof(data));
		receive(receive_port_no, rcvd_msg);
		computeReceivedMessage();
		// write data into file
	}
}

void clientOp(int id, int send_port_no, int receive_port_no)
{
	while(1)
	{
		data *request_data = (data *)malloc(sizeof(data));

		int i;
		request_data->replyPortNo = receive_port_no;
		
		// data to send
		
		send(send_port_no, request_data);

		data *result = (data *)malloc(sizeof(data));
		receive(receive_port_no, result);
		
		// actions to do after receive	
	}
}

void client()
{
	int send_port = 43;
	int recieve_port_no = 80;
	int id = 0;
	printf("Client%d sends file to port %d and recieves reply on %d\n",id,send_port,recieve_port_no );
	clientOp(id, send_port_no, receive_port_no);

}

int main(int argc, char *argv[])
{
	if (argc < 2 || atoi(argv[1]) != argc-2 )
	{
		printf("Error in command execution\n");
		return 0;
	}
	else
	{
		setReadyQueue();
		init_ports();
		printf("Starting server\n");
		start_thread(server);
		for(int i=0;i<atoi(argv[1]);i++)
		{
			printf("Starting client%d\n",i);
			start_thread(client);
		}
	}
	run();
	while(1)
	{
	}

}