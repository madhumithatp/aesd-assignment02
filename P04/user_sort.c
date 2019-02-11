/*
 *
 *@File user_sort.c
 *@Brief The C Code for sort syscall
 *
 *This file calls syscall customsort from user space
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

	printf("\nProgram in the User Space \n");
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
	
	/* Printing Input and Sorted Buffers before syscall */
	/*printf("\n------------DATA LOG BEFORE SORTING-------------- \n");
	printf("\nINPUT ARRAY :");
	for ( int i=0; i<BUFFER_SIZE; i++ )
	{
		printf("[%d] ");
	
	}
	printf("\n SORTED ARRAY :");
	for ( int i=0; i<BUFFER_SIZE; i++ )
	{
		printf("[%d]");
	}
	printf("\nBUFFER SIZE : %d /n",BUFFER_SIZE);
	printf("-------------------------------------------------- \n");
	*/
	int BufferLength = BUFFER_SIZE;
	/* Successful execution of Syscall customsort */
	printf("\nTEST CASE 01 : SUCCESSFULL SYSCALL EXECUTION \n");
	//gettimeofday(tvs,NULL);
	//printf("\n Execution started at [%d : %d] \n", tvs.tv_sec,tvs.tv_usec);
        syscall_ret = syscall( SYSCALL_CUSTOMSORT,ptr_inBuffer,BufferLength,ptr_sortBuffer );
	//gettimeofday(tvs,NULL);
	//printf(" \nExecution completed at [%d : %d] \n", tvs.tv_sec,tvs.tv_usec);
	if( syscall_ret==0 )
	{
		printf("\nSystemcall customsort executed successfully \n");
		printf("\nSORTED ARRAY \n");
		for ( int i=0; i<BUFFER_SIZE; i++ )
			printf(" [%d]", *(ptr_sortBuffer+i) );
		printf("\nKernel Log \n");
		system("dmesg | tail -7");
	}
	else
	{
		printf("\nSystemcall customsort failed \nError [%d] %s",syscall_ret,strerror(syscall_ret));
		printf("\nKernel Log \n");
		system("dmesg | tail -7");
	}


	/* Unsuccessful execution of Syscall customsort : NULL Buffer Pointer*/
	printf("\nTEST CASE 02 : UNSUCCESSFULL SYSCALL EXECUTION - NULL INPUT POINTER \n");
	//gettimeofday(tvs,NULL);
	//printf("\n Execution started at [%d : %d] \n", tvs.tv_sec,tvs.tv_usec);
        syscall_ret = syscall( SYSCALL_CUSTOMSORT,NULL,BufferLength,ptr_sortBuffer );
	//gettimeofday(tvs,NULL);
	//printf(" \nExecution completed at [%d : %d] \n", tvs.tv_sec,tvs.tv_usec);

	if( syscall_ret==0 )
	{
		printf("\nSystemcall customsort executed successfully \n");
		printf("\nSORTED ARRAY \n");
		for ( int i=0; i<BUFFER_SIZE; i++ )
			printf(" [%d] \n", *(ptr_sortBuffer+i) );
		printf("\nKernel Log \n");
		system("dmesg | tail -7");
	}
	else
	{
		printf("\nSystemcall customsort failed, Error [%d] %s",syscall_ret,strerror(syscall_ret));
		printf("\nKernel Log \n");
		system("dmesg | tail -7");
	}


	
	/* Unsuccessful execution of Syscall customsort : Invalid Length*/
	printf("\nTEST CASE 03 : UNSUCCESSFULL SYSCALL EXECUTION - INVALID BUFFER LENGTH \n");
	//gettimeofday(tvs,NULL);
	//printf("\n Execution started at [%d : %d] \n", tvs.tv_sec,tvs.tv_usec);
        syscall_ret = syscall( SYSCALL_CUSTOMSORT,ptr_inBuffer,10,ptr_sortBuffer );
	//gettimeofday(tvs,NULL);
	//printf(" \nExecution completed at [%d : %d] \n", tvs.tv_sec,tvs.tv_usec);

	if( syscall_ret==0 )
	{
		printf("\nSystemcall customsort executed successfully \n");
		printf("\nSORTED ARRAY \n");
		for ( int i=0; i<BUFFER_SIZE; i++ )
			printf(" [%d] \n", *(ptr_sortBuffer+i) );
		printf("\nKernel Log \n");
		system("dmesg | tail -7");
	}
	else
	{
		printf("\nSystemcall customsort failed Error [%d] %s",syscall_ret,strerror(syscall_ret));
		printf("\nKernel Log \n");
		system("dmesg | tail -7");
	}


	/* Unsuccessful execution of Syscall customsort : NULL Output Buffer Pointerv*/
	printf("\nTEST CASE 04 : UNSUCCESSFULL SYSCALL EXECUTION - NULL OUTPUT POINTER \n");
	//gettimeofday(tvs,NULL);
	//rintf(" \nExecution started at [%d : %d] \n", tvs.tv_sec,tvs.tv_usec);
        syscall_ret = syscall( SYSCALL_CUSTOMSORT,ptr_inBuffer,BufferLength,NULL );
	//gettimeofday(tvs,NULL);
	//printf(" \nExecution completed at [%d : %d] \n", tvs.tv_sec,tvs.tv_usec);

	if( syscall_ret==0 )
	{
		printf("\nSystemcall customsort executed successfully \n");
		printf("\nSORTED ARRAY \n");
		for ( int i=0; i<BUFFER_SIZE; i++ )
			printf(" [%d] \n", *(ptr_sortBuffer+i) );
		printf("\nKernel Log \n");
		system("dmesg | tail -7");
	}
	else
	{
		printf("\nSystemcall customsort failed Error [%d] %s",syscall_ret,strerror(syscall_ret));
		printf("\nKernel Log \n");
		system("dmesg | tail -7");
	}
	
	return 0;
}
