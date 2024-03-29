#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <unistd.h>

#define TRUE 1
#define MAX_SIZE 1000  

#ifndef bool
    #define bool int
    #define false ((bool)0)
    #define true  ((bool)1)
#endif

FILE *human_log_file;
FILE *log_file;

struct timeval start;
struct timeval current;
struct timeval temp_time;

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
int mod (int a, int b);
struct timeval time_stamp(struct timeval start, struct timeval current);