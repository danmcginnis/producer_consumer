#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <process.h>
#include <malloc.h>  

#define TRUE 1
#define MAX_SIZE 1000  

#ifndef bool
    #define bool int
    #define false ((bool)0)
    #define true  ((bool)1)
#endif

FILE *human_log_file;
FILE *log_file;

SYSTEMTIME start;
SYSTEMTIME current;
SYSTEMTIME temp_time;

typedef struct t_data
{ 
    HANDLE mutex;
    HANDLE empty;
    HANDLE full;
    int counter;
    int tail;
    int head;
    int buffer[MAX_SIZE];
} t_data;


void print_array(int data[], int size);
unsigned __stdcall producer(void *indata);
unsigned __stdcall consumer(void *indata);
int mod (int a, int b);
struct timeval time_stamp(struct timeval start, struct timeval current);