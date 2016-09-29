#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#define min(x, y) ((x < y) ? x : y)
#define max(x, y) ((x > y) ? x : y)

static void timer(void (*callback)(void)) {
	clock_t start = clock(), end;
	callback();
	end = clock();

	printf("finished executing fptr %lx in %.2f milliseconds of CPU time\n", (unsigned long) callback, (float) (end - start) / ((float) CLOCKS_PER_SEC / 1000.0f));
}
