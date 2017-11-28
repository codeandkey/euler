/* project euler: problem 77 */
#include "common.h"

void euler77(void);

#define PRIMES 1000
unsigned primes[PRIMES] = {0};

unsigned nsum(unsigned n);
unsigned _nsumsub(unsigned n, unsigned m);

int main(int argc, char** argv) {
	timer(euler77);
	return 0;
}

void euler77(void) {
	printf("crunching primes\n");

	unsigned cur = 1;
	for (unsigned i = 0; i < PRIMES; ++i) {
		while (!is_prime(++cur));
		primes[i] = cur;
	}

	printf("done\n");
	printf("crunching sums, 10 = %u\n", nsum(10));

	cur = 1;
	while (1) {
		if (nsum(++cur) > 5000) {
			printf("pass on cur=%u\n", cur);
			break;
		}
	}
}

unsigned nsum(unsigned n) {
	return _nsumsub(n, n);
}

unsigned _nsumsub(unsigned n, unsigned m) {
	/* compute prime partitions for n in strictly decreasing order */
	unsigned sum = 0;
	if (!n) return 1;
	if (n < 2) return 0;
	for (unsigned i = 0; primes[i] <= n; ++i) {
		if (primes[i] > m) break;
		int inner = _nsumsub(n - primes[i], primes[i]);
		sum += inner;
	}
	return sum;
}
