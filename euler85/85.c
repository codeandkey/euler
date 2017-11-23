/* project euler: problem 85 */
#include "common.h"

void euler85(void);

int main(int argc, char** argv) {
	timer(euler85);
	return 0;
}

unsigned long grc(unsigned w, unsigned h);

void euler85(void) {
	/* proceed iteratively in a sweeping motion */
	/* 1x1, 2x1, 2x2, 1x2, 3x1, 3x2, 3x3, 2x3, 1x3, ... */

	unsigned diag = 1;
	unsigned dist = 2000000, ar = 0, w, h;

	while (1) {
		for (unsigned x = 1; x < diag; ++x) {
			/* test x*diag and diag*x (we can actually skip the second because it will be the same.  */
			unsigned long count = grc(diag, x);
			unsigned long cdist = max(count, 2000000) - min(count, 2000000);

			if (cdist < dist) {
				dist = cdist;
				ar = x*diag;
				w = diag;
				h = x;
			}
		}


		unsigned long dcount = grc(diag, diag);
		unsigned long ddist = max(dcount, 2000000) - min(dcount, 2000000);

		if (ddist < dist) {
			dist = ddist;
			ar = diag*diag;
			w = h = diag;
		}

		diag++;

		if (ddist > 30000000) break;
	}

	printf("final area: %u (final dist %u, %u by %u)\n", ar, dist, w, h);
}

unsigned long grc(unsigned w, unsigned h) {
	/* compute number of subrects for dimensions */
	/* compute a subrect and then see how much we can move it around */

	unsigned long count = 0;

	for (int sw = 1; sw <= w; ++sw) {
		for (int sh = 1; sh <= h; ++sh) {
			/* we can add to the count in a pretty straightforward way */
			/* first, compute the different positions we can have the subrect horizontally */
			count += (1 + (w - sw)) * (1 + (h - sh));
		}
	}

	return count;
}
