#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>


void print_array(int data[], int size);
void produce(long data[], long size, long *full, int id);
void consume(long data[], long size, long *full, int id);


