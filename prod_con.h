#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


void print_array(int data[], int size);
void produce(int data[], int size, int *full);
void consume(int data[], int size, int *full);


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
void consume(int data[], int size, int *full)
{

    int i = 0;

        for (i = 0; i < size; i++)
        {

            if (data[i] != 0)
            {
                int temp = data[i];
                data[i] = NULL;
                printf("%16d was removed from cell %5d\n", temp, i);
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


