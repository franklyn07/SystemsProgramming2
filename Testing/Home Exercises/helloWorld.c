#include <stdio.h>
#include <pthread.h>

//my thread function
void *hello(){
	printf("Hello World!\n");
	pthread_exit(NULL);
}

int main(void){
	int returnVal;

	pthread_t myThread;

	//creating the thread
	returnVal = pthread_create(&myThread, NULL, hello, NULL);

	//check if some error occurred
	if(returnVal == 0){
		printf("No Error Occurred.\n");
	}else{
		printf("Warning! Error!\n");
	}

	//this waits for the threads to finish before continuouing execution in main thread
	pthread_join(myThread, NULL);

	return 0;
}