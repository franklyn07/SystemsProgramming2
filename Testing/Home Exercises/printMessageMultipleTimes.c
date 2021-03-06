#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

//we are using typedef to give an alias to our struct, which then can be used to refer to our structure

typedef struct thread_data{
	int no_times;
	char mess[20];
}myData;

//my thread function
void *printMess(void * structure){
	//recieving a pointer to struct containing data, type casting it to correct form and storing it in a new ptr
	myData* data = (myData *) structure;
	//use '->' operator to retrieve data from pointer
	for(int i = 0; i < data -> no_times; i++){
		printf("From inside the created thread: %s\n", data -> mess);
	}
	pthread_exit(NULL);
}

int main(void){
	int returnVal;

	pthread_t myThread;

	//array storing message
	char message[20];

	//storing #times to repeat
	int repeat;

	//getting user input
	printf("Enter message: \n");
	fgets(message, 20, stdin);
	printf("Enter number of times to be repeated: \n");
	scanf("%d", &repeat);

	//creating pointer to my structure
	myData * myDataPtr;
	//allocating memory for my struct and giving it values
	//(size of myDataPtr is equal to size of my struct thread_data aka myData), as well as setting them to point to correct
	//allocated address (through malloc) in memory
	myDataPtr = (myData *) malloc(sizeof(myData));
	myDataPtr -> no_times = repeat;
	strcpy(myDataPtr -> mess,message);

	//creating the thread
	returnVal = pthread_create(&myThread, NULL, printMess, (void *) myDataPtr);

	//check if some error occurred
	if(returnVal == 0){
		printf("No Error Occurred.\n");
	}else{
		printf("Warning! Error!\n");
	}

	//this waits for the threads to finish before continuing execution in main thread
	pthread_join(myThread, NULL);

	return 0;
}
