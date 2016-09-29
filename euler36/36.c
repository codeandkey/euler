#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define CAP 1000000
#define FILE_O "palindromes"
#define MAX_DIGITS 32

void to_binary(unsigned long num);
int is_pd_2(unsigned long num);

int main(int argc, char** argv) {
	FILE* f = fopen(FILE_O, "r");

	if (!f) return -1;

	char buf[10] = {0};
	unsigned out = 0;
	while (fgets(buf, 10, f)) {
		out += is_pd_2(strtol(buf, NULL, 10));
	}

	printf("RESULT: %d\n", out);
	fclose(f);
	return 0;
}

int is_pd_2(unsigned long num) {
	int digits[MAX_DIGITS] = {0};
	int digit_count;

	unsigned long cp = num;

	printf("converting %lu: ", num);

	while (num) {
		digits[digit_count++] = num & 1;
		printf("%d", digits[digit_count - 1]);
		num /= 2;
	}

	printf("\n");

	for (int i = 0; i < digit_count / 2; ++i) {
		if (i > digit_count - (i + 1)) break;

		printf("comparing %d [%d] and %d [%d]\n", digits[i], i, digits[digit_count - (i + 1)], digit_count - (i + 1));

		if (digits[i] != digits[digit_count - (i + 1)]) {
			return 0;
		}
	}

	return cp;
}
