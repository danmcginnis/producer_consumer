#include "prod_con.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
         printf("Proper usage: \npc number of producer threads  number of consumer threads\n");
         exit(1);
    } 
    int num_pro_threads = atoi(argv[1]);
    int num_con_threads = atoi(argv[2]);

    if ((num_pro_threads < 2) || (num_pro_threads > 1024))
    {
        printf("Please enter a reasonable number of producer threads\n");
        exit(1);
    }

    if ((num_con_threads < 2) || (num_con_threads > 1024))
    {
        printf("Please enter a reasonable number of consumer threads\n");
        exit(1);
    }
    
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

    static t_data lab_3 = {.tail = MAX_SIZE-1, .head = 0, .counter = 0};
    
    gettimeofday(&start, NULL);
    pthread_mutex_init (&lab_3.mutex, NULL);
    sem_init(&lab_3.empty, 0, MAX_SIZE);
    sem_init(&lab_3.full, 0, 0);

    memset(lab_3.buffer, 0, MAX_SIZE);           //to zero out array initially

    srandom(time(NULL));
   
    pthread_t pro_threads[num_pro_threads];
    pthread_t con_threads[num_con_threads];

    int i = 0;

    for (i = 0; i < num_con_threads; i++)
    {
        pthread_create(&con_threads[i], NULL, consumer, &lab_3);
    }

    for (i = 0; i < num_pro_threads; i++)
    {
        pthread_create(&pro_threads[i], NULL, producer, &lab_3);
        
    }

    /* The large buffer size combined with a large number of threads makes visual inspection
    *   of the output difficult. The following section exist to gracefully shut down the program
    *   if functionality to wind down the threads is added. Currently CTRL-C is used to terminate.
    */

    (void) sleep(1);
    
    for (i = 0; i < num_pro_threads; i++) 
    {
        pthread_join(pro_threads[i], NULL);
    }

    for (i = 0; i < num_con_threads; i++) 
    {
        pthread_join(con_threads[i], NULL);
    }

    fprintf(human_log_file, "All %d threads have returned.\n", (num_pro_threads + num_con_threads));
    time_t clk = time(NULL);
    fprintf(human_log_file, "Log File closed at %s\n", ctime(&clk));
    fprintf(human_log_file, "##---------------------------------------------------------------------##\n");
    fclose(human_log_file);
    fclose(log_file);
    pthread_mutex_destroy(&lab_3.mutex);
    return 0;
}