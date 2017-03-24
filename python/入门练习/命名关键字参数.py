
def person (name, age, **kw) :
	if 'city' in kw :
		# city pere
		pass
	if 'job' in kw :
		# job exist
		pass
	print ('name:', name, 'age:', age, 'other:', kw)


print (person( 'jack', 24, city = 'Beijing', addr = 'Chaoyang', zipcode = 12))
