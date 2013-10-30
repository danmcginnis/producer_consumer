producer_consumer
=================

Lab 3 for Operating Systems

The goal of this lab is to have multiple producer threads and consumer threads working off a single array. Access to the array is to be controlled through semaphores and mutex locks.

Testing was done on a 32 bit version of Ubuntu running in a VM. This created a limitation of roughly 381 threads per process. Other testing on a 64 bit version of OS X showed the program to be function with a thread count several orders of magnitude greater.

To run the file:
		
		make
		./pc x y 
		python3 test_harness.py log_file

where `x` and `y` are the number of producer and consumer threads to be created respectively.


This program will create two seperate log files in the current directory. The first file is called human_log_file. It contains all the relevant information about the operation of the program. The second is called log file. This file just contains the values written and read to the buffer. 0, which represents an empty buffer is not recorded when read. The purpose of this second file is to allow a programattic inspection of the programs output. I have included a python 3 program called test harness.py. This program will run through the log file and count the number of times each number is seen. Ideally each number would be seen twice, once for a write and once for a read. However, because the program runs until terminated, there is not a way to safely wind down the program and guarentee that the producer and consumer threads have done equal work. As a result, the test_harness will report a success if less that 1% of the numbers found are unique.





