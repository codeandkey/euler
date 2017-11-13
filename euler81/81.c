/* project euler: problem 81 */
#include "common.h"

void euler81(void);

#define LINEMAX 2048

int matrix[80*80] = {0};
char line[LINEMAX] = {0};

int minsum[80*80] = {0};

/* minsum [80*y+x] stores the minimum path sum from (x, y) to (79, 79)
 * we'll be computing these recursively, similar to a graph construction */

int main(int argc, char** argv) {
	timer(euler81);
	return 0;
}

int compute(int x, int y) {
	int right = 0, down = 0, output;


	if (minsum[x + y * 80]) return minsum[x + y * 80];

	if (x == 79 && y == 79) return matrix[81*79];
	if (x < 79) {
		output = right = compute(x + 1, y) + matrix[x+y*80];
	}

	if (y < 79) {
		output = down = compute(x, y + 1) + matrix[x+y*80];
	}

	if (down && right) output = ((right < down) ? right : down);
	minsum[x+y*80] = output; /* keep a cache for speed */
	printf("computing %d, %d -> %d\n", x, y, output);

	return output;
}

void euler81(void) {
	printf("loading matrix data\n");

	FILE* f = fopen("matrix.txt", "r");
	if (!f) return;

	for (int i = 0; i < 80; ++i) {
		fgets(line, LINEMAX, f);
		char* c = strtok(line, ",");
		int cur = 0;

		matrix[80 * i] = strtol(c, NULL, 10);

		for (int j = 0; j < 79; ++j) { /* first one already good */
			c = strtok(NULL, ",");
			matrix[80 * i + j + 1] = strtol(c, NULL, 10);
		}
	}

	printf("done\n");

	/* scanning paths -- any ordering of 79 "rights" and 79 "downs" */
	/* so, a path length will be of length 158 */

	/* we might be able to traverse these recursively, actually */

	int sum = compute(0, 0); /* min sum from bottom-left corner */
	printf("final sum: %d\n", sum);
}
