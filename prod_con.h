#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define TRUE 1
#define MAX_SIZE 100



typedef struct Thread_data
{
    sem_t sem_empty;
    sem_t sem_full;
    pthread_mutex_t mutex;
    int size;
    int counter;
    int empty;
    int full;
    int time_delay;
    long buffer[MAX_SIZE];
} t_data;


void print_array(int data[], int size);
void *producer(void *indata);
void *consumer(void *indata);


