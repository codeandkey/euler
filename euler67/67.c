/* project euler: problem 67 */
#include "common.h"

#define ROWS 100
#define TRI (ROWS*ROWS)

int tri[TRI];

void euler67(void);

int main(int argc, char** argv) {
	timer(euler67);
	return 0;
}

void euler67(void) {
	FILE* f;

	f = fopen("triangle.txt", "r");

	if (!f) return;

	char line[ROWS * 5] = {0};

	for (int i = 0; i < ROWS; ++i) {
		fgets(line, ROWS * 5, f);

		char* cur = strtok(line, " ");
		int ind = 0;

		do {
			tri[ROWS * i + ind++] = strtol(cur, NULL, 10);
		} while ((cur = strtok(NULL, " ")));
	}

	/* now, we proceed to combine the lower rows and build our way up to the top. */

	for (int r = ROWS - 2; r >= 0; --r) {
		for (int i = 0; i < r + 1; ++i) {
			/* we proceed for each element in the row, and replace it with the maximum path to its two children */
			tri[r * ROWS + i] += max(tri[(r+1)*ROWS+i],tri[(r+1)*ROWS+i+1]);
		}
	}

	printf("max: %d\n", *tri);
}
