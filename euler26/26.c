/* project euler problem 26 - reciprocal cycles */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define CAP 1000

unsigned int get_uniq_rem(unsigned int q);
int mark(int* list, int ind, int pos);

int main(int argc, char** argv) {
	int max = 0, mind = 0;
	for (int i = 1; i < CAP; ++i) {
		int res = get_uniq_rem(i);

		printf("%d -> %d\n", i, res);

		if (res > max) {
			max = res;
			mind = i;
		}
	}
	printf("maxmimum at i=%d with length %d\n", mind, max);
	return 0;
}

unsigned int get_uniq_rem(unsigned int d) {
	printf("calculating remainders for d=%d\n", d);

	int* rem = malloc(d * sizeof *rem);
	int* rem_index = malloc(d * sizeof *rem_index);

	int repeat = 0;

	memset(rem, 0, sizeof(d * sizeof *rem));
	for (int i = 0; i < d; ++i) rem_index[i] = -1;

	for (int i = 0; i < d; ++i) {
		if (!i) {
			rem[0] = 1;
		} else {
			rem[i] = 10 * rem[i - 1] - d * floor(10 * rem[i - 1] / d);
		}

		printf("rem for %d at position %d = %d\n", d, i, rem[i]);

		if ((repeat = mark(rem_index, rem[i], i))) {
			printf("repeat detected, breaking at %d\n", i);
			break;
		}
	}

	free(rem);
	free(rem_index);
	printf("returning remainder calc with %d\n", repeat);
	return repeat;
}

int mark(int* list, int ind, int pos) {
	if (list[ind] >= 0) {
		printf("remainder %d occurred last at %d, dist = (%d - %d) = %d\n", ind, list[ind], pos, list[ind], pos - list[ind]);
		return pos - list[ind];
	} else {
		printf("marking remainder %d with position %d\n", ind, pos);
		list[ind] = pos;
		return 0;
	}
}
