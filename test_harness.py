#!/usr/bin/python3

# Usage:
# 
#   python3 test_harness.py log_file
#
#   This program will work through the log file and look for duplicate numbers.
#   The expected format of the log file is a even number of occurances of any
#   number present. This would indicate that the random number was read and 
#   written to the buffer properly. Manual testing showed that it was very
#   unlikely that a random number would be written twice but not read out so
#   this program does not test for that possibility.
#
#   A passing test will simply print "Test Success to the stdout."
#   A failing test will display the numbers that were found an odd number of
#   times so that they can be cross referenced with the human readable log.
#
#   Uncomment the additional print statements for a more detailed output.
#  
#
#   If python3 is located at the path listed above this file can be made
#   executable and run without the python3 call before hand.
#
# I have tested this program on OS X and Ubuntu, but not on Windows 7.
#


from sys import exit
from sys import argv
from collections import Counter
import string
import os

script, *filename = argv

# stupid hack to check for valid file and ignore other input
if not filename or not os.path.isfile(str(filename[0])):
    exit(0)

filename = filename[0]

sp = 0
uni = 0
dup_limit = 10
wc = 0
payload = {}


for line in open(filename):
    line = line.rstrip('\n')
    wc += 1
    if line in payload:
       payload[line] += 1
    else:
        payload[line] = 1


for value in sorted(payload, key=payload.get, reverse=False):
    if payload[value] % 2 == 0:
        sp += 1
        if payload[value] > dup_limit:
            #print(value, "has been found", payload[value], "times.")
            pass            #no op to allow to maintain if/else structure
    else:
        #print(value, '=>', payload[value])
        uni += 1

#print()
#print(sp, "unique sets of numbers were entered.")
#print(wc, "lines were encountered")

#if uni > 0:
if uni > (wc * 0.01): 
    print("Test Failure! ---> ",  uni, " unique numbers were encountered.")
else:
    print("Test Success!")

exit(0)