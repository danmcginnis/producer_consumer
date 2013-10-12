#!/usr/local/bin/python3

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
uni = 0;
payload = {}


for line in open(filename):
        if line in payload:
            payload[line] += 1
        else:
            payload[line] = 1


for value in sorted(payload, key=payload.get, reverse=False):
    if payload[value] % 2 == 0:
        sp += 1
    else:
        print(value, '=>', payload[value])
        uni += 1

print()
print(sp, " pairs of numbers were entered.")
if uni > 0:
    print("Test Failure! ---> ",  uni, " unique numbers were encountered.")
else:
    print("Test Success!")


exit(0)

