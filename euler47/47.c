/* project euler: problem 29 */
#include "common.h"

#define START 100
#define CAP 10000000

typedef struct _pair {
	unsigned long base, exp;
	struct _pair* next;
} pair;

typedef struct _pf_list { /* an entry for a single number and its PF -- a base and exp are stored to indicate the exponentiation of the PF as a whole */
	unsigned long n;
	unsigned long exp;
	pair* pf;
	struct _pf_list* next;
} pf_list;

pair* get_pf(unsigned long n);
int pf_len(pair* pf);
void pf_free(pair* pf);
void output_pf(pair* pf);

void euler47(void);

int main(int argc, char** argv) {
	timer(euler47);
	return 0;
}

void euler47(void) {
	unsigned long csc_list[4] = {0};
	int csc = 0;

	for (unsigned i = START; i <= CAP; ++i) {
		pair* pf_base = get_pf(i); /* get the PF for the base n */
		//printf("pf of base %u : ", i);
		//output_pf(pf_base);

		if (pf_len(pf_base) == 4) {
			if (csc >= 2) {
				printf("pushing csc to %d with num %u\n", csc + 1, i);
				output_pf(pf_base);
			}
			csc_list[csc++] = i;
		} else {
			csc = 0;
		}

		if (csc == 4) {
			printf("found first 4 csc nums: s %lu\n", csc_list[0]);
			return;
		}

		pf_free(pf_base);
	}
}

pair* get_pf(unsigned long n) {
	pair* output = 0; /* the LL will grow in reversed order. */

	for (int i = 2; i < n; ++i) {
		unsigned count = 0;
		if (i >= ceil(sqrt(n)) + 1) break;
		if (!is_prime(i)) {
			//printf("%d not prime\n", i);
			continue;
		}

		while (!(n % i)) {
			//printf("dividing %d/%d (count = %d), resulting %d\n", n, i, count, n / i);
			n /= i;
			count++;
		}

		if (count) {
			pair* next_pair = malloc(sizeof *next_pair);
			next_pair->base = i;
			next_pair->exp = count;
			next_pair->next = output;
			output = next_pair;
		}
	}

	if (n > 1) { /* the last remaining number will be part of the PF */
		pair* next_pair = malloc(sizeof *next_pair);
		next_pair->base = n;
		next_pair->exp = 1;
		next_pair->next = output;
		output = next_pair;
	}

	return output;
}

void output_pf(pair* pf) {
	if (!pf) {
		printf("(null pf)\n");
		return;
	}

	while (pf) {
		printf("(b%lu, e%lu) ", pf->base, pf->exp);
		pf = pf->next;
	}

	printf("\n");
}

void pf_free(pair* pf) {
	pair* tmp = NULL;
	while (pf) {
		tmp = pf->next;
		free(pf);
		pf = tmp;
	}
}

int pf_len(pair* pf) {
	int out = 0;
	while (pf) {
		out++;
		pf = pf->next;
	}
	return out;
}
