#ifndef OUTPUT_CAPTURE_H_
#define OUTPUT_CAPTURE_H_
#include <pthread.h>
int fd[2];
char *file_name;

struct Read {
	int count;
	char buf[1024];
	

};

void *child_main();
void capture_stdout(char *filename);

#endif // OUTPUT_CAPTURE_H_
