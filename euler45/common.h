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

int contains_len(char* str, int len, char c) {
	printf("checking %.*s for containing %c\n", len, str, c);

	for (int i = 0; i < len; ++i) {
		if (str[i] == c) {
			printf("located %c at pos %d\n", c, i);
			return 1;
		}
	}

	printf("didn't find %c\n", c);
	return 0;
}

void gen_lex_order(char* str, void (*callback)(char* str)) {
	int len = strlen(str);

	callback(str); /* assume the arg. passed is the lowest perm */

	while (1) { /* inf. loop to do this */
		printf("starting left process on %s\n", str);

		/* <- left process */
		int inc_success = -1; /* -1 indicates failure; */
		for (int i = len - 1; i >= 0 && (inc_success < 0); --i) {
			printf("moving left, considering %c [j starts %c]\n", str[i], str[i] + 1);
			for (int j = str[i] + 1; j <= '9'; ++j) {
				printf("testing %c for availabiliy\n", j);
				if (!contains_len(str, i, j)) { /* check from 0 -> i not including str[i] */
					printf("found available digit %c\n", j);
					/* str doesn't contain an available digit -- we use it */
					str[i] = j;
					inc_success = i; /* don't forget */
					break;
				}
			}
		}

		if (inc_success >= 0) {
			printf("starting right process on %s [increment occurred at digit %d]\n", str, inc_success + 1);

			/* we incremented something, move back right (starting where < left off) */
			for (int i = inc_success + 1; i < len; ++i) {
				printf("moving right, considering %c\n", str[i]);
				for (int j = '1'; j <= '9'; ++j) {
					if (!contains_len(str, i, j)) { /* i is used to ensure 0..(cur - 1) is included in the condition (everything before the cur) */
						printf("found available low digit %c\n", j);
						/* the smallest available digit is located by considering taken digits (0->i) and inverting the set */
						/* walk in a upwards motion and grab the first one */
						str[i] = j;
						break;
					}
				}
			}
			/* there is no confirmation that anything was reset to the right afterwards, and there is no need for any */
			callback(str);
		} else {
			printf("no increment ever happened, terminating\n");

			/* could not successfully increment any digits -- this is the last perm */
			break;
		}
	}
}

int is_permutation(char* str, char* digits) {
	int* digit_test = malloc(strlen(digits));
	for (int i = 0; i < strlen(digits); ++i) {
		digit_test[i] = 0;
	}
	for (int i = 0; i < strlen(str); ++i) {
		for (int j = 0; j < strlen(digits); ++j) {
			if (str[i] == digits[j]) {
				if (digit_test[i]) {
					return 0;
				}

				digit_test[i] = 1;
			}
		}
	}
	for (int i = 0; i < strlen(digits); ++i) {
		if (!digit_test[i]) {
			return 0;
		}
	}
	return 1;
}
