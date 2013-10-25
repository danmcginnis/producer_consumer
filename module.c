#include "prod_con.h"


void *producer(void *indata)
{
    t_data *data = indata;
    
    while(TRUE)
    {
        sleep(random()/1000000000);
        long payload = random();                      //produce item
        sem_wait(&data->sem_empty);                  
        pthread_mutex_lock(&data->mutex);             //lock the mutex
        if(data->counter < MAX_SIZE) 
        {
            data->buffer[data->counter] = payload;
            data->counter++;
            //printf("%d\n", data->counter);
            //printf("Payload delivered = %lu\n", payload);
            printf("%15lu was written to the data structure at x time.\n", payload);
        }
        pthread_mutex_unlock(&data->mutex);             //unlock mutex
        sem_post(&data->sem_full);
    }
    return NULL;
}

void *consumer(void *indata) 
{
    t_data *data = indata;

    while(TRUE)
    {
        sleep(random()/10000000000);
        sem_wait(&data->full);
        pthread_mutex_lock(&data->mutex);
        if(data->counter > 0) 
        {
            if (data->buffer[data->counter] != 0)
            {
                long temp = data->buffer[data->counter];
                data->buffer[data->counter] = NULL;
                data->counter--;
                //printf("%d\n", data->counter);
                //printf("Payload removed = %lu\n", temp);
                printf("%15lu was removed from the data structure at x time.\n", temp);
            }
            else
            {
                data->counter--;
                //printf("%d\n", data->counter);
            }
        }
        pthread_mutex_unlock(&data->mutex);
        sem_post(&data->full);
    }
    return NULL;
}


        
        // t_data* foo = (t_data*)test; /* Cast the void* to our struct type */
       
        
        // /*long temp = 5;
        // long *full = &temp;      //this hack sucks. There has to be a better way.
        // long size = temp;
   

/*
 * void produce(int data[], int size)
 *
 * This function accepts an array of integers and 
 *    the size of the array as input. Starting at 
 *    the back of the array cells are filled in
 *    with randomly generated numbers.
 *
 * Input:
 *    int data[]: an array of type integer
 *    int size: an integer specifying the size of the
 *        array.
 *
 * Output:
 *    none (should return a int to indicate success or failure)
 *    prints each addition to the screen for testing purposes
 *
 * Modifies:
 *    The data[] array is filled with random numbers.
 *    
 * Assumptions:
 *    data[] has already been allocated.
 *    size accuratley represents the size of data.
 *    The current values in data are of no concern.
 *
 *
void produce(long data[], long size, long *full, int id)
{
    long i = size;
     
    while (*full > 0)
    {
            long j = i % size;
            if (data[j] == 0)
            {
                
            }
            *full = (*full) - 1;
            i--;
            
            //need to figure out a way to dynamically figure out
            //cell padding based on input
     } 
}
*/

/*
 * void consume(int data[], int size, int *full)
 *
 * This function accepts an array of integers and 
 *    the size of the array as input. Starting at 
 *    the front of the array cells are filled in
 *    with NULLs.
 *
 * Input:
 *    int data[]: an array of type integer
 *    int size: an integer specifying the size of the
 *        array.
 *
 * Output:
 *    none (should return a int to indicate success or failure)
 *    prints each removal to the screen for testing purposes
 *
 * Modifies:
 *    The data[] array is filled with NULLs.
 *    
 * Assumptions:
 *    data[] has already been allocated.
 *    size accuratley represents the size of data.
 *    The current values in data are of no concern.
 *
 *
void consume(long data[], long size, long *full, int id)
{

    long i = 0;

        for (i = 0; i < size; i++)
        {

            
        }
}
*/



/*
 * void print_array(int data[], int size)
 *
 * This function accepts an array of integers and 
 *    the size of the array as input. Starting at 
 *    the front of the array cells are printed to
 *    the screen.
 *
 * Input:
 *    int data[]: an array of type integer
 *    int size: an integer specifying the size of the
 *        array.
 *
 * Output:
 *    The array's content is printed to the screen.
 *
 * Modifies:
 *    none.
 *
 * Assumptions:
 *    data[] has already been allocated.
 *    size accuratley represents the size of data.
 *
 *
void print_array(int data[], int size)
{
    int i = 0;
    for (i=0; i < size; i++)
    {
        printf("|%d|", data[i]);
    }
    printf("\n\n");
}
*/


