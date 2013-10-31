producer consumer
=================

Lab 3 for Operating Systems

The goal of this lab is to have multiple producer threads and consumer threads working off a single array. Access to the array is to be controlled through semaphores and mutex locks.

Testing was done on a 32 bit version of Ubuntu running in a VM. This created a limitation of roughly 381 threads per process. Other testing on a 64 bit version of OS X showed the program to be function with a thread count several orders of magnitude greater.

To run the file:
		
		make
		./pc x y 
		python3 test_harness.py log_file

where `x` and `y` are the number of producer and consumer threads to be created respectively.


 

I tested this program on both 64bit OS X 10.8 and a 32bit vm running the latest long term release of Ubuntu. The program produces two log files in the current directory, one called human log file and the other called log file. The human log file contains all of the relevant data and displays it in a friendly format.  The other log file just contains the values written and read to the buffer. 0, which represents an empty buffer is not recorded when read. The purpose of this second file is to allow a programattic inspection of the programs output. I have included a python 3 program called test harness.py. This program will run through the log file and count the number of times each number is seen. Ideally each number would be seen twice, once for a write and once for a read. The program actually tests for a multiple of 2 to allow for the fact that the payload is a randomly generated number and could occur more than once. However, because the program runs until terminated, there is not a way to safely wind down the program and guarentee that the producer and consumer threads have done equal work. As a result, the test_harness will report a success if less that 1% of the numbers found are unique.The test harness will print out a message indicating success or failure. In the test harness file, there are additional print statements that could be uncommented to provide more feedback that could be compared to the human log file for further debugging. Because I belive the program to be functioning properly, this output is silenced for now.

The program takes two integers as input. The first is the number of producer threads. The second is the number of consumer threads. The program checks these input values to make sure they are reasonable. Currently that range is set from 2 to 1024. If the numbers are outside of that range, the program notifies the user and exits right away. I have set the buffer size to be 1000 cells long, so it is important to keep in mind that with very low numbers for producer of consumer, it will take a while for the threads to meet near the middle of the array.

The consumer thread starts at the beginning of the array and works upward. The consumer starts at the back of the array and works down. Sempahores are used to prevent the consumer from reading if there isn't any data and the producer from inserting if there isn't any room in the array. A mutex is used to protect the actual read or write to the array and the update of the counter variable. All the data associated with this program and the sempahores and mutex are stored in a struct. This struct is initialized in the main function and passed to each of the threads. Because the threads require that a void data type be passed in the struct is recast in the producer and consumer functions.

I have included functionality to wait for the threads to exit. After this occurs the files are safely closed and the mutex is destroyed before the program is terminated. Currently the flow of the program never reaches this code, because there is no mechanism to safely wind down the threads. I attempted to implement this in a way that ensured the producers and consumers did equal work without turning the program into a serial operation, but was unable to do so correctly. Because this functionality is not called for in the lab spec, I have removed the code that attempted to do this.







