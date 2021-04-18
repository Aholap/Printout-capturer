#include <stdio.h>
#include "output_capture.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "thread_funcs.h"
#include <sys/prctl.h>
#include <signal.h>
#define BUFFER_MAX 1024
#define READ_BYTES 512
pthread_mutex_t lock;



	
void *child_main()
{
	
	char read_buffer[BUFFER_MAX];
	//Structs for both threads
	struct Read toFile;
	struct Read toStream;
	toFile.count = 0;
	toStream.count = 0;
	pthread_t id1,id2;
	//Start threads
	int t1 = pthread_create(&id1, NULL,thread_write, &toFile);
	int t2 = pthread_create(&id2, NULL, thread_print, &toStream);
	if(t1 != 0){
	  printf("Error %d with thread writing to file.", t1);
	}
	if(t2 != 0){
	  printf("Error %d with thread printing to console", t2);
	}

	int a;	

	close(fd[1]);
	//reads from pipe
	while((a = read(fd[0], read_buffer,READ_BYTES))>0){

		pthread_mutex_lock(&lock); 

		if((toFile.count + a) <= BUFFER_MAX){
			memcpy(toFile.buf + toFile.count, read_buffer, a); 
		
		}
		else{
			a = BUFFER_MAX- (toFile.count + a); 
			memcpy(toFile.buf + toFile.count, read_buffer, a);

		}



		memcpy(toStream.buf + toStream.count, read_buffer, a);
		toFile.count = toFile.count + a; 
		toStream.count = toStream.count + a;
		pthread_mutex_unlock(&lock);

		


	}
	close(fd[0]);
	exit(0);	
}





void capture_stdout(char *filename)
{
	//file descriptor
	file_name = filename;
	//pipe
	pipe(fd);
	pid_t pid = fork();
	if(pid == -1){
		printf("Error with pipe");
	}
	if(pid == 0)
	{
		close(fd[1]);
	
		child_main();

	}
	else
	{
		close(fd[0]);
		//Direct stddout to pipe
		dup2(fd[1], 1);
		sleep(1);
	}



}
