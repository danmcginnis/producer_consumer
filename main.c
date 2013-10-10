#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_SIZE 32

void print_array(int data[], int size);
void produce(int data[], int size);
void consume(int data[], int size);

int main(void)
{
    int data[MAX_SIZE];
    srandom(time(NULL));    //random is preferred over rand
    int i = 0;
    for (i = 0; i < 5; i++)
    {
    produce(data, MAX_SIZE);
    print_array(data, MAX_SIZE);
    printf("\n\n");
    consume(data, MAX_SIZE);
    print_array(data, MAX_SIZE);
    printf("\n---------------\n");
    }
    return 0;
}

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
 *
 * Modifies:
 *    The data[] array is filled with random numbers.
 *    
 * Assumptions:
 *    data[] has already been allocated.
 *    size accuratley represents the size of data.
 *    The current values in data are of no concern.
 *
 */
void produce(int data[], int size)
{

    int i = 0;

        for (i = MAX_SIZE-1; i > -1; i--)
        {

            int j = random();
            j = j % size;
            data[j] = random();
            printf("Cell %d was just updated with %d\n", j, data[j]);
        }
}


/*
 * void consume(int data[], int size)
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
 *
 * Modifies:
 *    The data[] array is filled with NULLs.
 *    
 * Assumptions:
 *    data[] has already been allocated.
 *    size accuratley represents the size of data.
 *    The current values in data are of no concern.
 *
 */
void consume(int data[], int size)
{

    int i = 0;

        for (i = 0; i < MAX_SIZE; i++)
        {

            data[i] = NULL;
        }
}



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
 */
void print_array(int data[], int size)
{
    int i = 0;
    for (i=0; i < size; i++)
    {
        printf("|%d|", data[i]);
    }
}
