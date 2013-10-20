#include "prod_con.h"

int main(int argc, char *argv[])
{

    /*if (argc < 2)
    {
        printf("Proper usage: \n");
        printf("pc x y with x being the number of threads to run and y being the size of the array\n");
        return 0;
    } */
    
    

    thread_data test; // = (t_data*)malloc (sizeof(t_data));
    test.size = 0;


    int NUM = atoi(argv[1]);
    //int temp = atoi(argv[1]);
    pthread_t threads[NUM];
    int i = 0;
    //int *full = &temp;      //this hack sucks. There has to be a better way.
    //int size = temp;

    sem_t sem1;
    

    sem_init(&sem1, 0, 0);

    srandom(time(NULL));    //random is preferred over rand

    for (i; i < NUM; i++)
    {
        test.counter = i;
        pthread_create(&threads[i], NULL, thread_f, &test);   
    }

    
    (void) sleep(1);

    print_array(test.data, MAX_SIZE);
   
    
    return 0;
}
