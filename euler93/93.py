#!/bin/python
# euler 93
#
# parentheses can have 5 distinct states:
#
# (a . b) . (c . d)
# ((a . b) . c) . d
# (a . (b . c)) . d
# a . ((b. c)) . d
# a . (b . (c . d))

from itertools import permutations, combinations_with_replacement

def do_op(a, b, op):
	if (op == 0):
		return a+b
	if (op == 1):
		return a-b
	if (op == 2):
		if (b == 0):
			return None
		return a/b
	if (op == 3):
		return a*b

def opstr(op):
	if (op == 0):
		return "+"
	if (op == 1):
		return "-"
	if (op == 2):
		return "/"
	if (op == 3):
		return "*"

def calg(values):
	[a, b, c, d] = values
	output = []
	for oa in range(4):
		for ob in range(4):
			for oc in range(4):
				ops = [oa, ob, oc]
				for paren in range(5):
					cur = None
					if (paren == 0):
						cur = do_op(do_op(a, b, ops[0]), do_op(c, d, ops[2]), ops[1])
					if (paren == 1):
						cur = do_op(do_op(do_op(a, b, ops[0]), c, ops[1]), d, ops[2])
						if (values == [4, 3, 1, 2]):
							if (ops == [3, 1, 3]):
								print("CVAL " + str(cur))
					if (paren == 2):
						cur = do_op(do_op(a, do_op(b, c, ops[1]), ops[0]), d, ops[2])
					if (paren == 3):
						cur = do_op(a, do_op(do_op(b, c, ops[1]), d, ops[2]), ops[0])
					if (paren == 4):
						cur = do_op(a, do_op(b, do_op(c, d, ops[2]), ops[1]), ops[0])
					if (cur == None):
						continue
					if (int(cur) != cur):
						continue
					output.append(cur)
	return output

def chlen(a, b, c, d):
	hit = []
	for p in permutations([a, b, c, d], 4):
		hit += calg(p)
	it = sorted(set(hit))
	cur = 0
	curval = 1
	try:
		cur = it.index(1)
	except ValueError:
		return 0
	while True:
		try:
			if (it[cur + 1] != curval + 1):
				return curval
		except IndexError:
			return curval
		cur += 1
		curval += 1

chlong = 0
lset = []

for a in range(1, 7):
	for b in range(a + 1, 8):
		for c in range(b + 1, 9):
			for d in range(c + 1, 10):
				curlen = chlen(a, b, c, d)
				if (curlen > chlong):
					chlong = curlen
					lset = [a, b, c, d]
					print("new large: " + str(lset) + " => chlen " + str(chlong))

print("lset: " + str(lset))
