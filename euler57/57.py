from math import log10

num = 3
dem = 2
count = 0

for i in range(1000):
	num += dem
	tmp = num
	num = dem
	dem = tmp
	num += dem

	if (int(log10(num)) > int(log10(dem))):
		count += 1
		print("pass: " + str(num) + " / " + str(dem))

print("count = " + str(count))
