#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//pointer to the thread function
void *MyThread(){
	printf("From inside the created thread");
	//notifies the main that the thread has finished
	pthread_exit(NULL);
}

int main (void){
	int returnval;

	//thread as a name is used as an identifier for this thread (remember even if multiple threads they will all share memory location)
	pthread_t thread;

	printf("Pthreads example");

	//returnval should be checked - if 0 no error occurred in thread creation
	//here we will have 2 lines of execution - one will continue running the main and one the thread created
	returnval = pthread_create(&thread, NULL, MyThread, NULL);
	sleep(1);
	return 0;
}