#include	<stdio.h>
#include	<errno.h>
#include	<string.h>
#include	<unistd.h>
#include	<time.h>
#include	<stdlib.h>
#include	<sys/time.h>
#include	"MinHeap.h"


sem_t 			sem_name;
MinHeap			minHeap;
int oo;
static void
start_timer( int first_quantum, int next_quantum )
{
	struct itimerval		interval;
	interval.it_interval.tv_sec = next_quantum;
	interval.it_interval.tv_usec = 0;		/* microseconds */
	interval.it_value.tv_sec = first_quantum;
	interval.it_value.tv_usec = 0;
	setitimer( ITIMER_REAL, &interval, 0 );
}

static void timeout_handler(int signo,siginfo_t *info,void *p)
{
	char *a;
	int ok;
	int REQUEST;
	fprintf(stderr,"\x1b[1;31m\nSIGNAL****SIGNAL****SIGNAL\x1b[0m\n");
	a = (char *)getMin(&minHeap);
	fprintf(stderr,"\x1b[1;31mRecent activity performed: '%s'\x1b[0m\n",a);
	//removeMin( &minHeap, &ok );
	printf("removed");	
}
static void signal_handler( int signo )
{
	printf( "--Dang.  Cntl-C hit.  signo is %d, exit()ing.\n", signo );
	_exit( 0 );
}
void settimer(int totaltime)
{
	start_timer( totaltime, 0 );
}
void updating(char *REQUEST,char *now1)
{
	char *now;
	int rema;
	now = (char *)now1;
	struct sigaction	action;	action.sa_flags = SA_SIGINFO | SA_RESTART; action.sa_sigaction = timeout_handler; sigemptyset( &action.sa_mask );			// no additional signals blocked //
	sigaction( SIGALRM, &action, 0 ); action.sa_flags = 0; action.sa_handler = signal_handler; sigemptyset( &action.sa_mask );	sigaction( SIGINT, &action, 0 );
	char 		remT[100]; //remaining  time
	int 		year,month,hour,min,sec;
	int 		year1,month1,hour1,min1,sec1;
	int 		year2,month2,hour2,min2,sec2;
if(sscanf(REQUEST,"%d/%d/%d/%d/%d",&year1,&month1,&hour1,&min1,&sec1) == 5 && sscanf(now,"%d/%d/%d/%d/%d",&year2,&month2,&hour2,&min2,&sec2)==5)
					{
						year  	= year1 - year2;	
						month 	= month1-month2;hour 	= hour1 - hour2;min 	= min1 	- min2;sec 	= sec1 	- sec2;		
						sprintf(remT,"%d/%d/%d/%d/%d",year,month,hour,min,sec);
						int totaltime;
						totaltime = 31557600*year + 2592000*month + 86400*hour + 60*min + sec;
						
						if (totaltime < 0)
							{
								//printf("hii");
								removeMin( &minHeap, &oo );
							}
						else 
							{
								
								settimer(totaltime);
								//printf("Time remaining for nearest event to happen: %d seconds\n",totaltime );
							}
						}

}
void remainingtime(char *REQUEST,char *now1)
{
	struct sigaction	action;	action.sa_flags = SA_SIGINFO | SA_RESTART; action.sa_sigaction = timeout_handler; sigemptyset( &action.sa_mask );			// no additional signals blocked //
	sigaction( SIGALRM, &action, 0 ); action.sa_flags = 0; action.sa_handler = signal_handler; sigemptyset( &action.sa_mask );	sigaction( SIGINT, &action, 0 );
	char 		remT[100]; //remaining  time
	int 		ret;
	char 		*TIME1;
	char *now;
	now = (char *)now1;
	int 		year,month,hour,min,sec;
	int 		year1,month1,hour1,min1,sec1;
	int 		year2,month2,hour2,min2,sec2;
	
	//TIME = (char *)getMin(&minHeap);						//Getting the MinHeap
				TIME1 = (char *)getMin(&minHeap);						//Signal2
				//printf("TIME1 = %s\n",TIME1 );
				ret = strcmp(REQUEST,TIME1);
				//printf("Line 56\n------------------");
				if(ret < 0)
				{

					if(sscanf(REQUEST,"%d/%d/%d/%d/%d",&year1,&month1,&hour1,&min1,&sec1) == 5 && sscanf(now,"%d/%d/%d/%d/%d",&year2,&month2,&hour2,&min2,&sec2)==5)
					{
						year  	= year1 - year2;	
						month 	= month1-month2;hour 	= hour1 - hour2;min 	= min1 	- min2;sec 	= sec1 	- sec2;		
						sprintf(remT,"%d/%d/%d/%d/%d",year,month,hour,min,sec);
						int totaltime;
						totaltime = 31557600*year + 2592000*month + 86400*hour + 60*min + sec;
						//printf("Line 655\n------------------");
						if (totaltime < 0)
							{
								printf("Time has already passed. Cannot add to the memory---\n");
							}
						else 
							{
								
								settimer(totaltime);
								printf("Time remaining for nearest event to happen: %d seconds\n",totaltime );
							}

					}	
				//remainingtime(REQUEST,now);
				}
				else
				{
					if(sscanf(TIME1,"%d/%d/%d/%d/%d",&year1,&month1,&hour1,&min1,&sec1) == 5 && sscanf(now,"%d/%d/%d/%d/%d",&year2,&month2,&hour2,&min2,&sec2)==5)
					{
						year  	= year1 - year2;	
						month 	= month1-month2;hour 	= hour1 - hour2;min 	= min1 	- min2;sec 	= sec1 	- sec2;		
						sprintf(remT,"%d/%d/%d/%d/%d",year,month,hour,min,sec);
						int totaltime;
						totaltime = 31557600*year + 2592000*month + 86400*hour + 60*min + sec;
								//		printf("Line 89\n------------------");
						if (totaltime < 0)
							{
								printf("Time has already passed. Cannot add to the memory\n");
							}
						else 
							{
								
								settimer(totaltime);
								printf("Time remaining for nearest event to happen: %d seconds\n",totaltime );
							}
					}	
					//remainingtime(TIME1,now);
				}

	
}
void updatetime(char *now)
{
	int 		year,month,hour,min,sec;
	if (sscanf(now,"%d/%d/%d/%d/%d",&year,&month,&hour,&min,&sec) == 5)
				{

					if(month == 365 && hour == 23 && min == 59 && sec == 59)
					{
						year = year + 1;
						month = 0;
						hour = 0;
						min = 0;
						sec = 0;
						sprintf(now ,"%d/%d/%d/%d/%d",year,month,hour,min,sec );

						
						//printf("%s\n",now );
					//	printf("%d/%d/%d/%d/%d\n", year,month,hour,min,sec);
					}
					else if(min != 59 && sec == 59)
					{
						min = min + 1;
						sec = 0;
						sprintf(now, "%d/%d/%d/%d/%d",year,month,hour,min,sec );
						//printf("%s\n",now );
					//	printf("%d/%d/%d/%d/%d\n", year,month,hour,min,sec);
					}
					else if (month != 365 && hour == 23 && min == 59 && sec == 59)
					{
						month = month + 1;
						hour = 0;
						min = 0;
						sec = 0;
						sprintf(now, "%d/%d/%d/%d/%d",year,month,hour,min,sec );
						//printf("%s\n",now );
					//	printf("%d/%d/%d/%d/%d\n", year,month,hour,min,sec);
					}
					else if (hour != 23 && min == 59 && sec == 59)
					{
						hour = hour + 1;
						min = 0;
						sec = 0;
						sprintf(now, "%d/%d/%d/%d/%d",year,month,hour,min,sec );;
						//printf("%s\n",now );
					//	printf("%d/%d/%d/%d/%d\n", year,month,hour,min,sec);
					}
					else if (sec != 59)
					{
						sec = sec + 1;
						sprintf(now, "%d/%d/%d/%d/%d",year,month,hour,min,sec );
						//printf("%s\n",now );
					//	printf("%d/%d/%d/%d/%d\n", year,month,hour,min,sec);
					}
					else{}					
				}	
}

void check(char *timestamp, char *now)
{
	int 		year,month,hour,min,sec;
	int 		year1,month1,hour1,min1,sec1;
	int 		year2,month2,hour2,min2,sec2;
	char 		remT[100]; 
	if ((sscanf(timestamp,"%d/%d/%d/%d/%d",&year,&month,&hour,&min,&sec) != 5) || year < 1000 || year > 9999 || month < 0 || 
											month > 365 || hour < 0 || hour > 23 ||min < 0 || min > 59 ||sec < 0 || sec > 59 ) 	
	//Error - If enter more than 5 numbers still give correct answer	//CHECKING IF THE ARGUMENT IS CORRECT OR NOT
	{ 	
		fprintf(stderr,"\x1b[1;31mEnter a valid timestamp or type 'quit'\x1b[0m\n");
		scanf("%s",timestamp);
		if(strcmp(timestamp,"quit") == 0){exit(0);}
		check(timestamp,now);
	}

	if(sscanf(timestamp,"%d/%d/%d/%d/%d",&year1,&month1,&hour1,&min1,&sec1) == 5 && sscanf(now,"%d/%d/%d/%d/%d",&year2,&month2,&hour2,&min2,&sec2)==5)
					{
						year  	= year1 - year2;	
						month 	= month1-month2;hour 	= hour1 - hour2;min 	= min1 	- min2;sec 	= sec1 	- sec2;		
						sprintf(remT,"%d/%d/%d/%d/%d",year,month,hour,min,sec);
						int totaltime;
						totaltime = 31557600*year + 2592000*month + 86400*hour + 60*min + sec;
								//		printf("Line 89\n------------------");
						if (totaltime < 0)
							{
								printf("Time has already passed. Cannot add to the memory\n");
								fprintf(stderr,"\x1b[1;31mEnter a valid timestamp or type 'quit'\x1b[0m\n");
								scanf("%s",timestamp);
								if(strcmp(timestamp,"quit") == 0){exit(0);}
								check(timestamp,now);
							}
					}

	if ((sscanf(timestamp,"%d/%d/%d/%d/%d",&year,&month,&hour,&min,&sec) != 5) || year < 1000 || year > 9999 || month < 0 || 
											month > 365 || hour < 0 || hour > 23 ||min < 0 || min > 59 ||sec < 0 || sec > 59 ) 	
	//Error - If enter more than 5 numbers still give correct answer	//CHECKING IF THE ARGUMENT IS CORRECT OR NOT
	{ 	
		fprintf(stderr,"\x1b[1;31mEnter a valid timestamp or type 'quit'\x1b[0m\n");
		scanf("%s",timestamp);
		if(strcmp(timestamp,"quit") == 0){exit(0);}
		check(timestamp,now);
	}
}
