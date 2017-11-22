/* project euler: problem 94 */
#include "common.h"

/*
 * to do this it's sufficient to determine whether (a+b+c)(a+b-c)(a+c-b)(b+c-a) is a perfect square
 * as a=b this is equivalent to (a+b+c)(a+b-c)(a+c-b)^2, so we can pull out the third element and just test:
 * (a+b+c)(a+b-c) which should be a perfect square
 * so, we can determine whether 2 divides all of the prime factor counts
 */

int dpf3(unsigned long long val); /* determine if val is perfect square using double approx and then squaring */
int test(int ab, int c);
void euler94(void);

int main(int argc, char** argv) {
	timer(euler94);
	return 0;
}

void euler94(void) {
	unsigned long long ab = 2, c = 0, perm_sum = 0;

	printf("crunching triangles\n");

	while (1) {
		//if (!(ab % 100000)) printf("testing ab=%llu\n", ab);
		c = ab + 1;

		if (2*ab+c < 1000000000) {
			perm_sum += test(ab, c);
		}

		c = ab - 1;

		if (2*ab+c >= 1000000000) break;
		if (c > 0) perm_sum += test(ab, c);

		ab++;
	}

	printf("result: %llu\n", perm_sum);
}

int test(int ab, int c) {
	unsigned long long t = ab * 2, v = (t-c)*(t+c);
	return dpf3(v) * (2*ab+c);
}

int dpf3(unsigned long long val) {
	double apx = sqrt((double) val);
	unsigned long long rnd = (unsigned long long) apx;

	if (rnd*rnd > val) {
		/* approximation is above, starting moving down until we pass */
		while (rnd*rnd > val) rnd--;
	} else {
		/* approx below, increment until we pass */
		while (rnd*rnd < val) rnd++;
	}

	return (rnd*rnd == val);
}
