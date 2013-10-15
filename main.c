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
    
    int data[size];
    memset(data, 0, size);
    //this seems like a hack, make it better
    srandom(time(NULL));    //random is preferred over rand
	produce(data, size, full);
    consume(data, size, full);
    return 0;
}
