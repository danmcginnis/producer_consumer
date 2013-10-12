#include "prod_con.h"


int main(int argc, char *argv[])
{
    
    if (argc < 2)
    {
    	printf("Please enter the size of the array\n");
    	exit(1);
    }
    
    int temp = atoi(argv[1]);
    int *full = &temp;      //this hack sucks. There has to be a better way.
    int size = temp;
    
    printf("Size: %d\tFull: %d\n", size, *full);
    int data[size];
    srandom(time(NULL));    //random is preferred over rand
   
	produce(data, size, full);
    printf("Size: %d\tFull: %d\n", size, *full);
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
void produce(int data[], int size, int *full)
{
    int i = size;
    int j = 0;
    while (*full > 0)
    {
            j = i % size;
            data[j] = random();
            i--;
            *full = (*full) - 1;
            printf("Cell %d was just updated with %d\n", j, data[j]);
     } 
}
