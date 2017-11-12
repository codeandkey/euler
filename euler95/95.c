/* project euler: problem 95 */
#include "common.h"

#define NUM 1000000
#define MAXLEN 500

int cache[NUM + 1] = {0};

void euler95(void);

int main(int argc, char** argv) {
	timer(euler95);
	return 0;
}

/* we use a recursive method to quickly compute the aliquot sum for x */
int dsum(int x) {
	if (x <= 0) return 0;
	if (x <= 3) return x;
	if (cache[x]) return cache[x];

	int s = 1;
	for (int i = 2; i <= sqrt(x); ++i) {
		if (!(x%i)) {
			s += i;
			s += x/i;
		}
		if (x&1) i++; /* extra add if it's an odd num */
	}
	cache[x] = s;
	return s;

	int k = 1; /* use a pentagonal traversal to quickly compute.. */
	int iter = 0;
	int sum = 0;

	while (1) {
		int a = k*(3*k-1)/2, b = (-k)*(-3*k-1)/2;
		int first = dsum(x - a), second = dsum(x - b);

		if (++iter % 2) {
			sum += first + second;
		} else {
			sum -= (first + second);
		}

		if (!first && !second) {
			break; /* not getting anything done.. */
		}

		++k;
	}

	cache[x] = sum;
	return sum;
}

void euler95(void) {
	printf("grinding amicable chains\n");

	int sm = 0, chlen = 0;
	int curchain[MAXLEN] = {0};

	for (int i = 0; i < 1000000; ++i) {
		memset(curchain, 0, sizeof curchain);

		/* check for chain starting at i */
		int len = 1;
		int smallest = i;
		int cur = i, prev = 0;
		*curchain = i;

		while (1) {
			cur = curchain[len++] = dsum(cur);
			// printf(" -> %d", cur);
			if (cur >= 1000000) {
				break;
			}
			if (cur == i) {
				if (len > chlen) {
					chlen = len;
					sm = smallest;
					printf("pushed saved values to %d, %d\n", sm, chlen);
				}
				printf("chain at %d, cutting off at len=%d\n", i, len);
				break;
			}
			if (cur == prev) {
				break;
			}
			if (len > MAXLEN || cur <= 3) {
				break;
			}
			len++;
			if (cur < smallest) smallest=cur;
		}
	}

	printf("sm: %d, chlen=%d\n", sm, chlen);
}
