/* project euler: problem 52 */
#include "common.h"

void euler52(void);

int main(int argc, char** argv) {
	timer(euler52);
	return 0;
}

void euler52(void) {
	unsigned i = 0;
	while (++i) {
		if (!num_is_perm_of(i, i*2)) continue;
		if (!num_is_perm_of(i, i*3)) continue;
		if (!num_is_perm_of(i, i*4)) continue;
		if (!num_is_perm_of(i, i*5)) continue;
		if (!num_is_perm_of(i, i*6)) continue;

		printf("found: %d\n", i);
		break;
	}
}
