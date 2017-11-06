/*
Assignment #4:
Student 1: Bharath Kumar Suresh (ASU ID: 1211182086)
Student 2: Vamsi Krishna Godavarthi (ASU ID: 1210933825)

Task: 
Step 1:
Declare a port. A port is something that contains N messages, make N=10.
There would be semaphores associated with the port, for controlling synchronization.
The port “contains” messages hence a port may be a pointer to a Q of messages, or an array of messages.

Declare a message type. For simplicity, a message is an array of 10 integers.

Declare a set (array of ports). The ports are numbered 0 to 99.

Step 2:
Implement the routines

Send (with appropriate arguments).The send is a “blocking” asynchronous send that is:
it places the message in the port and returns but blocks if port is full.
 
Receive (with appropriate arguments). The receive is a “blocking” receive.
 
Put the code in msgs.h, and include sem.h in the file msgs.h

*/

#include sem.h

typedef port {
	int number;
	int message[10];
}port;


void init_ports()
{
	port p[100];
	int i = 0;
	for (i=0;i<100;i++)
	{
		p[i].number = i;
		p[i].message = [0,0,0,0,0,0,0,0,0,0];
	}
}

void send(port_num,message)
{

}

void receive(port_num,message)
{
	
}