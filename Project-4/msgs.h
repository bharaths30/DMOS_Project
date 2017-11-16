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
