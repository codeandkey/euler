def is_bouncy(n):
	if (n < 100):
		return False
	s = str(n)
	
	inc = 0
	dec = 0
	for i in range(len(s)-1):
		if (s[i] < s[i+1]):
			inc = 1
		if (s[i] > s[i+1]):
			dec = 1
		if (inc == 1 and dec == 1):
			return True
	return False

cur = 0
count = 0
while True:
	cur += 1
	if is_bouncy(cur):
		count += 1
	if (cur == 538):
		print("ratio for " + str(cur) + ": " + str(count / cur))
	if (cur == 21780):
		print("ratio for " + str(cur) + ": " + str(count / cur))
	if ((count/cur) == 0.99):
		print("reached target ratio at cur = " + str(cur))
