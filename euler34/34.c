/* euler 34 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define CAP 2540160

typedef unsigned long long ull;

ull fac[CAP] = {0};
ull getfac(unsigned ind);

int test(unsigned long num);

int main(int argc, char** argv) {
	unsigned long total = 0;

	for (unsigned long i = 100; i < CAP; ++i) {
		if (test(i)) {
			printf("%lu passed\n", i);
			total += i;
		}
	}

	printf("total: %lu\n", total);

	return 0;
}

ull getfac(unsigned ind) {
	if (!ind) return 1;
	if (ind == 1) return 1;
	if (ind == 2) return 2;

	if (fac[ind]) return fac[ind];
	ull output = getfac(ind - 1) * ind;
	fac[ind] = output;
	return output;
}

int test(unsigned long num) {
	printf("testing %lu\n", num);
	char* digit_str = malloc(floor(log10(num)) + 2);
	snprintf(digit_str, floor(log10(num)) + 2, "%lu", num);

	unsigned long total = 0;

	for (char* cur = digit_str; *cur; ++cur) {
		int dig = *cur - '0';
		printf("dig: %d -> %d\n", dig, getfac(dig));
		total += getfac(dig);

		if (total > num) {
			printf("%lu overflowed at %lu\n", num, total);
			free(digit_str);
			return 0;
		}
	}

	if (total != num) {
		printf("%lu failed with total %lu\n", num, total);
	}

	free(digit_str);
	return (total == num);
}
