/*
Assignment #2:
Student 1: Bharath Kumar Suresh (ASU ID: 1211182086)
Student 2: Vamsi Krishna Godavarthi (ASU ID: 1210933825)

Task:
Roll the code and light the fire.
Remember to include threads.h which includes q.h, which includes TCB.h, which includes ucontext.h
Write a few functions with infinite loops (put an yield in each loop).
Start them up, from main, using start_thread
Call run() and watch.  // note try to write thread functions that are meaningful, use global and local variables
Call friends and family

How to Compile:
    gcc threads_test.c
    
How to Run:  
    ./a.out

*/
#include "threads.h"

int global = 0;

void function_1()
{
	int local = 0;
	while(1)
	{
		global++;
		local++;
		printf("Func 1, Thread ID is: %d Global value is: %d and Local value is: %d\n", getThreadID(), global, local);
		sleep(1);
		yield();
	}
}

void function_2()
{
        int local = 0;
        while(1)
        {
                global++;
                local++;
                printf("Func 2, Thread ID is: %d Global value is: %d and Local value is: %d\n", getThreadID(), global, local);
		sleep(1);
                yield();
        }
}

void function_3()
{
        int local = 0;
        while(1)
        {
                global++;
                local++;
                printf("Func 3, Thread ID is: %d Global value is: %d and Local value is: %d\n", getThreadID(), global, local);
		sleep(1);
                yield();
        }
}

void function_4()
{
        int local = 0;
        while(1)
        {
                global++;
                local++;
                printf("Func 4, Thread ID is: %d Global value is: %d and Local value is: %d\n", getThreadID(), global, local);
                sleep(1);
                yield();
        }
}

int main()
{
	setReadyQueue();
	start_thread(function_1);
	start_thread(function_2);
	start_thread(function_3);
	start_thread(function_4);
	start_thread(function_4);
	run();	
	return 0;
}
