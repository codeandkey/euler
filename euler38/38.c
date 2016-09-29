/* project euler: problem 38 */
#include "common.h"

#define N_MIN 9
#define N_CAP 9876
#define C_CAP 5

int strocc(char* str, int c);
int is_pandigital(char* num);
int num_digits(unsigned long n);
void euler38(void);

int main(int argc, char** argv) {
	timer(euler38);
	return 0;
}

void euler38(void) {
	for (unsigned n = N_MIN; n <= N_CAP; ++n) {
		char cur_cat[10] = {0};
		int cur_pos = 0;
		unsigned c;
		printf("starting n=%u\n", n);
		for (c = 1; c <= C_CAP; ++c) {
			/* fmt into cur_cat at curpos, if 10-c*num_digits(n) bytes are written => bad */
			cur_pos += snprintf(cur_cat + cur_pos, 10 - cur_pos, "%u", n * c);
			printf("cur_cat: %s, cur_pos: %d\n", cur_cat, cur_pos);
			if (strocc(cur_cat, '0')) {
				printf("found 0, pruning\n");
				goto next_n;
			}
			for (int h = '1'; h <= '9'; ++h) {
				if (strocc(cur_cat, h) > 1) {
					printf("repeat of %c detected, pruning\n", h);
					goto next_n; /* escaping nested loops is not cool */
				}
			}
			if (cur_pos >= 9) {
				printf("all digits filled\n");
				break; /* all digits filled */
			}
		}

		for (int h = '1'; h <= '9'; ++h) { /* we made it this far, check to see it's a 9-perm */
			if (strocc(cur_cat, h) != 1) {
				goto next_n; /* repeats somewhere, run away */
			}
		}

		/* probably a 9-perm, put it on the screen */
		printf("possible match: n=%u c=(1-%u)  %s\n", n, c, cur_cat);

		next_n: continue;
	}
}

int is_pandigital(char* num) {
	int taken[9] = {0};
	while (*num) {
		if (taken[*num - '0']) {
			return 0;
		}
		taken[*num - '0'] = 1;
		num++;
	}
	for (int i = 0; i < sizeof taken / sizeof *taken; ++i) {
		if (!taken[i]) return 0;
	}
	return 1;
}

int num_digits(unsigned long n) {
	return floor(log10(n)) + 1;
}

int strocc(char* c, int o) {
	int out = 0;
	while (*c) {
		out += (*c == o);
		c++;
	}
	return out;
}
