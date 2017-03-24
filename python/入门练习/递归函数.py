def fact (n) :
	return fact_item (n, 1)

def fact_item (num, product) :
	if num == 1 :
		return product
	return fact_item (num - 1, num * product)

print (fact (5))
