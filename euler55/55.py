count = 0

for i in range(10000):
	cur = i
	is_lyc = 1
	for _ in range(49):
		cur += int(str(cur)[::-1])
		if (str(cur) == str(cur)[::-1]):
			is_lyc = 0
			break
	if is_lyc:
		count += 1
		print("pass: " + str(i))

print("count = " + str(count))
