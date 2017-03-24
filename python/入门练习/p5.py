def calc (*numbers):
	sum = 0
	for n in numbers :
		sum = sum + n*n
	return sum

L = [1,2,3,4,5]
print (calc(1, 2, 3))

print (calc(L[1], L[2], L[3]))

print (calc(*L))
