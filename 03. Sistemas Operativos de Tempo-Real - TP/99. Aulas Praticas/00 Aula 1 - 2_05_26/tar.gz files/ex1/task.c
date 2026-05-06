
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NSEC_PER_SEC		1000000000L

void do_work(unsigned long long exec)
{	
	unsigned long long i,ten_ns;
	ten_ns=exec/10;
	for(i=0; i<ten_ns; i++){
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
//32	
	
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		
//64
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 
		asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); asm volatile  ("nop" ::); 

	}
}
int main(int argc, char** argv) 
{
	struct timespec t;
	unsigned long long C, T, O, time0, release;
	unsigned int task_id,njobs,i=0;
	if(argc != 6){
		printf("Error: arguments\n\n");
		exit(EXIT_FAILURE);
	}
	
	task_id=atoi(argv[1]);
	njobs=atoi(argv[2]);
	C=(unsigned long long)atoll(argv[3]);
	T=(unsigned long long)atoll(argv[4]);
	O=(unsigned long long)atoll(argv[5]);
	
	clock_gettime(CLOCK_MONOTONIC, &t);
	time0 = t.tv_sec * NSEC_PER_SEC;
	time0 += t.tv_nsec;
	
	release = time0 + O;	
	for(i=0;i<njobs;i++){
		t.tv_sec = release / NSEC_PER_SEC;
		t.tv_nsec = release % NSEC_PER_SEC;
		printf("Task(%d,%d,%d): sleeping until %lld\n",task_id,getpid(),i,release);
		clock_nanosleep(CLOCK_MONOTONIC,TIMER_ABSTIME, &t,NULL);
		printf("Task(%d,%d,%d): ready for execution\n",task_id,getpid(),i);
		do_work(C); 
		//computes the next release
		release += T;
		
	}
	printf("Task(%d,%d): finishing\n",task_id,getpid());
	exit(task_id);
	return 0;
}
	
	
	

	
	
	
	

