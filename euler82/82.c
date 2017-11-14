/* project euler: problem 82 */
#include "common.h"

void euler82(void);

#define LINEMAX 2048
#define WIDTH 80
#define HEIGHT 80

int matrix[WIDTH*HEIGHT] = {0};
char line[LINEMAX] = {0};

int main(int argc, char** argv) {
	timer(euler82);
	return 0;
}

int compute(int x, int y) {
	/* this one's a bit simpler -- we connect each element to the column on the right and use the smallest path */

	int output = matrix[y*WIDTH+x] + matrix[y*WIDTH+x+1]; /* start with cy=y just to make sure things are sane */

	for (int cy = 0; cy < 80; ++cy) {
		/* try a connection to (x+1, cy) and test the sum */

		int sum = matrix[cy*WIDTH+x+1];

		/* sum (x, y->cy) inclusive and then (x+1, cy) */

		for (int sy = 0; sy < 80; ++sy) {
			if (sy >= min(y, cy) && sy <= max(y, cy)) {
				sum += matrix[sy*WIDTH+x];
			}
		}

		if (sum < output) output = sum;
	}

	return output;
}

void euler82(void) {
	printf("loading matrix data\n");

	FILE* f = fopen("matrix.txt", "r");
	if (!f) return;

	for (int i = 0; i < HEIGHT; ++i) {
		fgets(line, LINEMAX, f);
		char* c = strtok(line, ",");
		int cur = 0;

		matrix[WIDTH * i] = strtol(c, NULL, 10);

		for (int j = 0; j < WIDTH - 1; ++j) { /* first one already good */
			c = strtok(NULL, ",");
			matrix[WIDTH * i + j + 1] = strtol(c, NULL, 10);
		}
	}

	printf("done\n");

	/*
	 * this one can be computed differently -> we can combine columns starting from the left iteratively.
	 */

	for (int x = WIDTH - 2; x >= 0; --x) {
		/* we want to reduce this column to the minsums for each of it's elements so we can treat it as a new "right" side. */
		/* so, we for each y we compute the minsum manually by connecting each element to each other element and seeing how the paths add up. */

		int str[HEIGHT] = {0};

		for (int y = 0; y < HEIGHT; ++y) {
			str[y] = compute(x, y);
		}

		for (int y = 0; y < HEIGHT; ++y) {
			matrix[y*WIDTH+x] = str[y];
		}
	}

	int ms = matrix[0];

	for (int t = 0; t < HEIGHT; ++t) {
		if (matrix[t*WIDTH] < ms) ms = matrix[t*WIDTH];
	}

	printf("min: %d\n", ms);
}
