#include "threads.h"

int global = 0;

void function_1()
{
	int local = 0;
	while(1)
	{
		global++;
		local++;
		printf("Func 1, Global value is: %d and Local value is: %d\n", global, local);
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
                printf("Func 2, Global value is: %d and Local value is: %d\n", global, local);
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
                printf("Func 3, Global value is: %d and Local value is: %d\n", global, local);
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
	run();	
	return 0;
}
