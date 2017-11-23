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

#define PRIME_CACHE_SIZE 1000000
static int prime_cache[PRIME_CACHE_SIZE] = {0};

static void timer(void (*callback)(void)) {
	clock_t start = clock(), end;
	callback();
	end = clock();

	printf("finished executing fptr %lx in %.2f milliseconds of CPU time\n", (unsigned long) callback, (float) (end - start) / ((float) CLOCKS_PER_SEC / 1000.0f));
}

int contains_len(char* str, int len, char c) {
	for (int i = 0; i < len; ++i) {
		if (str[i] == c) {
			return 1;
		}
	}
	return 0;
}

/* digits are treated by value, please order least to most significant */
void gen_lex(char* digits, int len, void (*callback)(char* str)) {
	char* output_buf = malloc(len + 1);
	memcpy(output_buf, digits, len);

	callback(output_buf);

	while (1) { /* inf. loop to do this */
		/* <- left process */
		int inc_success = -1; /* -1 indicates failure; */
		for (int i = len - 1; i >= 0 && (inc_success < 0); --i) {
			for (int j = output_buf[i] + 1; j <= digits[strlen(digits) - 1]; ++j) {
				if (!contains_len(output_buf, i, j)) { /* check from 0 -> i not including str[i] */
					/* str doesn't contain an available digit -- we use it */
					output_buf[i] = j;
					inc_success = i; /* don't forget */
					break;
				}
			}
		}

		if (inc_success >= 0) {
			/* we incremented something, move back right (starting where < left off) */
			for (int i = inc_success + 1; i < len; ++i) {
				for (int j = *digits; j <= digits[strlen(digits) - 1]; ++j) {
					if (!contains_len(output_buf, i, j)) { /* i is used to ensure 0..(cur - 1) is included in the condition (everything before the cur) */
						/* the smallest available digit is located by considering taken digits (0->i) and inverting the set */
						/* walk in a upwards motion and grab the first one */
						output_buf[i] = j;
						break;
					}
				}
			}
			/* there is no confirmation that anything was reset to the right afterwards, and there is no need for any */
			callback(output_buf);
		} else {
			/* could not successfully increment any digits -- this is the last perm */
			break;
		}
	}
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
					free(digit_test);
					return 0;
				}

				digit_test[i] = 1;
			}
		}
	}
	for (int i = 0; i < strlen(digits); ++i) {
		if (!digit_test[i]) {
			free(digit_test);
			return 0;
		}
	}
	free(digit_test);
	return 1;
}

void foreach_digit(unsigned long a, void* data, void (*callback)(void* data, unsigned dig)) {
	while (a >= 1) {
		callback(data, a % 10);
		a /= 10;
	}
}

void _num_is_perm_of_cb_a(void* data, unsigned dig) {
	int* adig = (int*) data;
	adig[dig] += 1;
}

void _num_is_perm_of_cb_b(void* data, unsigned dig) {
	int* adig = (int*) data;
	adig[dig] -= 1;
}

int num_is_perm_of(unsigned long a, unsigned long b) {
	int dig[9] = {0};
	foreach_digit(a, dig, _num_is_perm_of_cb_a);
	foreach_digit(b, dig, _num_is_perm_of_cb_b);
	for (int i = 0; i < sizeof dig / sizeof *dig; ++i) {
		if (dig[i]) return 0;
	}
	return 1;
}

int is_prime(long n) {
	if (n <= 1) return 0;
	if (n <= 3) return 1;
	if (!(n % 2)) return 0;

	if (n < PRIME_CACHE_SIZE && prime_cache[n]) {
		return prime_cache[n] - 1;
	}

	for (unsigned long i = 3; i <= ceil(sqrt(n)); i += 2) {
		if (!(n % i)) {
			if (n < PRIME_CACHE_SIZE) {
				prime_cache[n] = 1;
			}

			return 0;
		}
	}

	if (n < PRIME_CACHE_SIZE) {
		prime_cache[n] = 2;
	}

	return 1;
}

void num_perm(unsigned long n, void (*callback)(unsigned long n)) {
}
