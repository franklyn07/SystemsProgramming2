#include <stdio.h>
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

	for (int i = 0; i< myThreadPtr -> RepeatMessage; i++){
		printf("ThreadID: %d\n", myThreadPtr -> ThreadID );
		sleep(2);
	}

	printf("Thread %d printed %d times\n",myThreadPtr -> ThreadID, myThreadPtr -> RepeatMessage);

	//notifies main that the particular thread is finished from execution
	pthread_exit(NULL);
}

int main(void){
	int returnVal;

	//generating a random number of threads to be produced
	int amntThreads = rand() % 22;

	//creating an array of pthreads to have a reference to each
	pthread_t myThread[amntThreads];

	printf("Number of Threads to be produced: %d\n",amntThreads);
	//creating a random number of threads
	for (int i = 0; i< amntThreads; i++){

		//allocating memory for the struct and setting the values
		threadData *tdata;
		tdata = (threadData *) malloc (sizeof(threadData));

		//generating random values and storing them in struct
		tdata-> ThreadID = rand() % 1001;
		tdata -> RepeatMessage = rand() % 21;

		returnVal = pthread_create(&myThread[i], NULL, printer, (void *) tdata);

		//check if some error occurred
		if(returnVal == 0){
			printf("No Error Occurred.\n");
		}else{
			printf("Warning! Error!\n");
		}
	}

	//this waits for the threads to finish before continuouing execution in main thread
	//by joining each one of them created to the main thread
	for(int i = 0; i < amntThreads; i++){
		pthread_join(myThread[i], NULL);
	}

	//for debugging purposes to check that no thread is still running
	printf("Finish\n");
	sleep(10);
	return 0;
}