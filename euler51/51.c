/* project euler: problem 51 */
#include "common.h"

void euler51(void);

int main(int argc, char** argv) {
	timer(euler51);
	return 0;
}

void euler51(void) {
	unsigned i = 56002;
	while (1) {
		while (!is_prime(++i));

		int digs = 1 + (int) log10(i); /* log(100) = 2, so 3 digits */
		int bitmax = pow(2, digs); /* 0->(bitmax-2) is the value range we work with, 2^3=8 -2=6 (we ignore all bits on and all bits off */

		for (int comb = 1; comb < bitmax - 1; ++comb) {
			/* use bits in combination */
			int chlen = 0;
			if (comb & 1) continue; /* the first digit can't be replaced */
			for (int repl = 0; repl <= 9; ++repl) {
				if (!repl && (comb >> (digs - 1))) continue; /* skip leading 0 */
				int cur_digit = 0, cur_value = i, new_num = 0, ccm = comb;
				for (cur_digit = 0; cur_digit < digs; ++cur_digit) {
					int cur = cur_value % 10;
					if (!(ccm & 1)) {
						new_num += cur * pow(10, cur_digit);
					} else {
						new_num += repl * pow(10, cur_digit);
					}

					cur_value /= 10;
					ccm /= 2;
				}

				if (is_prime(new_num)) {
					printf("prime: %d\n", new_num);
					chlen++;
				}
			}
			printf("%d-chain found at i=%d, comb=%d\n", chlen, i, comb);
			if (chlen == 8) {
				printf("8-chain found at i=%d, comb=%d%d%d%d%d%d\n", i, comb>>5, (comb>>4)&1, (comb>>3)&1, (comb>>2)&1, (comb>>1)&1, comb&1);
				exit(0);
			}
		}
	}
}
