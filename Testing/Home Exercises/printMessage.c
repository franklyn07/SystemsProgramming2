#include <stdio.h>
#include <pthread.h>

//my thread function
void *printMess(void * message){
	printf("From inside the created thread: %s\n", (char *)message);
	pthread_exit(NULL);
}

int main(void){
	int returnVal;

	pthread_t myThread;

	//array storing message
	char mess[20];

	//getting message
	printf("Enter input: \n");
	fgets(mess, 20, stdin);

	//creating the thread
	returnVal = pthread_create(&myThread, NULL, printMess, (void *) mess);

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