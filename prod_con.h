#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define TRUE 1
#define MAX_SIZE 10000



typedef struct Thread_data
{
    sem_t sem_empty;
    sem_t sem_full;
    pthread_mutex_t mutex;
    int size;
    int counter;
    int full_counter;
    int empty;
    int full;
    int time_delay;
    long buffer[MAX_SIZE];
} t_data;


void print_array(int data[], int size);
void *producer(void *indata);
void *consumer(void *indata);

//int clock_gettime(clockid_t clk_id, struct timespect *tp); //per http://www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/


