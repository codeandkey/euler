/* project euler: problem 30 */
#include "common.h"

#define CAP 10000000 /* 10mil to start */

unsigned long get_digit_fp(unsigned long n);
void euler30(void);

int main(int argc, char** argv) {
	timer(euler30);
	return 0;
}

void euler30(void) {
	unsigned long cur = 1;
	while (cur <= CAP) {
		unsigned long dfp = get_digit_fp(cur);
		if (dfp == cur) {
			printf("match: %lu\n", cur);
		} else {
			printf("dfp (%lu) = %lu\n", cur, dfp);
		}
		cur++;
	}
}

unsigned long get_digit_fp(unsigned long n) {
	unsigned long out = 0;

	while (n >= 1) {
		out += pow(n % 10, 5);
		n /= 10;
	}

	return out;
}
