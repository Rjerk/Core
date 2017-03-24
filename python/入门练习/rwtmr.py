#/usr/bin/env python

from sys import argv

script,test,test2=argv

words_in_test = open(test,"w")

words_in_test.truncate()

some_words = raw_input("\nSomething I want to say:\n")

words_in_test.write(some_words)

words_in_test=open(test)

indata = words_in_test.read()

output = open(test2,"w")

output.write(indata)

print "\nCopying to test2.txt ... \n\ntest2.txt:\n"

output = open(test2)

print output.read()


