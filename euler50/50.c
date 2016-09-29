/* project euler: problem 50 */
#include "common.h"

#define CAP 1000000
unsigned long prime_ind[CAP] = {0};
unsigned long primes[CAP] = {0};
unsigned long num_primes = 0;

void euler50(void);

int main(int argc, char** argv) {
	timer(euler50);
	return 0;
}

void euler50(void) {
	printf("generating and crunching primes\n");
	for (unsigned long i = 0; i < CAP; ++i) {
		if (is_prime(i)) {
			prime_ind[i] = is_prime(i);
			primes[num_primes++] = i;
		}
	}
	printf("done, found %lu primes\n", num_primes);
	printf("starting chain construction\n");
	for (unsigned long i = 0; i < num_primes - 1; ++i) {
		/* the prime index serves as a quick goto cache for is_prime */
		unsigned long chain_sum = 0, j;
		for (j = i + 1; j < num_primes; j++) { /* stop j at i to prevent buffer underflow */
			/* sub j from chain */
			chain_sum += primes[j];

			if (chain_sum >= CAP) {
				break;
			}

			if (prime_ind[chain_sum]) {
				/* chain sum is prime, print out chain info */
				printf("%lu -> sum %lu, starts %lu: ", (j - i) + 1, chain_sum, primes[i]);
				for (unsigned long c = i; c <= j; ++c) {
					//printf("%lu ", primes[c]);
				}
				printf("\n");
			}
		}
	}
	printf("done\n");
}
