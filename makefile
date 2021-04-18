

default: all

all: example_prog
	
example_prog: output_capture.c thread_funcs.c test.c
	gcc -c thread_funcs.c -o thread_funcs.o; gcc -c output_capture.c -o output_capture.o; gcc -c test.c -o test.o;
	
	gcc test.o output_capture.o thread_funcs.o -o example_prog -pthread
clean:
	rm test.o thread_funcs.o output_capture.o
