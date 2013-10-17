#include "prod_con.h"

 sem_t sem1;

 void *thread_f(void *par)
    {
        int id = (int) par;
        long temp = 5000;
        long *full = &temp;      //this hack sucks. There has to be a better way.
        long size = temp;
        

        //go to sleep
        sem_wait(&sem1);

        //printf("Thread %d starting to work!\n", id);
        long data[size];
        memset(data, 0, size);
        //this seems like a hack, make it better
       
        produce(data, size, full, id);
        consume(data, size, full, id);
        return NULL;
    }

int main(int argc, char *argv[])
{

    /*if (argc < 2)
    {
        printf("Proper usage: \n");
        printf("pc x y with x being the number of threads to run and y being the size of the array\n");
        return 0;
    } */
    int NUM = atoi(argv[1]);
    //int temp = atoi(argv[1]);
    pthread_t threads[NUM];
    int i;
    //int *full = &temp;      //this hack sucks. There has to be a better way.
    //int size = temp;


    sem_init(&sem1, 0, 0);

    srandom(time(NULL));    //random is preferred over rand

    for (i = 0; i < NUM; i++)
    {
        pthread_create(&threads[i], NULL, thread_f, (void *)i);
        
    }

    //printf("Everyone wait...\n");

    sleep(1);
    //printf("Now Go!\n");

    //wake threads
    for(i = 0;i < NUM; i++)
    {
        sem_post(&sem1);
    }
        //give some time to the threads
        sleep(1);
        //printf("Main is quitting.\n");
    return 0;
}
