/* project euler: problem 70 */
#include "common.h"

#define NUM 10000000

int cache[NUM] = {0};

void euler69(void);

/* optimized gcd by Daniel Lemire */
unsigned int gcd(unsigned int u, unsigned int v)
{
    int shift;
    if (u == 0) return v;
    if (v == 0) return u;
    shift = __builtin_ctz(u | v);
    u >>= __builtin_ctz(u);
    do {
        v >>= __builtin_ctz(v);
        if (u > v) {
            unsigned int t = v;
            v = u;
            u = t;
        }  
        v = v - u;
    } while (v != 0);
    return u << shift;
}

int totient(int n) {
	int sum = 1;

	for (int i = 2; i < n; ++i) {
		sum += (gcd(i, n) == 1);
	}

	return sum;
}

int main(int argc, char** argv) {
	timer(euler69);
	return 0;
}

void euler69(void) {
	float max = 100;
	int ind = 0;
	cache[1] = 1;
	printf("crunching totient\n");
	for (int i = 2; i < NUM; ++i) {
		if (!cache[i]) {
			cache[i] = i - 1;
			for (int j = 2; j * i < NUM; ++j) {
				if (!cache[j]) continue;
				int q = j, f = i - 1;
				while (!(q % i)) {
					f *= i;
					q /= i;
				}

				cache[i * j] = f * cache[q];
			}
		}
	}

	printf("crunching perms\n");

	for (int i = 2; i < NUM; ++i) {
		if (!num_is_perm_of(i, cache[i])) continue;

		float cur = (float) i / (float) cache[i];
		if (cur < max) {
			max = cur;
			ind = i;
		}

		printf("perm: %d (%d) -> ratio %f\n", i, cache[i], cur);
	}

	printf("minimum w/perm: %f (%d/%d) at i=%d (%d)\n", max, ind, cache[ind], ind, totient(ind));
}
