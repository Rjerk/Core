#/usr/bin/env python

from sys import argv

script, test = argv

my_file = open(test, "w")

my_file.truncate(0)

print "Please input something in the test.txt!"

line1 = raw_input("The line1:")
line2 = raw_input("The line2:")

my_file.write(line1)
my_file.write("\n")
my_file.write(line2)


my_file = open(test)

print my_file.read()


