def person (name, age, **kw):
	return ('name:', name, 'age:', age, 'other:', kw)

print (person('David', 45, city = 'Beijing'))
