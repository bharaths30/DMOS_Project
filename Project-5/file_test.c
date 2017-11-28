#include<stdio.h>
#include "msgs.h"

int currentClientID;
char filenameMappings[100][100];

//Server listens at port 0, so client sends messages to port 0

int computeReceivedMessage(data *rcvd_msg)
{
	int errCode = 0;
	if (rcvd_msg->isFileName == true)
	{
		if(strlen(rcvd_msg->message) > 15)
		{	
			printf("\nFile name exceeded 15 chars");
			errCode = -1;
			return errCode;
		}
		else
		{
			errCode = 1;
			return errCode;
		}
		
	}
	else if (rcvd_msg->isFileContent == true)
	{
		if(strlen(rcvd_msg->message) > 1048576)
		{
			printf("\nFile size exceeded 1MB");
			errCode = -2;
			return errCode;
		}
		else
		{
			errCode = 2;
			return errCode;
		}	
	}
	else 
	{
		if(strcmp(rcvd_msg->message,"DONE") == 0)
		{
			errCode = 3;
			return errCode;
		}
	}
	return errCode;
}

void createFile(char *filename_client)
{
	char *filename_server = (char *)malloc(strlen(filename_client)+7);
	strcpy(filename_server, filename_client);
	strcat(filename_server, ".server");
	FILE *newFilePtr = fopen(filename_server, "ab+");
	fclose(newFilePtr);		
}

void writeFile(char *filename_client, char *content)
{
        char *filename_server = (char *)malloc(strlen(filename_client)+7);
        strcpy(filename_server, filename_client);
        strcat(filename_server, ".server");
        FILE *newFilePtr = fopen(filename_server, "ab+");
	//printf("\nWriting content to file named %s", filename_server);
        fwrite(content, sizeof(char), strlen(content), newFilePtr);
	fclose(newFilePtr);
}

void closeFile(FILE *fp)
{
	fclose(fp);
}

void server()
{
	int receive_port_no = 0, status;
	int noOfActiveClients = 0;

	printf("\n\tServer recieves files on port %d",receive_port_no);
	while(1)
	{	
		//printf("No. of active clients %d", noOfActiveClients);
		data *rcvd_msg = (data *)malloc(sizeof(data));
		receive(receive_port_no, rcvd_msg);
		int status = computeReceivedMessage(rcvd_msg);
		if (status == -1 || status == -2)
		{
			printf("\n\tServer: Client %d's file transfer request failed", rcvd_msg->replyPortNo-1); 
			if (status == -2)
			{
				noOfActiveClients--;
			}
			data *replyMsg = (data *)malloc(sizeof(data));
			replyMsg->message = (char *)malloc(5);
			strcpy(replyMsg->message, "FAIL");
			replyMsg->replyPortNo = 0;
			send(rcvd_msg->replyPortNo, replyMsg);
				
		}
		else if(status == 1 && noOfActiveClients < 3)
		{
			noOfActiveClients++;
			createFile(rcvd_msg->message);

			printf("\n\tServer created a file named %s.server", rcvd_msg->message);
			data *replyMsg = (data *)malloc(sizeof(data));
                        replyMsg->message = (char *)malloc(15);
                        strcpy(replyMsg->message, "FILE_CREATED");
                        replyMsg->replyPortNo = 0;
                        send(rcvd_msg->replyPortNo, replyMsg);
		}
		else if(status == 1 && noOfActiveClients >= 3)
		{
			printf("\n\tServer: There are already 3 clients that are currently transferring files. So the request by client %d will be blocked until server receives a message from one or more of the clients saying file transfer is done.", rcvd_msg->replyPortNo-1);
			data *replyMsg = (data *)malloc(sizeof(data));
                        replyMsg->message = (char *)malloc(24);
                        strcpy(replyMsg->message, "MAX_REQUESTS_REACHED");
                        replyMsg->replyPortNo = 0;
                        send(rcvd_msg->replyPortNo, replyMsg);
		}
		else if(status == 2)
		{
			int cl_id = rcvd_msg->replyPortNo - 1;
			char * w_fileName = (char *) malloc(sizeof(filenameMappings[cl_id]));
			strcpy(w_fileName, filenameMappings[cl_id]);
			writeFile(w_fileName, rcvd_msg->message);

			printf("\n\tServer wrote content received from client %d into the file %s.server", rcvd_msg->replyPortNo-1, w_fileName);
			data *replyMsg = (data *)malloc(sizeof(data));
                        replyMsg->message = (char *)malloc(24);
                        strcpy(replyMsg->message, "TRANSFER_COMPLETED");
                        replyMsg->replyPortNo = 0;
                        send(rcvd_msg->replyPortNo, replyMsg);
							
		}
		else if(status == 3)
		{
			printf("\n\tServer received a message from client %d saying file transfer is complete", rcvd_msg->replyPortNo-1);	
			noOfActiveClients--;
		}
			
	}
}

void threadExit()
{
	while(1)
	{
		sleep(1);
		yield();
	}
}

char* readFile_Client(char *filename)
{
	FILE * fp = fopen(filename, "rb");
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	rewind(fp);
	char *f_content = (char *)malloc(fSize*sizeof(char));
	fread(f_content, sizeof(char), fSize, fp);
	printf("\nFile %s is read", filename);
	fclose(fp);
	return f_content;
}

void clientOp(int id, int send_port_no, int receive_port_no, char *fname)
{
	data *request_data = (data *)malloc(sizeof(data));
	int i;
	//Send filename
	request_data->replyPortNo = receive_port_no;
	request_data->isFileName = true;
	//request_data->isFileContent = false;
	//request_data->isTransferDone = false;
	request_data->message = (char *)malloc(strlen(fname));
	strcpy(request_data->message, fname);	
	while(1)
	{
		printf("\nClient %d sending a request to the server with the filename %s", id, fname);
		send(send_port_no, request_data);

		data *result = (data *)malloc(sizeof(data));
		receive(receive_port_no, result);
		if (strcmp(result->message, "FAIL") == 0)
		{
			threadExit();
		}
		else if (strcmp(result->message, "FILE_CREATED") == 0) 
		{
			char *f_content = readFile_Client(fname);
			data *requestContentdata = (data *)malloc(sizeof(data));	
			requestContentdata->message = f_content;
			requestContentdata->replyPortNo = receive_port_no;
			requestContentdata->isFileName = false;
			requestContentdata->isFileContent = true;
			//requestContentdata->isTransferDone = false;
			printf("\nClient %d is sending the content of the file named %s to the server for processing", id, fname);
			send(send_port_no, requestContentdata);
			
			data *result_transfer = (data *)malloc(sizeof(data));
			receive(receive_port_no, result_transfer);	
			if (strcmp(result->message, "FAIL") == 0)
	                {
        	                threadExit();
                	}
			else
			{
				data *requestAck = (data *)malloc(sizeof(data));
				requestAck->message = (char *)malloc(5);
				
				printf("\nClient %d is sending file transfer is done", id);
				strcpy(requestAck->message, "DONE");
				requestAck->replyPortNo = receive_port_no;
				requestAck->isFileName = false;
				requestAck->isFileContent = false;
				requestAck->isTransferDone = true;
				send(send_port_no, requestAck);		
			}

			break;
		}
		else if (strcmp(result->message, "MAX_REQUESTS_REACHED") == 0)
		{
			sleep(2);
			yield();
		}
	}
	threadExit();
		
	// actions to do after receive	
}

void client()
{
	int send_port_no = 0;
	currentClientID++; //global
	int receive_port_no = currentClientID+1;
	int id = currentClientID;
	char *filename = (char *) malloc(strlen(filenameMappings[currentClientID]));
	strcpy(filename, filenameMappings[currentClientID]);
	printf("\nClient %d sends file to port %d and recieves reply on %d",id, send_port_no ,receive_port_no );
	clientOp(id, send_port_no, receive_port_no, filename);

}

int main(int argc, char *argv[])
{
	currentClientID = -1;
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
			strcpy(filenameMappings[i], argv[i+2]); 
			start_thread(client);
		}
	}
	run();
	while(1)
	{	
		sleep(1);
	}

}
