/* euler 37 - truncatable primes */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define CAP 1000000

int is_prime(unsigned long ind);
int test(unsigned long prime);

int main(int argc, char** argv) {
	unsigned long total = 0;

	for (unsigned long i = 10; i <= CAP; ++i) {
		if (is_prime(i)) {
			if (test(i)) {
				printf("PASS: %lu\n", i);
				total += i;
			} else {
				printf("FAIL: %lu\n", i);
			}
		}
	}

	printf("total: %lu\n", total);

	return 0;
}

int is_prime(unsigned long ind) {
	if (ind <= 1) return 0;
	if (ind == 2) return 1;
	if (ind == 3) return 1;
	if (!(ind % 2)) return 0;

	for (int i = 3; i <= sqrt(ind); i+=2) {
		if (!(ind % i)) return 0;
	}

	return 1;
}

int test(unsigned long prime) {
	int num_digits = floor(log10(prime)) + 1;
	char* str = malloc(num_digits + 1);
	memset(str, 0, num_digits + 1);

	snprintf(str, num_digits + 1, "%lu", prime);

	switch(str[num_digits - 1] - '0') { /* hella fast optimization for checking last digit */
	case 1:
	case 4:
	case 6:
	case 8:
	case 9:
	case 0:
		free(str);
		return 0;
	}

	switch(*str - '0') { /* check first digit */
	case 1:
	case 4:
	case 6:
	case 8:
	case 9:
	case 0:
		free(str);
		return 0;
	}

	/* left-test */
	for (int i = 1; i < num_digits; ++i) {
		if (!is_prime(strtol(str + i, NULL, 0))) {
			free(str);
			return 0;
		}
	}

	/* right-test */
	for (int i = 1; i < num_digits; ++i) {
		str[num_digits - i] = 0;
		if (!is_prime(strtol(str, NULL, 0))) {
			free(str);
			return 0;
		}
	}
	
	free(str);

	return 1;
}
