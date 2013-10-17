#!/usr/bin/python3

# ubuntu python path^^

#the path on Mac OS X is /usr/local/bin/python3
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
dup_limit = 2
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
            print(value, "has been found", payload[value], "times.")
    else:
        print(value, '=>', payload[value])
        uni += 1

print()
print(sp, "unique sets of numbers were entered.")
print(wc, "lines were encountered")


if uni > 0:
    print("Test Failure! ---> ",  uni, " unique numbers were encountered.")
else:
    print("Test Success!")

exit(0)