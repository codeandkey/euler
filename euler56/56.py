_max = 0

for a in range(100):
	for b in range(100):
		c = str(pow(a, b))
		s = 0
		for i in c:
			s += int(i)
		if (s > _max):
			_max = s

print("_max = " + str(_max))
