/* project euler: problem 44 */
#include "common.h"

#define CAP 1000000

void euler44(void);

int main(int argc, char** argv) {
	timer(euler44);
	return 0;
}

void euler44(void) {
	unsigned long l = 165;

	while (l <= CAP) {
		if (floor(sqrt(3*pow(l, 2) - l))*(floor(sqrt(3*pow(l, 2) - l))+1) == 3 * pow(l, 2) - l) {
			printf("L: %lu\n", l);
		}

		l++;
	}
}
