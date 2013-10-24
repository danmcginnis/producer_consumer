#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_SIZE 20

pthread_mutex_t mutex;
pthread_mutex_t mutex1;

typedef struct Thread_data
{
    int size;
    int counter;
    int data[MAX_SIZE];
} t_data;


void print_array(int data[], int size);
void *thread_f(void* test);
void produce(long data[], long size, long *full, int id);
void consume(long data[], long size, long *full, int id);


