/* project euler: problem 119 */
#include "common.h"

#define NUMTEST 100

void euler119alt(void);

int main(int argc, char** argv) {
	timer(euler119alt);
	return 0;
}

int dseq(unsigned long long n, int val) {
	int sum = 0;
	while (n) {
		sum += n % 10;
		if (sum > val) return 0;
		n /= 10;
	}
	return (sum == val);
}

void euler119alt(void) {
	printf("starting 119 alternate solution\n");

	/* this solution uses a generating method.. we just hope that they are mostly in order */

	unsigned int cdig = 2;
	unsigned long long cval = cdig, power = 1;

	unsigned long long found[NUMTEST] = {0}, fc = 0;

	for (cdig = 2; cdig <= 300; ++cdig) {
		printf("testing powers for dig %u, cval=%llu\n", cdig, cval);

		cval = cdig;
		power = 1;

		for (int i = 0; i < 20; ++i) {
			cval *= cdig;
			++power;

			printf("testing power %u ^ %llu = %llu\n", cdig, power, cval);

			if (dseq(cval, cdig)) {
				found[fc++] = cval;
				
				printf("%llu found value %llu = %u ^ %llu\n", fc - 1, cval, cdig, power);
			}
		}
	}

	/* sort list and find the 30th one */
	for (int i = 0; i < fc; ++i) {
		unsigned long long sm = found[i], smind = i, tmp;

		for (int j = i + 1; j < fc; ++j) {
			if (found[j] < sm) {
				sm = found[j];
				smind = j;
			}
		}

		if (i != smind) {
			tmp = found[i];
			found[i] = sm;
			found[smind] = tmp;
		}
	}

	printf("pos 30: %llu\n", found[29]);
}
