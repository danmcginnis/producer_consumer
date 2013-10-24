#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_SIZE 20




typedef struct Thread_data
{
    sem_t empty;
    sem_t full;
    pthread_mutex_t mutex;
    int size;
    int head, tail;
    int data[MAX_SIZE];
} t_data;


void print_array(int data[], int size);
void *thread_f(void* data);
void produce(t_data *data);
void consume(t_data *data);


