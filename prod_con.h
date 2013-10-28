#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <unistd.h>

#define TRUE 1
#define MAX_SIZE 100000000          //The buffer size didn't appear to change the program behavior once it got above 100.
#define TICKER 2000000              //must be much bigger than thread count otherwise each thread only runs once.

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
    int pro_ticker;
    int con_ticker;
    int counter;
    int tail;
    int head;
    int buffer[MAX_SIZE];
} t_data;


void print_array(int data[], int size);
void *producer(void *indata);
void *consumer(void *indata);
struct timeval time_stamp(struct timeval start, struct timeval current);