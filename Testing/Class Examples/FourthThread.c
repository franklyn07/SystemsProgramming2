#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

//global variable which keeps hold whether the run once code has run or not
static pthread_once_t runonce = PTHREAD_ONCE_INIT;

//cleanup function - this can be called if there is an outside cancellation
//or if directly invoked from within the thread
void thread_cleanup(void *arg){
	printf("DO CLEANUP");
}

void run_once_for_all_threads(){
	printf("(this should be run once!))\n");
}

void run_for_every_thread(){
	printf("this hsould be run for every thread!\n");
}

typedef struct thread_data{
	long threadid;
	char*message;
} thread_data_t;

void *MyThread(void *arg){
	//this code will run the first time this thread is invoked
	int err = pthread_once(&runonce, run_once_for_all_threads);

	//this code will run in each end every thread
	run_for_every_thread();

	//we push on the stack the cleanup function - if thread is cancelled from outside
	//the function is popped off the stack through pthread_cleanup_pop
	pthread_cleanup_push(thread_cleanup, NULL);
	thread_data_t *data;
	data = (thread_data_t *)arg;
	int i;
	for(i = 0; i < 10; i++){
		printf("From insid ethe created thread: %ld %s\n", data->threadid, data ->message);	
		sleep(2);
	}
	
	pthread_exit(NULL);
	pthread_cleanup_pop(1);
	//else the pthread_cleanup_pop and pthread_cleanup_push can be eliminated and 
	//we directly invoke thread_cleanup and we would cleanup always, irrispective
	//of whether thread was cancelled or not 
}

void *ThreadThatSleeps(void *arg){
	//this will prevent the pthread_cancle function from cancelling this thread
	//(however note that it can still be killed if we send a direct signal to it)
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	sleep(10);
	printf("Finished SLeeping\n");
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
	pthread_t threadSleep;

	printf("Pthreads example\n");

	long tid = 123;
	//returnval should be checked - if 0 no error occurred in thread creation
	//here we will have 2 lines of execution - one will continue running the main and one the thread created
	returnval = pthread_create(&thread, NULL, MyThread, (void*) tdata);
	returnval = pthread_create(&threadSleep, NULL, ThreadThatSleeps, NULL);

	for(int i = 0; i<4; i++){
		returnval = pthread_create(&thread, NULL, MyThread, (void*) tdata);
	}

	//this waits for the threads to finish before continuouing execution in main thread
	pthread_join(threadSleep, NULL);

	//this will kill the 20 second long thread after threadSleep has finished
	pthread_cancel(thread);
	
	pthread_join(thread, NULL);
	return 0;
}