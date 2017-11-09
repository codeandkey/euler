/* project euler: problem 74 */
#include "common.h"

int fac[10] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880 };

void euler74(void);

int main(int argc, char** argv) {
	timer(euler74);
	return 0;
}

int fsum(int x) {
	int d = fac[x%10];
	while (x /= 10) {
		d += fac[x%10];
	}
	return d;
}

int lengths[1000000] = {0};

void euler74(void) {
	int sum = 0;

	lengths[1]=1;
	lengths[0]=1;
	lengths[2]=1;
	lengths[169]=lengths[363601]=lengths[1454]=3;
	lengths[871]=lengths[45361]=2;
	lengths[872]=lengths[45362]=2;

	for (int i = 10; i < 999999; ++i) {
		int len = 1, next=i;
		while (!lengths[i]) {
			int pnext = next;
			next = fsum(next);
			if (pnext == next) {
				lengths[i]=len;
				break;
			}
			if (lengths[next]) {
				lengths[i] = len + lengths[next];
				break;
			} else {
				len++;
			}
		}

		if (lengths[i] == 60) {
			++sum;
		}
	}

	printf("final sum: %d of length 60\n", sum);
}
