producer_consumer
=================

Lab 3 for Operating Systems

The goal of this lab is to have multiple producer threads and consumer threads working off a single array. Access to the array is to be controlled through semaphores and mutex locks.

To run the file:
		
		make
		./pc x

where `x` is the number of elements to be stored in the array.

Current testing:

	pc 200 | cut -c 1-16 > temp
	test_framework.py temp



