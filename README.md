producer_consumer
=================

Lab 3 for Operating Systems

The goal of this lab is to have multiple producer threads and consumer threads working off a single array. Access to the array is to be controlled through semaphores and mutex locks.

Testing was done on a 32 bit version of Ubuntu running in a VM. This created a limitation of roughly 381 threads per process. Other testing on a 64 bit version of OS x showed the program to be function with a thread count several orders of magnitude greater.

To run the file:
		
		make
		./pc x

where `x` is the number of elements to be stored in the array.

Current testing:

	pc 200 | cut -c 1-12 > temp; test_framework.py temp



