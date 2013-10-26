#include "prod_con.h"

#define NUM 2560
#define THREAD_COUNT 2


int main(int argc, char *argv[])
{

    // if (argc < 4)
    // {
    //     printf("Proper usage: \n");
    //     printf("pc "number of producer threads" " number of consumer threads" "delay between threads"\n");
    //     return 0;
    // } 
    // int num_pro_threads = atoi(argv[1]);
    // int num_con_threads = atoi(argv[2]);
    // int Time_delay = atoi(argv[3]);

    static t_data test = {.tail = 0, .head = 0, .counter = 0};
    pthread_mutex_init (&test.mutex, NULL);
    sem_init(&test.empty, 0, MAX_SIZE);
    sem_init(&test.full, 0, 0);

    memset(test.buffer, 0, MAX_SIZE);  //to zero out array initially

    srandom(time(NULL));    //random is preferred over rand
   
    pthread_t pro_threads[NUM];
    pthread_t con_threads[NUM];

    int i = 0;
    for (i; i < NUM; i++)
    {
        pthread_create(&pro_threads[i], NULL, producer, &test);
        pthread_create(&con_threads[i], NULL, consumer, &test);
    }

    
    /* The following section will not be used unless I figure out a graceful way to wind down the threads.
    *    The solutions that come to mind would require stopping the threads individually and the result
    *    would be that one would be unable to tell if the test passes because the "threads" can finish the 
    *    work without any competition
    */

    (void) sleep(1);
    i = 0;
    for (i; i < NUM; i++) 
    {
        pthread_join(pro_threads[i], NULL);
        pthread_join(con_threads[i], NULL);
    }
    
    pthread_mutex_destroy(&test.mutex);
    return 0;
}