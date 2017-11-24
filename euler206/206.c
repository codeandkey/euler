/* project euler: problem 206 */
#include "common.h"

#include <math.h>

void euler206(void);

typedef unsigned __int128 big;

int main(int argc, char** argv) {
	timer(euler206);
	return 0;
}

void euler206(void) {
	for (unsigned in = 0; in <= 999999999; ++in) {
		big cursum = 1020304050607080900, c = in, magnitude = 1;
		for (unsigned int i = 0; i < 9; ++i) {
			/* construct the total 19-digit number quickly by spacing these digits */
			big dig = 0;
			dig = c % 10;
			magnitude *= 10;
			cursum += magnitude * dig;
			c /= 10;
			magnitude *= 10;
		}
		double aprx = sqrt(cursum);
		big api = (big) aprx;
		if (api*api > cursum) {
			while (api*api > cursum) --api;
		} else if (api*api < cursum) {
			while (api*api < cursum) ++api;
		}
		if (api*api == cursum) {
			printf("found at %llu^2 = %llu\n", api, cursum);
			break;
		}
		if (!(in%1000000)) printf("testing in=%llu, %llu\n", in, cursum);
	}
}
