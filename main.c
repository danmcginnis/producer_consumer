#include "prod_con.h"

#define NUM 4096
#define THREAD_COUNT 2
#define TICKER 2000000              //must be much bigger than thread count otherwise each thread only runs once.






int main(int argc, char *argv[])
{

    // if (argc < 3)
    // {
    //     printf("Proper usage: \npc "number of producer threads" " number of consumer threads"\n");
    //     return 0;
    // } 
    // int num_pro_threads = atoi(argv[1]);
    // int num_con_threads = atoi(argv[2]);

    
    
    //clock_gettime(CLOCK_REALTIME,&start);

    if ((log_file = fopen("log_file", "w")) == NULL)
    {
        printf("Cannot open log file!");
        exit(1);
    }

    if ((human_log_file = fopen("human_log_file", "a+")) == NULL)
    {
        printf("Cannot open log file!");
        exit(1);
    }

    static t_data lab_3 = {.tail = 0, .head = 0, .counter = 0, .pro_ticker = TICKER, .con_ticker = TICKER};
    gettimeofday(&start, NULL);
    pthread_mutex_init (&lab_3.mutex, NULL);
    sem_init(&lab_3.empty, 0, MAX_SIZE);
    sem_init(&lab_3.full, 0, 0);

    memset(lab_3.buffer, 0, MAX_SIZE);           //to zero out array initially

    srandom(time(NULL));                        //random is preferred over rand
   
    pthread_t pro_threads[NUM];
    pthread_t con_threads[NUM];

    int i = 0;
    for (i = 0; i < NUM; i++)
    {
        pthread_create(&pro_threads[i], NULL, producer, &lab_3);
        pthread_create(&con_threads[i], NULL, consumer, &lab_3);
    }

    
    /* The large buffer size combined with a large number of threads makes visual inspection
    *   of the output difficult. The following section will gracefully shut down the program
    *   to allow the output to be written to a file and inspected programatically.
    */

    (void) sleep(1);
    
    for (i = 0; i < NUM; i++) 
    {
        pthread_join(pro_threads[i], NULL);
        pthread_join(con_threads[i], NULL);
    }
    fprintf(human_log_file, "All %d threads have returned.\n", NUM);
    time_t clk = time(NULL);
    fprintf(human_log_file, "Log File closed at %s\n", ctime(&clk));
    fprintf(human_log_file, "##---------------------------------------------------------------------##\n");
    fclose(human_log_file);
    fclose(log_file);
    pthread_mutex_destroy(&lab_3.mutex);
    return 0;
}