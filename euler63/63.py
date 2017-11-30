#!/bin/python

from math import log10

def digs(n):
	return int(log10(n))+1

def tbase(n, mp):
	count = 0
	for i in range(1, mp+1):
		v = pow(n, i)
		if (digs(v) == i):
			count += 1
			print("pass: " + str(n) + "^" + str(i) + " = " + str(v))
	return count

cc = 0
for i in range(1, 10):
	cc += tbase(i, 50)

print(cc)
