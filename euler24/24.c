/* euler 24 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

unsigned long rank(char* i);
unsigned long fac(unsigned long i);

int main(int argc, char** argv) {
	if (argc < 2) return -1;
	printf("rank of %s: %d\n", argv[1], rank(argv[1]));
	return 0;
}

unsigned long rank(char* i) {
	unsigned int digits = strlen(i);
	unsigned int orank = 0;

	printf("digits: %d\n", digits);

	char tmpstr[2] = {0};

	for (int d = 0; d < digits; ++d) {
		*tmpstr = i[d];
		orank += strtol(tmpstr, NULL, 10) * fac(digits - (d + 1));

		for (int j = d + 1; j < digits; ++j) {
			if (i[j] > i[d]) --i[j];
		}
	}

	return orank + 1;
}

unsigned long fac(unsigned long i) {
	if (i <= 0) return 1;
	unsigned long out = i;
	for (unsigned long a = i - 1; a; --a) out *= a;
	printf("out: %d\n", i);
	return out;
}
