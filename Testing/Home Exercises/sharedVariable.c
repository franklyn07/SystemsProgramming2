#include <stdio.h>
//library used to include 65 bit integer
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>

//enables mutex to lock variable for a specific thread
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

//my thread function
void *increment(void * arg){
	int64_t* counter = (int64_t*) arg;
	pthread_mutex_lock(&lock);
	for(int i =	0;	i <	100000;	i++){
		(*counter)++;
		if	((*counter)	%	1000	==	0)	{
			printf("another	1000\n");
		}
	}
	pthread_mutex_unlock(&lock);
	printf("Thread Finished!\n");
	pthread_exit(NULL);
}

int main(void){

	//global counter - all 10 threads will be updating this global counter
	int64_t counter = 0;

	int returnVal;

	pthread_t myThread[10];

	//generating 10 threads
	for (int i = 0; i < 10; ++i){
		//creating the thread
		returnVal = pthread_create(&myThread[i], NULL, increment, (void *) &counter);

		//check if some error occurred
		if(returnVal == 0){
			printf("No Error Occurred.\n");
		}else{
			printf("Warning! Error!\n");
		}
	}

	for (int i = 0; i < 10; ++i){
		//this waits for the threads to finish before continuouing execution in main thread
		pthread_join(myThread[i], NULL);
	}
	
	printf("Counter: %lu\n",counter );

	pthread_mutex_destroy(&lock);

	return 0;
}
