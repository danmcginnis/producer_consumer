#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>


void print_array(int data[], int size);
void produce(int data[], int size, int *full, int id);
void consume(int data[], int size, int *full, int id);


