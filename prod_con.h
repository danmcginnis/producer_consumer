#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define TRUE 1
#define MAX_SIZE 10000



typedef struct t_data
{
    pthread_mutex_t mutex;
    sem_t empty;
    sem_t full;
    int counter;
    int tail;
    int head;
    int buffer[MAX_SIZE];
} t_data;


void print_array(int data[], int size);
void *producer(void *indata);
void *consumer(void *indata);

//int clock_gettime(clockid_t clk_id, struct timespect *tp); //per http://www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/


