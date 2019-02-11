/*
 *
 *@File crontabfile.c
 *@Brief Code for crontab
 *
 *@Author Madhumitha Tolakanahalli Pradeep
 *@Date 6 Febraury 2019
 *
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>


#define SYSCALL_CUSTOMSORT 398
#define BUFFER_SIZE 256
#define SEED 10
#define NUM_LIMIT 100

struct timeval tvs;

int main()
{
	long syscall_ret = 0;
	 printf("Process ID: %d\n", (int)getpid());
	printf("User ID :   %d\n", (int)getuid());
	printf("\nProgram in the User Space \n");
	system("date");
	srand(SEED);

	/* Dynamically allocate buffers for input and sorted array */
	int32_t * ptr_inBuffer = (int32_t *)malloc(sizeof(int32_t)*BUFFER_SIZE);
	int32_t * ptr_sortBuffer = (int32_t *)malloc(sizeof(int32_t)*BUFFER_SIZE);	
	
	/* Check for validity of pointers */
	if( ptr_inBuffer==NULL || ptr_sortBuffer==NULL )
	{
		printf(" \nMalloc unsuccessful /n Exiting program \n");
		return -1;
	}
	
	/* Initialize Output Buffer */
	for( int i=0; i<BUFFER_SIZE; i++)
	{
		*(ptr_sortBuffer+i) = 0;
	}

	/* Generate random numbers and initialize Input Buffer */
	for( int i=0; i<BUFFER_SIZE; i++)
	{
		*(ptr_inBuffer+i) = rand()%BUFFER_SIZE;
	}
	
	
	int BufferLength = BUFFER_SIZE;
	/* Successful execution of Syscall customsort */
        syscall_ret = syscall( SYSCALL_CUSTOMSORT,ptr_inBuffer,BufferLength,ptr_sortBuffer );
	if( syscall_ret==0 )
	{
		printf("\nSystemcall customsort executed successfully \n");
		printf("\nSORTED ARRAY \n");
		for ( int i=0; i<BUFFER_SIZE; i++ )
			printf(" [%d]", *(ptr_sortBuffer+i) );
	}
	else
	{
		printf("\nSystemcall customsort failed \nError [%d] %s",syscall_ret,strerror(syscall_ret));
		
	}

	return 0;
}
