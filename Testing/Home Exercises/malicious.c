#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//thread data structure
typedef struct thread_data{
	int ThreadID;
	int RepeatMessage;
} threadData;

//my thread function
void *printer(void * arg){
	threadData * myThreadPtr = (threadData *) arg;

	while(true){
		for (int i = 0; i< myThreadPtr -> RepeatMessage; i++){
			printf("ThreadID: %d\n", myThreadPtr -> ThreadID );
		}
	}

	//notifies main that the particular thread is finished from execution
	pthread_exit(NULL);
}

int main(void){
	int returnVal;

	//creating an array of pthreads to have a reference to each
	pthread_t myThread;

	//allocating memory for the struct and setting the values
	threadData *tdata;
	tdata = (threadData *) malloc (sizeof(threadData));

	//generating random values and storing them in struct
	tdata-> ThreadID = rand() % 1001;
	tdata -> RepeatMessage = rand() % 21;

	returnVal = pthread_create(&myThread, NULL, printer, (void *) tdata);

	//check if some error occurred
	if(returnVal == 0){
		printf("No Error Occurred.\n");
	}else{
		printf("Warning! Error!\n");
	}

	pthread_join(myThread, NULL);

	return 0;
}