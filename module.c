#include "prod_con.h"




/*
 * void *producer(void *indata)
 *
 * This function accepts a void pointer to a struct as the input. The struct 
 *      is recast as type t_data before and work is done on it. 
 *      After waiting some random time, a random integer is generated and the 
 *      semaphores and mutex are checked respectively. Once the data structure
 *      is locked, the random number payload is written into the next 
 *      available cell in the data structure. The counter is updated and the
 *      locks and semphores are released.
 *
 * Input:
 *    indata: a pointer to a void data type. This is a requirement of pthreads.
 *          once inside the function the input is recast as type t_data.
 *
 * Output:
 *    none (should return a int to indicate success or failure)
 *    currently prints each addition to the screen for testing purposes
 *
 * Modifies:
 *    The buffer[] array of the struct is filled with random numbers.
 *    
 * Assumptions:
 *    buffer[] has already been allocated.
 *    That the cells of buffer[] have been zeroed and any current values in 
 *      data are of no concern.
 *
 * Note:
 *  Because this function is intended to be called as several dozen threads, the exact
 *      order of it's behavior is not guarenteed.
 *
 *
 */
void *producer(void *indata)
{
    t_data *data = indata;
    
    while(data->pro_ticker > 0)
    {
        // int rand_variable = 1;
        // int divisor = rand_variable % 5;
        // int divisor_1 = pow(1000, divisor + 1);
        // sleep(random()/1000000000 * divisor_1);
        // rand_variable++;
        sleep(random()/100000000000);
        int payload = random();                      //produce item
        if (data->counter == MAX_SIZE)
        {
            sem_wait(&data->empty);    
        }                
        pthread_mutex_lock(&data->mutex);             //lock the mutex
        data->buffer[data->tail] = payload;
        printf("%15d was written to the data structure at x time.\n", payload);
        //printf("\tProducer tail = %d", data->tail);
        //printf("\tCounter = %d\n", data->counter);
        //printf("pro Ticker = %d\n", data->pro_ticker);
        data->tail = (data->tail + 1) % MAX_SIZE;
        data->counter++;
        data->pro_ticker--;
        pthread_mutex_unlock(&data->mutex);             //unlock mutex
        sem_post(&data->full);
    }
    return NULL;
}









/*
 * void consumer(void *indata)
 *
 * This function accepts a void pointer to a struct as the input. The struct 
 *      is recast as type t_data before and work is done on it. 
 *      After waiting some random time, the semaphores and mutex are checked 
 *      respectively. Once the data structure is locked, the value in the current
 *      cell (if it isn't 0, indicating nothing has been written) is removed and
 *      a NULL character is written into the cell. The counter is updated and the
 *      locks and semphores are released.
 *
 * Input:
 *    indata: a pointer to a void data type. This is a requirement of pthreads.
 *          once inside the function the input is recast as type t_data.
 *
 * Output:
 *    none (should return a int to indicate success or failure)
 *    prints each removal to the screen for testing purposes
 *
 * Modifies:
 *    The buffer[] array of the struct is filled with NULL values.
 *    
 * Assumptions:
 *   buffer[] has already been allocated.
 *    That the cells of buffer[] are cleared to be zeroed and any current values in 
 *      data are of no concern.
 *
 * Note:
 *  Because this function is intended to be called as several dozen threads, the exact
 *      order of it's behavior is not guarenteed.
 *
 */
void *consumer(void *indata) 
{
    t_data *data = indata;
    while(data->con_ticker > 0)
    {
        // int rand_variable = 1;
        // int divisor = rand_variable % 5;
        // int divisor_1 = pow(1000, divisor + 1);
        // sleep(random()/1000000000 * divisor_1);
        // rand_variable++;
        sleep(random()/100000000000);
        if(data->counter == 0) 
        {
            sem_wait(&data->empty);
        }
        pthread_mutex_lock(&data->mutex);
        int temp = data->buffer[data->head];
        if (temp != 0)
        {
            data->buffer[data->head] = NULL;
            printf("%15d was removed from the data structure at x time.\n", temp /*, time_stamp.tv_nsec*/);
            //printf("\tConsumer head = %d", data->head);
            //printf("\tCounter = %d\n", data->counter);
            data->head = (data->head + 1) % MAX_SIZE;
            data->counter--;
            data->con_ticker--;
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
   


//             long j = i % size;
//             if (data[j] == 0)

//             *full = (*full) - 1;
//             i--;






/*!!!!!Current Legacy Function from eary testing!!!!!
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
 */
void print_array(int data[], int size)
{
    int i = 0;
    for (i=0; i < size; i++)
    {
        printf("|%d|", data[i]);
    }
    printf("\n\n");
}



