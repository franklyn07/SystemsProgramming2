#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

/*note that all the type casting is from void pointer and to it are occuring since void pointer is used by the library
since they don't know the parameter we are going to pass, thus they leave it an open vehicile which you can use to 
troansform to desired form*/

typedef struct thread_data{
	long threadid;
	char*message;
} thread_data_t;

void *MyThread(void *arg){
	thread_data_t *data;
	data = (thread_data_t *)arg;
	printf("From inside the created thread: %ld %s\n", data->threadid, data ->message);
	pthread_exit(NULL);
}

int main (void){
	//allocating memory for the struct and setting the values
	thread_data_t *tdata;
	tdata = (thread_data_t *) malloc (sizeof(thread_data_t));
	tdata-> threadid = 456;
	tdata -> message = "test";

	int returnval;

	//thread as a name is used as an identifier for this thread (remember even if multiple threads they will all share memory location)
	pthread_t thread;

	printf("Pthreads example\n");

	long tid = 123;
	//returnval should be checked - if 0 no error occurred in thread creation
	//here we will have 2 lines of execution - one will continue running the main and one the thread created
	returnval = pthread_create(&thread, NULL, MyThread, (void*) tdata);
	sleep(1);
	return 0;
}