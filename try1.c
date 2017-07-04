#include	<stdio.h>
#include	<pthread.h>
#include	<errno.h>
#include	<string.h>
#include	<unistd.h>
#include	<time.h>
#include	<sys/time.h>
#include	<stdlib.h>
#include	<semaphore.h>
#include 	<locale.h>
#include	<signal.h>
#include	"function.h"
#include	"MinHeap.h"
#include	"MinHeap.c"

pthread_t 		pit1;
pthread_t 		pit2;
pthread_t 		pit3;
pthread_mutex_t lock;
MinHeap			minHeap;
sem_t 			sem_name;
//void updating(char *REQUEST,char *now1);
static void
printHeap( MinHeap * minHeap )
{
	unsigned int	i, limit;
	char	*x;

	limit = minHeap->elemcount;
	printf( "[ " );
	for ( i = 0 ; i < limit ; i++ )
	{
		x = (char *)(minHeap->block + i * sizeof(char *));
		printf( "%s ", x );
	}
	printf( "]\n" );
}


static int
intCompare( const void * p1, const void * p2 )
{
	const char *		p01 = p1;
	const char *		p02 = p2;

	return strcmp(p01,p02);
}

void *ReaderT(void *now1)					//Thread 1 - Reader
{
	char *now;	
	char timestamp[100];				   	//user timestamp
	char activity[100];						//user activity
	now = (char *)now1;
	while(1)
	{
		printf("--->Enter Timestamp\n");
		scanf("%s",timestamp);	
		char REQUEST[100];
		check(timestamp,now);
		printf("--->Enter activity to be performed at that time:\n");			//Entering Name of the activity
		scanf("%s",activity);
		sprintf(REQUEST,"%s %s",timestamp,activity);
		printf("--->Request of '%s' at '%s' added to the memory\n",activity,timestamp);
		pthread_mutex_lock(&lock);
		addElement( &minHeap, REQUEST );						//Adding element to the MinHeap
		pthread_mutex_unlock(&lock);
		remainingtime(REQUEST,now);
		//pthread_mutex_unlock(&lock);
	}			
}

void *WorkerT(void *now1)				//Thread 2 - Worker
{
int i = 0;
char *now;
now = (char *)now1;
int REQUEST1;
char *x;
	while(1)
	{		
		sleep(1);	
			pthread_mutex_lock(&lock);
			if ( removeMin1( &minHeap, &REQUEST1 ) == 0 ){}
				//printf( "No Requests yet\n" );
			
			else{
				x = (char *)getMin(&minHeap);
//				pthread_mutex_lock(&lock);
				updating(x,now);
//				pthread_mutex_unlock(&lock);			
			}	
			 pthread_mutex_unlock(&lock);

	}
}

void *ClockT(void *now1)				//Thread 3 - Clock
{
	char *now;
	now = (char *)now1;
	while(1)
	{
		sleep(1);
		pthread_mutex_lock(&lock);
		updatetime(now);
		pthread_mutex_unlock(&lock);
	}
}

int main(int argc, char ** argv )
{
	char 		*now;
	int 		year,month,hour,min,sec;
	now = strdup(argv[1]);
	//strcpy(now,argv[1]);		

	if ( argc > 2) 							//GREATER THAN 2 ARGUMENTS
		{
			fprintf(stderr,"\x1b[1;31mMust specify only 2 argument\nExiting........\x1b[0m\n");
			_exit( 1 );	
		}
	else if (sscanf(now,"%d/%d/%d/%d/%d",&year,&month,&hour,&min,&sec) != 5  || year < 1000 || year > 9999 || month < 0 || 
											month > 365 || hour < 0 || hour > 23 ||min < 0 || min > 59 ||sec < 0 || sec > 59 ) 	//Error - If enter more than 5 numbers still give correct answer	//CHECKING IF THE ARGUMENT IS CORRECT OR NOT
		{ 	
			fprintf(stderr,"\x1b[1;31mMust specify correct timestamp format\nExiting........\x1b[0m\n");
			exit(1);	
		}
	else															//IF WORKING CORRECTLY THEN
		{
			pthread_mutex_init(&lock,NULL);							//Initializing Mutex
			
			sem_init(&sem_name,1,0);								//Initializing Semaphore
			initializeMinHeap( &minHeap, intCompare, 64); 			//Initialzing MinHeap
			pthread_create(&pit1, NULL, ReaderT,now );				//Initializing Thread 1 - Reader
			pthread_create(&pit2, NULL, WorkerT,now);				//Initializing Thread 2 - Worker
			pthread_create(&pit3, NULL, ClockT, now);				//Initializing Thread 3 - Clock	
			pthread_exit(0);										//Exiting Threads
		}
	return 0;
}

