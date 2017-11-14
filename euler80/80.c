/* project euler: problem 80 */
#include "common.h"

#include <gmp.h>
#include <mpfr.h>

#define BITS 16384

void euler80(void);

int main(int argc, char** argv) {
	timer(euler80);
	return 0;
}

void euler80(void) {
	mpfr_t root;
	mpfr_init2(root, BITS); /* precision for 100 digits */

	int s = 0;

	for (int i = 2; i <= 100; ++i) {
		if (sqrt(i) - floor(sqrt(i)) <= 0.0001f) continue;

		mpfr_sqrt_ui(root, (unsigned) i, MPFR_RNDD);

		char dig[256] = {0};

		mpfr_printf("sqrt(%d) = %.99RDf ", i, root);
		mpfr_snprintf(dig, sizeof dig, "%.99RDf", root);

		int is = *dig - '0';

		/* eval for 100 digits */
		for (int j = 0; j < 99; ++j) {
			is += dig[j + 2] - '0';
		}

		printf("total %d\n", is);
		s += is;
	}

	printf("final sum: %d\n", s);
}
