#!/usr/bin/env python

from sys import argv

script , test = argv

my_file = open(test)


print "\nHere is your file:%r\n " %test

print my_file.read()

 
