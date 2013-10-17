#include "prod_con.h"



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
 *    prints each addition to the screen for testing purposes
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
void produce(long data[], long size, long *full, int id)
{
    long i = size;
    long j = 0;
    while (*full > 0)
    {
            j = i % size;
            if (data[j] == 0)
            {
                data[j] = random();
            }
            *full = (*full) - 1;
            i--;
            printf("%12ld was placed in cell %5ld of array number %d\n",  data[j], j, id);
            //need to figure out a way to dynamically figure out
            //cell padding based on input
     } 
}

/*
 * void consume(int data[], int size, int *full)
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
 *    prints each removal to the screen for testing purposes
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
void consume(long data[], long size, long *full, int id)
{

    long i = 0;

        for (i = 0; i < size; i++)
        {

            if (data[i] != 0)
            {
                long temp = data[i];
                data[i] = NULL;
                printf("%12ld was removed from cell %ld of array number %d\n", temp, i, id);
            }
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
    printf("\n\n");
}

