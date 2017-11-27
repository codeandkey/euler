#!/bin/python
# this one was gonna be a lot simpler in python

a = 1
b = 1
c = 3
cur = 0

def is_pan(s):
	if (int(s) < 123456789):
		return False
	if (int(s) > 987654321):
		return False
	s = set(s)
	if ('0' in s):
		return False
	if (len(s) < 9):
		return False
	return True

while True:
	if (c % 100000 == 0):
		print("passed c=" + str(c), flush=True)
	if (c % 2):
		a += b
		cur = a
	else:
		b += a
		cur = b
	if (is_pan(str(cur % 1000000000))):
		if (is_pan(str(cur)[:9])):
			print("passed second stage: n = " + str(c))
			quit()
	c += 1
