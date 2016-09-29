#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* JTS */
/* compute solution to project euler problem 21 */

#define MAX_SUM 10000
unsigned long results[MAX_SUM] = {0};

/* boolean array designating amicables */
int amicable[MAX_SUM] = {0};

int is_divisor(unsigned long large, unsigned long div);
unsigned long d(unsigned long n);
void search_chain(unsigned long i);

int main(int argc, char** argv) {
	printf("computing d(i) for all i < %d\n", MAX_SUM);

	for (unsigned long i = 1; i < MAX_SUM; ++i) {
		results[i] = d(i);
	}

	printf("searching chains for amicable pairs\n");

	for (unsigned long i = 1; i < MAX_SUM; ++i) {
		/* reiterate results, check for pairs */
		search_chain(i);
		printf("d(%d) = %d\n", i, d(i));
	}

	unsigned long output = 0;

	for (unsigned long i = 2; i < MAX_SUM; ++i) {
		if (amicable[i]) output += i;
	}

	printf("finished, sum: %d\n", output);
	return 0;
}

void search_chain(unsigned long i) {
	unsigned long f_d = 0, f_second = 0;
	printf("searching chain %d\n", i);

	if (i <= 2) {
		printf("pruning chain\n");
		return;
	}

	if (i > MAX_SUM) {
		printf("pruning chain: high i\n");
		return;
	}

	if (amicable[i]) {
		printf("pruning chain: found previous amicable\n");
		return;
	}

	if (results[i]) {
		f_d = results[i];
	} else {
		printf("pruning chain on %d: no d() saved\n");
		return;
	}

	if (results[f_d]) {
		f_second = results[f_d];
	} else {
		printf("pruning chain on second %d: no d() saved\n");
	}

	if (f_second == i && (f_d != f_second)) {
		/* chain leads back to f_d -- f_d and f_second are amicable */
		amicable[f_d] = 1;
		amicable[f_second] = 1;

		printf("located amicable pair %d, %d\n", f_d, f_second);
	} else if (f_d != f_second) {
		/* no chain here; proceed to next set */
		printf("following chain from f_second = %d\n", f_second);
		search_chain(f_second);
	} else {
		printf("pruning perfect pair i=%d\n", i);
		return;
	}
}

unsigned long d(unsigned long n) {
	/* brute-force sum of divisors */
	unsigned long output = 0;

	if (!n) return 0;
	if (n == 1) return 0;
	if (n == 2) return 1;

	for (unsigned long i = 1; i <= (unsigned long) (floor(sqrt((float) n))); ++i) {
		if (is_divisor(n, i)) {
			output += (i + (n / i)); /* add both the divisor and its counterpart */

			if (i == (n / i)) {
				output -= i;
			}
		}
	}

	printf("d(%d) = %d\n", n, output - n);
	return output - n; /* subtract the original number */
}

int is_divisor(unsigned long large, unsigned long div) {
	/* quick solution using modular arithmetic to test clean division */
	return !(large % div);
}
