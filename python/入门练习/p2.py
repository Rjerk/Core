#!/usr/bin/env python3


def power (x, n):
	i = n
	sum = 1
	while i > 0:
		sum *= x 
		i -= 1
	return sum

print (power (2,3))

print (power (2,10))
