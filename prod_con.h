#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>


pthread_mutex_t mutex;

typedef struct
{
    int size;
    int counter;
} thread_data;


void print_array(int data[], int size);
void *thread_f(void* test);
void produce(long data[], long size, long *full, int id);
void consume(long data[], long size, long *full, int id);


