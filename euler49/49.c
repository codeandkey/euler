/* project euler: problem 49 */
#include "common.h"

#define N_MIN 1000
#define N_MAX 9999

int prime_ind[N_MAX] = {0};
unsigned long primes[N_MAX] = {0};
unsigned long num_primes = 0;

void euler49(void);

int main(int argc, char** argv) {
	timer(euler49);
	return 0;
}

void euler49(void) {
	for (unsigned long n = N_MIN; n <= N_MAX; ++n) {
		if (is_prime(n)) {
			prime_ind[n] = 1;
			primes[num_primes++] = n;
		}
	}

	printf("generated %lu primes\n", num_primes);
	/* for each prime, look for some evenly spaced perms */

	for (unsigned i = 0; i < num_primes; ++i) {
		for (unsigned long n = N_MIN; n < N_MAX; ++n) {
			if (primes[i] == n) continue;

			if (num_is_perm_of(primes[i], n)) {
				/* found 1 perm, check at n + 2*(n2-n) to do a super-fast third perm test */
				if (num_is_perm_of(primes[i], n + (n - primes[i]))) {
					/* found a perm triplet. check all three for primality */
					if (prime_ind[n] && prime_ind[n + (n - primes[i])]) {
						printf("found prime triplet: %lu %lu %lu\n", primes[i], n, n + (n - primes[i]));
					}
				}
			}
		}
	}
}
