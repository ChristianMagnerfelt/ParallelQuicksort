/*	description: quicksort using recursive parallism in pthreads
	
	author: Christian Magnerfelt
	
	email: magnerf@kth.se
   
	features:
             
	usage under Linux:
		
	building the executable:
	
*/
#ifndef _REENTRANT 
#define _REENTRANT 
#endif

#define DEBUG

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

#define MAX_SIZE 100000
#define MAX_WORKERS 10

int g_maxSize = MAX_SIZE;
const int g_sortCutoff = 1000000;

int g_arrayData[MAX_SIZE];

pthread_t workers[MAX_WORKERS];

double startTime;
double finalTime;

void generate(int * start, int * end);
bool isSorted();
int compare(const void * a, const void * b);
void parallel_quicksort(int * start, int n, int size);
void printArray(int * start, int * end);
double readTimer();

int main(int argc, const char * argv [])
{
	/* Generate test data */
	generate(&g_arrayData[0], &g_arrayData[g_maxSize]);
	
	/* Initialize timer and set start time */
	startTime = readTimer();
	
	/* Start the recursive parallel quick sort */
	parallel_quicksort(&g_arrayData[0], g_maxSize, sizeof(int));

	/* Set end time */
	finalTime = readTimer() - startTime;
	
	/* Check if the array is sorted */
	if(isSorted(&g_arrayData[0], &g_arrayData[g_maxSize]))
	{
		printf("Array is sorted\n");
	}
	else
	{
		printf("Array is not sorted\n");
	}
	
	printf("The execution time is %g sec\n", finalTime);
	
	/* Print array */
	#ifdef DEBUG
	printArray(&g_arrayData[0], &g_arrayData[g_maxSize]);
	#endif
	
	return 0;
}
void generate(int * start, int * end)
{
	if(start == end)
		return;
	while(start != end)
	{
		*start = rand() % 100;
		start++;
	}
}
bool isSorted(int * start, int * end)
{
	start++;
	if(start == end)
		return true;
	while(start != end)
	{
		if(*(start - 1) > *(start))
			return false;
		start++;  
	}
	return true;
}
int compare(const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}
void parallel_quicksort(int * start, int n, int size)
{
	if(n < g_sortCutoff)
	{
		qsort(start, n, sizeof(int), compare);
	}
	
}
void printArray(int * start, int * end)
{
	if(start == end)
		return;
	while(start != end)
	{
		printf("%d ", *start);
		start++;
	}
	printf("\n");
}
double readTimer()
{
	static bool initialized = false;
	static struct timeval start;
	struct timeval end;
	if( !initialized )
	{
		gettimeofday( &start, NULL );
		initialized = true;
	}
	gettimeofday( &end, NULL );
	return (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
}
