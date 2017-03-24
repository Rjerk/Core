#/usr/bin/env python

from sys import argv

script,test,test2=argv

input = open(test)

indata = input.read()

output = open(test2,"w")

output.write(indata)

print "\nCopying...Done!This is test2:\n"

output=open(test2)

print output.read()


