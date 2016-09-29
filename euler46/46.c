#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define CAP 100000

int* c;
int* p;

int is_prime(int n);
void print_pb(float p);

int main(int argc, char** argv) {
	c = malloc(CAP * sizeof *c);
	p = malloc(CAP * sizeof *p);

	printf("initializing lists\n");

	for (int i = 0; i < CAP; ++i) {
		c[i] = 1;
		p[i] = 2;
	}

	printf("marking evens, primes\n");

	for (int i = 0; i < CAP; ++i) {
		if (!i) c[i] = 0;

		if (!(i % 2)) {
			c[i] = 0;
			continue;
		}

		if (is_prime(i)) {
			c[i] = 0;
		}
	}

	printf("marking prime-square combinations\n");

	for (int i = 0; i < CAP; ++i) {
		if (is_prime(i)) {
			int k = 1;
			while (i + 2 * pow(k, 2) <= CAP) {
				c[i + 2 * (int) pow(k++, 2)] = 0;
			}
		}
	}

	printf("checking for unmarked entries\n");

	for (int i = 0; i < CAP; ++i) {
		if (c[i]) {
			printf("found unmarked at ind %i\n", i);
			return 0;
		}
	}

	printf("all entries marked\n");
	return 0;
}

int is_prime(int n) {
	if (p[n] != 2) return p[n];

	if (n <= 3) return 1;
	if (!(n % 2)) return 0;

	for (int i = 3; i < n; i += 2) {
		if (!(n % i)) {
			p[n] = 0;
			return 0;
		}
	}

	p[n] = 1;
	return 1;
}
