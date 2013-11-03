#include "prod_con.h"

/* int mod (int a, int b)
 *
 * This function provides modular operations for C. Because the C standard
 *  defines the % operator as the remainder function, calling for a negative
 *  number mod a positive number will result in a negative result.
 *  i.e. -1 % 10 returns -9
 * This function checks the output and if it is negative will add the mod value
 *  to the result. mod(-1, 10) returns 9.
 * This function is very heavily based on the following post on Stack Overflow:
 * http://stackoverflow.com/a/4003287/738842
 *
 * Input:
 *      Two integers
 *
 * Output:
 *      a positive integer representing a modulo b
 *
 * Modifies:
 *      none
 *
 * Assumptions:
 *      b is a positive integer
 *
 */
int mod (int a, int b)
{
   int ret = a % b;
   if(ret < 0)
   {
     ret += b;
   }
   return ret;
}





/* struct timeval time_stamp(struct timeval start, struct timeval current)
 * 
 * This function takes two microsecond values and returns the difference. The
 *  function takes into account that the value may "roll over" before the
 *  difference is calculated. This function is based very heavily on the 
 *  following post on Stack Overflow: http://stackoverflow.com/a/10487325/738842
 *
 * Input:
 *      Two timeval structs.
 *
 * Output:
 *      A timeval struct representing the difference between the two input
 *          in microseconds [one millionth of a second].
 *
 * Modifies:
 *      none
 *
 * Assumptions:
 *      There is valid data in both input variables.
 *      The time gap being calculated is of a size that is reasonably
 *          represented in microseconds [ i.e. less an several minutes].
*/
struct timeval time_stamp(struct timeval start, struct timeval current)
{
    struct timeval temp;
    temp.tv_usec = current.tv_usec + (1000000 - start.tv_usec);
    while(temp.tv_usec > 1000000)
    {
        temp.tv_usec -= 1000000;
    }
    return temp;
}




/* void *producer(void *indata)
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
 *    writes output to logfiles
 *
 * Modifies:
 *    The buffer[] array of the struct is filled with random numbers.
 *    
 * Assumptions:
 *    buffer[] has already been allocated.
 *    That the cells of buffer[] have been zeroed.
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
    
    while(TRUE)
    {
        Sleep(random()/1000000000);                             //generates a Sleep from 0 to 21
        int payload = random();                                 //produce item
        if (data->counter == MAX_SIZE)
        {
            sem_wait(&data->empty);
            fprintf(human_log_file, "\n\nCounter is at MAX_SIZE. Waiting...\n\n");    
        }  
        pthread_mutex_lock(&data->mutex);             
        

        if (data->buffer[data->tail] == 0)
        {
            if(!(data->buffer[data->tail] = payload))
            {
                fprintf(human_log_file, "Error writing to buffer!\n");
                pthread_mutex_unlock(&data->mutex);             
                sem_post(&data->full);
                return NULL;
            }

            GetSystemTime(&current);
            temp_time = start - current;
            fprintf(log_file, "%d\n", payload);
            fprintf(human_log_file, "%13d was written to the data structure at %d microseconds.\n", payload, temp_time);
            fprintf(human_log_file, "\tProducer tail = %d", data->tail);
            fprintf(human_log_file, "\tCounter = %d\n", data->counter);
            data->counter++;
        }

        else
        {
            fprintf(human_log_file, "An written but not read cell was encountered. Logging, unlocking, and continuing.\n");
            fprintf(human_log_file, "\tProducer tail = %d", data->tail);
            fprintf(human_log_file, "\tbuffer value = %d\n", data->buffer[data->tail]);
        }
        data->tail = mod((data->tail - 1),  MAX_SIZE);
        pthread_mutex_unlock(&data->mutex);            
        sem_post(&data->full);
    }
    return NULL;
}




/* void consumer(void *indata)
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
 *    writes output to logfiles
 *
 * Modifies:
 *    The buffer[] array of the struct is filled with random numbers.
 *    
 * Assumptions:
 *    buffer[] has already been allocated.
 *    That the cells of buffer[] have been zeroed.
 *
 * Note:
 *  Because this function is intended to be called as several dozen threads, the exact
 *      order of it's behavior is not guarenteed.
 *
 */
void *consumer(void *indata) 
{
    t_data *data = indata;
    while(TRUE)
    {

        int temp = 0;
        Sleep(random()/1000000000);                      //generates a Sleep from 0 to 21
        if(data->counter == 0) 
        {
            sem_wait(&data->empty);
            fprintf(human_log_file, "\n\nCounter is at ZERO. Waiting...\n\n"); 
        }
        pthread_mutex_lock(&data->mutex);

        temp = data->buffer[data->head];
        
        if (temp == 0)
        {
            fprintf(human_log_file, "An empty cell was encountered. Logging, unlocking, and continuing.\n");
            fprintf(human_log_file, "\t Consumer head = %d", data->head);
            fprintf(human_log_file, "\tbuffer value = %d\n", data->buffer[data->head]);
            
        }
        else 
        {
            data->buffer[data->head] = 0;
            GetSystemTime(&current);
            temp_time = start - current;
            fprintf(log_file, "%d\n", temp);
            fprintf(human_log_file, "%13d was removed from the data structure at %d microseconds.\n", temp, temp_time);
            fprintf(human_log_file, "\tConsumer head = %d", data->head);
            fprintf(human_log_file, "\tCounter = %d\n", data->counter);
            data->counter--;
        }
        
        data->head = mod((data->head + 1), MAX_SIZE);
        pthread_mutex_unlock(&data->mutex);
        sem_post(&data->full);
    }
    return NULL;
}