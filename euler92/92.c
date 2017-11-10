/* project euler: problem 92 */
#include "common.h"

#define NUM 10000000

void euler92(void);

void _chaincb(void* d, unsigned dig) {
	int* s = (int*) d;
	*s += dig*dig;
}

int chain(int x) {
	while (x != 1 && x != 89) {
		int nx = 0;
		foreach_digit(x, (void*) &nx, _chaincb);
		x = nx;
	}

	return (x == 89);
}

int main(int argc, char** argv) {
	timer(euler92);
	return 0;
}

void euler92(void) {
	int sum = 0;
	for (int i = 2; i < NUM; ++i) {
		int s = chain(i);
		sum += s;
		printf("%d -> %d\n", i, s);
	}

	printf("sum: %d\n", sum);
}
