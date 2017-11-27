/* project euler: problem 97 */
#include "common.h"

void euler97(void);

int main(int argc, char** argv) {
	timer(euler97);
	return 0;
}

void euler97(void) {
	unsigned long long cur = 28433;

	for (int i = 0; i < 7830457; ++i) {
		cur *= 2;
		cur %= 10000000000;
	}

	printf("final: %llu\n", cur+1);
}
