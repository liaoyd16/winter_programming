
#gen.py

import random as rand
import sys

def gen(batch_num):
	wr = str(batch_num) + "\n"
	# ans = ""
	a = -1
	b = -1
	for i in xrange(batch_num):
		# a = rand.randint(1, 10**4999)
		# b = rand.randint(1, 10**4999)
		a = 10**5000-1
		b = 10**5000-1
		wr += str(a) + " " + str(b) + "\n"
		# ans += str(a*b) + "\n"

	open("feed.txt", "w").write(wr)
	# open("ans.txt", "w").write(ans)

def check(batch_num):
	tr = open("out.txt", "r")
	que = open("feed.txt", "r")
	a = -1
	b = -1
	que.readline()
	line = None
	base = -1
	for l in xrange(batch_num):
		out = int(tr.readline().rstrip())
		line = que.readline()
		a = int(line.split(" ")[0])
		b = int(line.split(" ")[1])
		base = a*b
		if not out==base:
			print "line #", l, "base =", base, "ans = ", out
		else:
			print "ok"

sw = sys.argv[1]
if sw == '0':
	gen(int(sys.argv[2]))
else:
	check(int(sys.argv[2]))