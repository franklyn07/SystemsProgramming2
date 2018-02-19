#include <stdio.h>
//library used to include 65 bit integer
#include <stdint.h>
#include <pthread.h>

//global counter - all 10 threads will be updating this global counter
int64_t counter = 0;

//check number of times there is output - supposed value is 100*10
int checker = 0;

//my thread function
void *increment(){
	for(int i =	0;	i <	100000;	i++)	{
		counter++;
		if	(counter	%	1000	==	0)	{
			printf("another	1000\n");
			checker++;
		}
	}
	pthread_exit(NULL);
}

int main(void){
	int returnVal;

	pthread_t myThread[10];

	//generating 10 threads
	for (int i = 0; i < 10; ++i){
		//creating the thread
		returnVal = pthread_create(&myThread[i], NULL, increment, NULL);

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

	printf("Checker: %d\n",checker );

	return 0;
}