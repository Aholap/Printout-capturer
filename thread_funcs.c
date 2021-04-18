#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "thread_funcs.h"
#include <pthread.h>
#include "output_capture.h"

#define BUFFER_MAX 1024

char *file_name;  
pthread_mutex_t lock;  

//Thread for writing into logfile
void *thread_write(void *arg)
{
   	FILE *txtfile;
    struct Read *reads = (struct Read*)arg;
	char *buf = reads->buf;
	char data[BUFFER_MAX+1];
	//Check if file exists --> write/append
	if(access(file_name, F_OK) != -1)
	{
		txtfile = fopen(file_name, "a");  
	}
	else
	{
		txtfile = fopen(file_name, "w");
	}

	while(1)
	{
		if(reads->count > 0)
		{

			pthread_mutex_lock(&lock);
	
			int len = reads->count;
			if(len > BUFFER_MAX){
				memcpy(data, buf, BUFFER_MAX); 
					
			}
			else{
				memcpy(data, buf, reads->count);  
			}
			reads->count = 0;
			pthread_mutex_unlock(&lock);
			data[len] = 0;
			fprintf(txtfile, "%s",data);
			fflush(txtfile);

		}
	}	
	fclose(txtfile);	
}





//Thread for writing to console
void *thread_print(void *arg)
{
    struct Read *reads = (struct Read*)arg;
    char *buf = reads->buf;
    char data[BUFFER_MAX+1];
		while(1){
		    if(reads->count > 0)
		    {  
		      pthread_mutex_lock(&lock);
		      memcpy(data, buf, reads->count);
		      int len = reads->count;
			if(len > BUFFER_MAX){
		  		memcpy(data, buf, BUFFER_MAX); 		
			}
			else{
				memcpy(data, buf, reads->count);  
			}
			
		      reads->count = 0;
		      pthread_mutex_unlock(&lock);
		      fflush(stderr);
		      fprintf(stderr, "%s", data);
		      fflush(stderr);
		    }
		}


}

