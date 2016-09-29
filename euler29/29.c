/* project euler: problem 29 */
#include "common.h"

#define START 2
#define CAP 100

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
pair* exp_pf_cp(pair* pf, unsigned long e);
void pf_free(pair* pf);
void output_pf(pair* pf);

void euler29(void);

int main(int argc, char** argv) {
	timer(euler29);
	return 0;
}

void euler29(void) {
	for (unsigned i = START; i <= CAP; ++i) {
		pair* pf_base = get_pf(i); /* get the PF for the base n */
		//printf("pf of base %u : ", i);
		//output_pf(pf_base);

		for (unsigned exp = START; exp <= CAP; ++exp) {
			pair* pf_exp_output = exp_pf_cp(pf_base, exp);
			//printf("pf of %u^%u : ", i, exp);
			output_pf(pf_exp_output);
			pf_free(pf_exp_output);
		}

		pf_free(pf_base);
	}
}

pair* exp_pf_cp(pair* pf, unsigned long e) { /* copies a PF while exponentiating it */
	pair* output = NULL;

	while (pf) {
		pair* next = malloc(sizeof *next);

		next->exp = pf->exp * e;
		next->base = pf->base;

		next->next = output;
		output = next;

		pf = pf->next;
	}

	return output;
}

pair* get_pf(unsigned long n) {
	/* ONLY applies to numbers <= 100.. this cannot be used with other problems. */
	unsigned long primes[] = {2, 3, 5, 7};
	pair* output = 0; /* the LL will grow in reversed order. */

	for (int i = 0; i < (sizeof primes / sizeof *primes); ++i) {
		unsigned count = 0;

		if (primes[i] >= ceil(sqrt(n)) + 1) {
			break;
		}

		while (!(n % primes[i])) {
			n /= primes[i];
			count++;
		}

		if (count) {
			pair* next_pair = malloc(sizeof *next_pair);
			next_pair->base = primes[i];
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
