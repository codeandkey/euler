/* euler 23 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long d(unsigned long i);
int is_divisor(unsigned long n, unsigned long i);

#define CAP 28123
int rem[CAP] = {0}; /* rem[i] = 1 indicates a pair of ab. nums can sum to i */

unsigned long d_results[CAP] = {0}; /* stored values for d() */

int main(int argc, char** argv) {
	printf("computing d(i) for i < %d\n", CAP);

	for (unsigned long i = 0; i < CAP; ++i) {
		if (d(i) <= i) { d_results[i] = 0; } else { printf("abundant d(%d) = %d\n", i, d_results[i]); }
	}

	/* all abundant numbers are in d_results */
	for (unsigned long i = 0; i < CAP; ++i) {
		if (!d_results[i]) continue;
		for (unsigned long j = i; j < CAP; ++j) {
			if (!d_results[j]) continue;
			unsigned long ind = i + j;
			if (ind < CAP && !rem[ind]) {
				printf("marking %d as unviable (%d + %d = %d)\n", ind, i, j, ind);
				rem[ind] = 1;
			}
		}
	}

	unsigned long result = 0;

	/* sum all remaining */
	for (unsigned long i = 0; i < CAP; ++i) {
		if (!rem[i]) {
			result += i;
			printf("%d viable\n", i);
		}
	}

	printf("done, result = %d\n", result);
	return 0;
}

unsigned long d(unsigned long n) {
	/* brute-force sum of divisors */
	unsigned long output = 0;

	if (!n) return 0;
	if (n == 1) return 0;
	if (n == 2) return 1;

	if (n < CAP && d_results[n]) {
		return d_results[n]; /* ret. known value */
	}

	for (unsigned long i = 1; i <= (unsigned long) (floor(sqrt((float) n))); ++i) {
		if (is_divisor(n, i)) {
			output += (i + (n / i)); /* add both the divisor and its counterpart */

			if (i == (n / i)) {
				output -= i;
			}
		}
	}

	d_results[n] = output - n;
	return output - n; /* subtract the original number */
}

int is_divisor(unsigned long large, unsigned long div) {
	/* quick solution using modular arithmetic to test clean division */
	return !(large % div);
}
