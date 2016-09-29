/* project euler: problem 78 */
#include "common.h"

#define PCACHEMAX 10000000
long pcache[PCACHEMAX] = {0};

void euler78(void);

long p(unsigned n);

int main(int argc, char** argv) {
	timer(euler78);
	return 0;
}

void euler78(void) {
	for (unsigned i = 0; i < PCACHEMAX; ++i) {
		pcache[i] = -1;
		printf("p(%u) = %lu\n", i, p(i));
		if (!p(i)) { printf("PASS p(%u) = %ld\n", i, p(i)); }
	}
}

long p(unsigned n) {
	if (!n) return 1;
	if (n <= 3) return n;
	if (n == 4) return 5;
	if (n == 5) return 7;

	if (n < PCACHEMAX && pcache[n] >= 0) {
		printf("returning stored p(%u) = %ld\n", n, pcache[n]);
		return pcache[n];
	}

	unsigned m = 1;
	long sum = 0;
	while(m * (3*m + 1) / 2 <= n) {
		printf("considering sm=p(n-m(3m+1)/2)\n");
		unsigned sm = p(n - (m * (3*m+1))/2);
		printf("m=%u, sm=%u\n", m, sm);
		if (m % 2) {
			printf("adding %u to sum %ld = %ld\n", sm, sum, sum + sm);
			sum += sm;
		} else {
			printf("subtracting %u from sum %ld = %ld\n", sm, sum, sum - sm);
			sum -= sm;
		}

		++m;
	}

	m = 1;
	while(m * (3*m - 1) / 2 <= n) {
		printf("considering sm=p(n-m(3m-1)/2)\n");
		unsigned sm = p(n - (m * (3*m-1))/2);
		printf("m=%u, sm=%u\n", m, sm);
		if (m % 2) {
			printf("adding %u to sum %ld = %ld\n", sm, sum, sum + sm);
			sum += sm;
		} else {
			printf("subtracting %u from sum %ld = %ld\n", sm, sum, sum - sm);
			sum -= sm;
		}
		++m;
	}

	long result = sum % 1000000;

	if (result < 0) {
		result += 1000000;
	}

	if (n < PCACHEMAX) {
		printf("storing newly computed p(%u) = %ld mod 10 = %ld\n", n, sum, result);
		pcache[n] = result;
	}

	return result;
}
