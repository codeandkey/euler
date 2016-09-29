/* project euler: problem 43 */
#include "common.h"

#define TEST 14063572

void gen_10perm(void (*callback)(char* s));
void callback(char* c);
void euler43(void);

unsigned long sum = 0;

int main(int argc, char** argv) {
	timer(euler43);
	return 0;
}

void euler43(void) {
	gen_lex("0123456789", 10, callback);
	printf("sum: %lu\n", sum);
}

void callback(char* c) {
	char buf[4] = {0};
	int primes[] = {2, 3, 5, 7, 11, 13, 17};
	for (unsigned i = 1; i <= 7; ++i) {
		memcpy(buf, c + i, 3);
		if (strtol(buf, NULL, 10) % primes[i - 1]) return;
	}
	printf("PASS: %s\n", c);
	sum += strtol(c, NULL, 0);
}
