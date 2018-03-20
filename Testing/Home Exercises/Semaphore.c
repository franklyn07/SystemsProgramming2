#include <stdio.h>
//library used to include 65 bit integer
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>


struct semaphore
{
	int lock;
	int initialValue;
};

struct semaphore s1Ptr;

void sm_create(struct semaphore * sPtr,int initVal){
	sPtr->initialValue = initVal;
	sPtr->lock = 0;
}

void sm_destroy(struct semaphore * semaphorePtr){
	
}

void sm_wait(struct semaphore * sPtr){
	while(__sync_lock_test_and_set(&sPtr->lock,1));
	while(sPtr->initialValue <= 0);
	sPtr->initialValue-=1;
	__sync_lock_release(&sPtr->lock);
}

void sm_signal(struct semaphore *sPtr){
	while(__sync_lock_test_and_set(&sPtr->lock,1));
	sPtr->initialValue +=1;
	__sync_lock_release(&sPtr->lock);
}

//my thread function
void *increment(void * arg){
	int64_t* counter = (int64_t*) arg;
	sm_create(&s1Ptr, 1);
	sm_wait(&s1Ptr);
	for(int i =	0;	i <	100000;	i++){
		(*counter)++;
		if	((*counter)	%	1000	==	0)	{
			printf("another	1000\n");
		}
	}
	sm_signal(&s1Ptr);
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

	sleep(10);

	return 0;
}
