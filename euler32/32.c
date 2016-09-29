#include <stdlib.h>
#include <stdio.h>
#include <math.h>

char digits[] = "123456789";
const int num_digits = 9;

void gen_lex_order(char* str, void (*callback)(char* str));
int contains(char* str, char c);
int contains_len(char* str, int len, char c);
int is_permutation(char* str, char* digits);

void callback_prt(char* str);

int main(int argc, char** argv) {
	char product[10] = "123456789";
	gen_lex_order(product, callback_prt);

	return 0;
}

void callback_prt(char* str) {
	printf("permutation: %s\n", str);
	unsigned long perm_value = strtol(str, NULL, 10);

	char ff[4] = {0};
	memcpy(ff, str, 4);

	char sf[4] = {0};
	memcpy(sf, str + 4, 4);

	char ld = str[8];

	char st[3] = {0};
	memcpy(st, str + 4, 3);

	char lt[2] = {0};
	memcpy(lt, str + 7, 2);

	unsigned ff_value = strtol(ff, NULL, 10);
	unsigned sf_value = strtol(sf, NULL, 10);
	int ld_value = ld - '0';

	if (ff_value == sf_value * ld_value) {
		printf("match: %d * %d = %d (%s)\n", sf_value, ld_value, ff_value, str);
	}

	unsigned st_value = strtol(st, NULL, 10);
	unsigned lt_value = strtol(lt, NULL, 10);

	if (ff_value == st_value * lt_value) {
		printf("match: %d * %d = %d (%s)\n", st_value, lt_value, ff_value, str);
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

int contains(char* str, char c) {
	while (*str) {
		if (*(str++) == c) return 1;
	}

	return 0;
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
