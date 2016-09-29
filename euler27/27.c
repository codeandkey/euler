/* project euler: problem 27 */
#include "common.h"

#define A_MIN -1000
#define B_MIN 2 
#define A_MAX 1000
#define B_MAX 1000

void euler27(void);

int main(int argc, char** argv) {
	timer(euler27);
	return 0;
}

int test(int a, int b) {
	if (!is_prime(b)) return 0;
	unsigned len = 0;
	int n = 0;
	while (1) {
		if (!is_prime((pow(n, 2) + a*n + b))) break;
		len++;
		n++;
	}
	printf("len=%u (a=%d b=%d)\n", len, a, b);
	return len;
}

void euler27(void) {
	int ma = A_MIN, mb = B_MIN, ml = 0;
	for (int a = A_MIN; a <= A_MAX; ++a) {
		for (int b = B_MIN; b <= B_MAX; ++b) {
			int result = test(a, b);
			if (result > ml) {
				ml = result;
				ma = a;
				mb = b;
			}
		}
	}

	printf("largest: %d with a=%d, b=%d\n", ml, ma, mb);
}
