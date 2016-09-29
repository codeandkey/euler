/* project euler problem 40 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PN_MAX 6

int get_digit_at(unsigned long pos);
int get_digit_count(unsigned long num);

int main(int argc, char** argv) {
	unsigned long product = 1;

	for (unsigned i = 0; i <= PN_MAX; ++i) {
		product *= get_digit_at((unsigned long) pow(10, i));
	}

	printf("product: %lu\n", product);
	return 0;
}

int get_digit_at(unsigned long pos) {
	/* we can trace through the digits of the constant without actually storing much of it.. at all */
	/* follow through the digits until pos is reached.. */

	unsigned long cur_num = 0;
	unsigned long cur_digit = 0;

	while (cur_digit < pos) {
		cur_digit += get_digit_count(++cur_num);
	}

	if (cur_digit > pos) {
		/* the last number didn't land exactly on pos, we must find which part of cur_num did */
		unsigned dist_from_end = cur_digit - pos; /* how many extra digits? */

		for (unsigned i = 0; i < dist_from_end; ++i) {
			cur_num /= 10; /* throw away remaining digits */
		}
	}

	return cur_num % 10; /* the last number landed exactly on the target digit -- return the last digit */
}

int get_digit_count(unsigned long num) {
	return (int) floor(log10(num)) + 1;
}
