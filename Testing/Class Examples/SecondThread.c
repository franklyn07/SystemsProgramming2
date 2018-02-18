#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *MyThread(void *threadid){
	long tid;
	tid = (long)threadid;
	printf("From insid ethe created therad: %ld", tid);
	pthread_exit(NULL);
}

int main (void){
	int returnval;

	//thread as a name is used as an identifier for this thread (remember even if multiple threads they will all share memory location)
	pthread_t thread;

	printf("Pthreads example");

	long tid = 123;
	//returnval should be checked - if 0 no error occurred in thread creation
	//here we will have 2 lines of execution - one will continue running the main and one the thread created
	returnval = pthread_create(&thread, NULL, MyThread, (void*) tid);
	sleep(1);
	return 0;
}