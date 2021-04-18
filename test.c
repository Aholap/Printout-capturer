#include <stdio.h>
#include "output_capture.h"
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

void *thread_func(){
		printf("Printed by a thread\n");
	}

char *main(){

	
	capture_stdout("testaustiedosto");
	//printf("%s", argv[0]);
	char a;
	printf("kljlk\n");
	//sleep(1);
	int p = fork();
	if(p == 0){
		printf("This ws printed by a child process\n");
	} else {
		pthread_t one,two;
		pthread_create(&one, NULL, thread_func, NULL);
		pthread_create(&two, NULL, thread_func, NULL);
		
		
	}
	
	
	
	sleep(1);
	printf("This including everything else printed should be written in 'testaustiedosto'!\n");
	sleep(3);
	
	exit(0);	
}
