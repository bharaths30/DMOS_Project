/*
Assignment #5:
Student 1: Bharath Kumar Suresh (ASU ID: 1211182086)
Student 2: Vamsi Krishna Godavarthi (ASU ID: 1210933825)

Task: 

Step 1:
Declare a port. A port is something that contains N messages, make N=10. There would be semaphores associated with the port, for controlling synchronization. 
The port “contains” messages hence a port may be a pointer to a Q of messages, or an array of messages.

Declare a message type. For simplicity, a message is an array of 10 integers.

Declare a set (array of ports). The ports are numbered 0 to 99.

Step 2:
Implement the routines

Send (with appropriate arguments). The send is a “blocking” asynchronous send that is: 
it places the message in the port and returns but blocks if port is full.
 
Receive (with appropriate arguments). The receive is a “blocking” receive.

*/
#include "sem.h"
#define NUMBER_OF_MSGS 10
#define SIZE_OF_MSG 10
#define NUMBER_OF_PORTS 100

typedef struct data {
	int replyPortNo;
	int message[SIZE_OF_MSG];	
}data;

typedef struct port {
	int number;
	data *content;
	semaphore_t empty, full, mutex;
	int in, out;
}port;

port *ports;

void init_ports()
{
	ports = (port *) malloc(sizeof(port)*NUMBER_OF_PORTS);
	int i = 0;
	for (i=0;i<NUMBER_OF_PORTS;i++)
	{
		ports[i].number = i;	
		//ports[i].message = (int (*)[SIZE_OF_MSG])malloc(NUMBER_OF_MSGS*sizeof(int [SIZE_OF_MSG]));
		ports[i].content = (data *)malloc(NUMBER_OF_MSGS*sizeof(data));
		ports[i].empty = CreateSem(NUMBER_OF_MSGS);
		ports[i].full = CreateSem(0);
		ports[i].mutex = CreateSem(1);
		ports[i].in = 0;
		ports[i].out = 0;
	}
}

void send(int port_num, data *data_ptr)
{
    P(&ports[port_num].empty);
    P(&ports[port_num].mutex);
	//printf("\nSending message to Port %d in slot %d", port_num, ports[port_num].in);
	memcpy(&ports[port_num].content[ports[port_num].in], data_ptr, sizeof(data));
	ports[port_num].in = (ports[port_num].in+1) % NUMBER_OF_MSGS;
    V(&ports[port_num].mutex);
    V(&ports[port_num].full);	
}

void receive(int port_num, data *msg)
{
	P(&ports[port_num].full);
    P(&ports[port_num].mutex);
	//printf("\nReceiving from Port %d from slot %d", port_num, ports[port_num].out);
	memcpy(msg, &ports[port_num].content[ports[port_num].out], sizeof(data));
    ports[port_num].out = (ports[port_num].out+1) % NUMBER_OF_MSGS;
    V(&ports[port_num].mutex);
    V(&ports[port_num].empty);	
}