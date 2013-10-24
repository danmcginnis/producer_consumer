#include "prod_con.h"

#define NUM 2

int main(int argc, char *argv[])
{

    static t_data test = {.size = 1};
    if (&test == NULL)
    {
        printf("Failure to initialize data structure\n");
        exit(1);
    }
    pthread_mutex_init (&test.mutex, NULL);
    sem_init(&test.empty, 0, 0);
    sem_init(&test.full, 0, 0);

    memset(test.data, 0, MAX_SIZE);  //to zero out array initially

    srandom(time(NULL));    //random is preferred over rand
   
    pthread_t threads[NUM];

    producer(&test);
    consumer(&test);

    for (int i = 0; i < NUM; i++)
    {
        pthread_create(&threads[i], NULL, thread_f, &test);
    }

    /*if (argc < 2)
    {
        printf("Proper usage: \n");
        printf("pc x y with x being the number of threads to run and y being the size of the array\n");
        return 0;
    } 
    
    

    
    int NUM = atoi(argv[1]);
    //int temp = atoi(argv[1]);
    
    int i = 0;
    //int *full = &temp;      //this hack sucks. There has to be a better way.
    //int size = temp;

    
    

    

    
    (void) sleep(1);

    print_array(test.data, MAX_SIZE);
   */
    
    return 0;
}
