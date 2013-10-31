CIS 3207 Lab 3 -- Producer / Consumer
====================================
Dan McGinnis -- October 29, 2013
---------------------------------

The goal of this lab is to have multiple producer threads and consumer threads working off a single circular array. Access to the array is to be controlled through semaphores and mutex locks.

To run the file:
		
		make
		./pc x y 
		python3 test_harness.py log_file

where `x` and `y` are the number of producer and consumer threads to be created respectively.

The program takes two integers as input. The first is the number of producer threads. The second is the number of consumer threads. The program checks these input values to make sure they are reasonable. Currently that range is set from 2 to 1024. If the numbers are outside of that range, the program notifies the user and exits right away. I have set the buffer size to be 1000 cells long, so it is important to keep in mind that with very low numbers for producer of consumer, it will take a while for the threads to meet near the middle of the array.

The consumer thread starts at the beginning of the array and works upward. The consumer starts at the back of the array and works down. Sempahores are used to prevent the consumer from reading if there isn't any data and the producer from inserting if there isn't any room in the array. A mutex is used to protect the actual read or write to the array and the update of the counter variable. All the data associated with this program and the sempahores and mutex are stored in a struct. This struct is initialized in the main function and passed to each of the threads. Because the threads require that a void data type be passed in the struct is recast in the producer and consumer functions.

I have included functionality to wait for the threads to exit. After this occurs the files are safely closed and the mutex is destroyed before the program is terminated. Currently the flow of the program never reaches this code, because there is no mechanism to safely wind down the threads. I attempted to implement this in a way that ensured the producers and consumers did equal work without turning the program into a serial operation, but was unable to do so correctly. Because this functionality is not called for in the lab spec, I have removed the code that attempted to do this.


Testing
-------

I tested this program in several ways. The first route I persued was manual testing of the output. I initally had all the output that now goes to the log writing to the screen. I lowered the size of the buffer and increased the time delay so that it was reasonable to observe the operation of the program as it ran. Once I was satisified that it was working properly, I reverted the program to writing into the human log file and ran it for larger numbers of threads. I read through the log file to makes sure that the program appeared to be working properly. Additionally, while I was attempting to implement the wind down function to gracefully end the program, I observed the thread count displayed by running the `top` program on a second terminal. Finally, I implemented the previously mentioned python based test harness. This allowed me to run the program with a much bigger buffer and larger producer and consumer threads and still make sure that the reads and writes were happening as expected. I tested this program on both 64bit OS X 10.8 and a 32bit vm running the latest long term release of Ubuntu. Testing on the Ubuntu VM showed a limitation of roughly 381 threads per process. Other testing on a 64 bit version of OS X showed the program to be function with a thread count several orders of magnitude greater. The program produces two log files in the current directory, one called human log file and the other called log file. The human log file contains all of the relevant data and displays it in a friendly format.  The other log file just contains the values written and read to the buffer. Becaue the human log file is meant for human consumption it is opened in append mode. Since that would interfere with the programtic testing, the log file is opened in write mode and overwritten every time the program is run. The number 0, which represents an empty buffer is not recorded when read. The purpose of this second file is to allow a programatic inspection of the programs output. I have included a python 3 program called test harness.py. This program will run through the log file and count the number of times each number is seen. Ideally each number would be seen twice, once for a write and once for a read. The program actually tests for a multiple of 2 to allow for the fact that the payload is a randomly generated number and could occur more than once. However, because the program runs until terminated, there is not a way to safely wind down the program and guarentee that the producer and consumer threads have done equal work. As a result, the test_harness will report a success if less that 1% of the numbers found are unique.The test harness will print out a message indicating success or failure. In the test harness file, there are additional print statements that could be uncommented to provide more feedback that could be compared to the human log file for further debugging. Because I belive the program to be functioning properly, this output is silenced for now.


Program details
---------------

The `prod_con.h` file

* Lists all the included files
* Defines the global variables needed
* Defines the struct that holds all the relevant program data
* Lists the headers of all the programs functions.


The `main.c` file

* Checks user input for a reasonable number of threads
* Opens the log files or terminates the program upon failure to open files.
* Populates the struct with data for the program to begin running
* Initiates the timer, the random number generator, the semaphore, and the mutex
* Fires off the producer and consumer threads and waits


The `module.c` file

* Contains the code for the four functions needed for the program to function. Documentation from the functions themselves is included below.

 	int mod (int a, int b)
----------------------
 	*
 	* This function provides modular operations for C. Because the C standard
 	*  defines the % operator as the remainder function, calling for a negative
 	*  number mod a positive number will result in a negative result.
 	*  i.e. -1 % 10 returns -9
 	* This function checks the output and if it is negative will add the mod value
 	*  to the result. mod(-1, 10) returns 9.
 	* This function is very heavily based on the following post on Stack Overflow:
 	* [http://stackoverflow.com/a/4003287/738842]
 	*
 	* Input:
 	*      Two integers
 	*
 	* Output:
 	*      a positive integer representing a modulo b
 	*
 	* Modifies:
 	*      none
 	*
 	* Assumptions:
 	*      b is a positive integer
 	*
 	*/


 	struct timeval time_stamp(struct timeval start, struct timeval current)
-----------------------
 	* 
 	* This function takes two microsecond values and returns the difference. The
 	*  function takes into account that the value may "roll over" before the
 	*  difference is calculated. This function is based very heavily on the 
 	*  following post on Stack Overflow: http://stackoverflow.com/a/10487325/738842
 	*
 	* Input:
 	*      Two timeval structs.
 	*
 	* Output:
 	*      A timeval struct representing the difference between the two input
 	*          in microseconds [one millionth of a second].
 	*
 	* Modifies:
 	*      none
 	*
 	* Assumptions:
 	*      There is valid data in both input variables.
 	*      The time gap being calculated is of a size that is reasonably
  	*          represented in microseconds [ i.e. less an several minutes].
 	*/


 	void *producer(void *indata)
-------------

 	* This function accepts a void pointer to a struct as the input. The struct 
 	*      is recast as type t_data before and work is done on it. 
 	*      After waiting some random time, a random integer is generated and the 
 	*      semaphores and mutex are checked respectively. Once the data structure
 	*      is locked, the random number payload is written into the next 
 	*      available cell in the data structure. The counter is updated and the
 	*      locks and semphores are released.
 	*
 	* Input:
 	*    indata: a pointer to a void data type. This is a requirement of pthreads.
 	*          once inside the function the input is recast as type t_data.
 	*
 	* Output:
 	*    writes output to logfiles
 	*
 	* Modifies:
 	*    The buffer[] array of the struct is filled with random numbers.
 	*    
 	* Assumptions:
 	*    buffer[] has already been allocated.
 	*    That the cells of buffer[] have been zeroed.
 	*
 	* Note:
 	*  Because this function is intended to be called as several dozen threads, the exact
 	*      order of it's behavior is not guarenteed.
 	*
 	*
 	*/


 	void consumer(void *indata)
----------------

 	* This function accepts a void pointer to a struct as the input. The struct 
 	*      is recast as type t_data before and work is done on it. 
 	*      After waiting some random time, the semaphores and mutex are checked 
 	*      respectively. Once the data structure is locked, the value in the current
 	*      cell (if it isn't 0, indicating nothing has been written) is removed and
 	*      a NULL character is written into the cell. The counter is updated and the
 	*      locks and semphores are released.
 	*
 	* Input:
 	*    indata: a pointer to a void data type. This is a requirement of pthreads.
 	*          once inside the function the input is recast as type t_data.
 	*
 	* Output:
 	*    writes output to logfiles
 	*
 	* Modifies:
 	*    The buffer[] array of the struct is filled with random numbers.
 	*    
 	* Assumptions:
 	*    buffer[] has already been allocated.
 	*    That the cells of buffer[] have been zeroed.
 	*
 	* Note:
 	*  Because this function is intended to be called as several dozen threads, the exact
 	*      order of it's behavior is not guarenteed.
 	*
 	*/