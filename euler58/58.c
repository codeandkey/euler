/* project euler: problem 58 */
#include "common.h"

void euler58(void);

int main(int argc, char** argv) {
	timer(euler58);
	return 0;
}

void euler58(void) {
	unsigned inc = 2, num_primes = 0, num_cps = 1, cur_num = 1;

	while (1) {
		for (int i = 0; i < 4; ++i) {
			/* go around the spiral 4x and watch for the diagonals */
			cur_num += inc;
			if (is_prime(cur_num)) {
				num_primes++;
			} else {
				num_cps++;
			}
		}

		if ((double) num_primes / (double) (num_primes + num_cps) < 0.1) {
			printf("dropped below ratio 0.1 at side length %u\n", inc + 1);
			break;
		}

		inc += 2;
	}
}
