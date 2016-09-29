/* project euler: problem 41 */
#include "common.h"

#define CAP 88888888

void euler41(void);

void test_perm(char* perm);
int is_perm(unsigned long n);
int is_prime(unsigned long n);

int main(int argc, char** argv) {
	timer(euler41);
	return 0;
}

void euler41(void) {
	for (unsigned long i = 10; i < CAP; ++i) {
		if (!is_perm(i)) continue;
		printf("perm: %lu\n", i);
		if (is_prime(i)) printf("PASS: %lu\n", i);
	}
}

void test_perm(char* perm) {
	printf("test_perm called with %s\n", perm);

	if (is_prime(strtol(perm, NULL, 10))) {
		printf("PASS %s\n", perm);
	} else {
		printf("FAIL %s\n", perm);
	}
}

int is_prime(unsigned long n) {
	if (n <= 1) return 0;
	if (n <= 3) return 1;
	if (!(n % 2)) return 0;

	for (unsigned i = 3; i <= ceil(sqrt(n)); i += 2) {
		if (!(n % i)) return 0;
	}

	return 1;
}

int is_perm(unsigned long n) {
	int dig_mark[9] = {0};
	int num_digits = floor(log10(n)) + 1;

	if (num_digits > 9) {
		return 0;
	}

	while (n >= 1) {
		int offset = (n % 10) - 1;

		if (offset < 0 || offset > num_digits) {
			return 0;
		}

		dig_mark[offset]++;
		n /= 10;
	}

	for (int i = 0; i < num_digits; ++i) {
		if (dig_mark[i] != 1) return 0;
	}

	return 1;
}
