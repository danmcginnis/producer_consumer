#include "prod_con.h"

int main(int argc, char *argv[])
{
    
	static t_data lab_3;
	int num_pro_threads;
	int num_con_threads;
	int i;
	time_t clk;
	HANDLE pro_threads[200];
    HANDLE con_threads[200];
	
	if (argc < 3)
    {
         printf("Proper usage: \npc number of producer threads  number of consumer threads\n");
         exit(1);
    } 
    
	num_pro_threads = atoi(argv[1]);
    num_con_threads = atoi(argv[2]);

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

   
	lab_3.tail = MAX_SIZE-1;
	lab_3.head = 0;
	lab_3.counter = 0;
    
    GetSystemTime(&start);
    lab_3.mutex = CreateMutex(NULL, false, NULL);
    lab_3.empty = CreateSemaphore(NULL, 0, MAX_SIZE, NULL);
    lab_3.full = CreateSemaphore(NULL, 0, 0, NULL);

    memset(lab_3.buffer, 0, MAX_SIZE);           //to zero out array initially

    srand((unsigned)time(NULL));                       
   
    

   

    for (i = 0; i < num_con_threads; i++)
    {
        unsigned thread_id;
		con_threads[i] = (HANDLE)_beginthreadex(NULL, 0, consumer, &lab_3, 0, &thread_id);
    }

    for (i = 0; i < num_pro_threads; i++)
    {
        unsigned thread_id;
		pro_threads[i] = (HANDLE)_beginthreadex(NULL, 0, producer, &lab_3, 0, &thread_id);
    }

    /* The large buffer size combined with a large number of threads makes visual inspection
    *   of the output difficult. The following section exist to gracefully shut down the program
    *   if functionality to wind down the threads is added. Currently CTRL-C is used to terminate.
    */

    (void) Sleep(1);
    
    for (i = 0; i < num_pro_threads; i++) 
    {
        WaitForSingleObject(pro_threads[i], NULL);
    }

    for (i = 0; i < num_con_threads; i++) 
    {
        WaitForSingleObject(con_threads[i], NULL);
    }

    fprintf(human_log_file, "All %d threads have returned.\n", (num_pro_threads + num_con_threads));
    clk = time(NULL);
    fprintf(human_log_file, "Log File closed at %s\n", ctime(&clk));
    fprintf(human_log_file, "##---------------------------------------------------------------------##\n");
    fclose(human_log_file);
    fclose(log_file);
    CloseHandle(&lab_3.mutex);
    return 0;
}