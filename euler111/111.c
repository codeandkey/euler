/* project euler: problem 111 */
#include "common.h"

#define MAXPRIMES 512
#define DIG 10

typedef unsigned long long big;

void euler111(void);
big s(int n, int d);
void place(big* primes, int* count, big* dest, int startpos, int digits, int avoid); /* digits is additional subdigits, 1 is assumed with digits=0 */

int main(int argc, char** argv) {
	timer(euler111);
	return 0;
}

void euler111(void) {
	big sum = 0;
	for (int i = 0; i <= 9; ++i) {
		printf("testing d=%d\n", i);
		sum += s(DIG, i);
	}
	printf("final sum: %llu\n", sum);
}

big s(int n, int d) {
	/* sum of primes with maximum repeated digits of d */
	int curprime = 0, curm = n - 1;
	big primes[MAXPRIMES] = {0}, sum = 0;
	/* we start by assuming m(n, d) = n - 1 and slowly decrease it */
	/* we generate numbers where there are m() repeating digits and iterate through all possibilities */
	/* to iterate, we generate (n-m) digit numbers and place the digits all over the place */
	big base = 0;
	for (int i = 0; i < n; ++i) {
		big cur = d;

		for (int j = 0; j < i; ++j) {
			cur *= 10;
		}

		base += cur;
	}

	// base = max(base, pow(10, DIG - 1)); /* avoid leading zeros */

	printf("base for s(%d, %d) -> %llu\n", n, d, base);
	printf("starting iterations with m = %d\n", curm);

	while (curm) {
		int num_digits = n - curm;

		/* iterate through n-m digits to place */
		big cur = base;
		/* we'll use a recursive method to place the digits here */
		place(primes, &curprime, &cur, 0, num_digits - 1, d);

		if (curprime > 0) {
			/* there are some primes here, we can sum them and get out of here */
			for (int i = 0; i < curprime; ++i) {
				sum += primes[i];
			}

			printf("found %d primes for n=%d, d=%d, m(n, d) = %d, sum = %llu\n", curprime, n, d, curm, sum);
			return sum;
		}

		curprime=0;
		curm--;
	}

	return 0;
}

void place(big* primes, int* count, big* num, int start, int digits, int avoid) {
	/* replace each digit one by one excluding everything before start */

	for (int i = start; i < DIG - digits; ++i) {
		for (int d = 0; d <= 9; ++d) {
			if (d == avoid) continue;
			if (i == DIG-1 && !d) continue; /* don't set a leading 0 */
			/* we need to replace digit at position i with d */
			big cur = *num, tmp = cur, magnitude = 1;
			for (int s = 0; s < i; ++s) {
				tmp /= 10;
				magnitude *= 10;
			}
			cur -= (tmp % 10) * magnitude;
			cur += d * magnitude;

			/* do some fancy recursion here */
			if (digits) {
				place(primes, count, &cur, i + 1, digits - 1, avoid);
			} else {
				if (is_prime(cur) && log10(cur) >= DIG - 1) {
					printf("good prime: %llu\n", cur);
					primes[*count] = cur;
					(*count)++;
				}
			}
		}
	}
}
