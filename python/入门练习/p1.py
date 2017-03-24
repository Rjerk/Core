#!/usr/bin/env python3

import math

def quadratic (a, b, c):
	if not isinstance (a, (int, float)):
		raise TypeError ('Bad operand type')
	if not isinstance (b, (int, float)):
		raise TypeError ('Bad operand type')
	if not isinstance (c, (int, float)):
		raise TypeError ('Bad operand type')
	if b*b - 4*a*c > 0 :
		x = (-b + math.sqrt(b*b - 4*a*c))/(2*a)
		
		x1 = (-b - math.sqrt(b*b - 4*a*c))/(2*a)
		return x1,x
	else:
		return 0

print (quadratic (2, 3, 1))

print (quadratic (1, 3, -4))

print (quadratic ('a', 3, 1))
