/* project euler: problem 44 */
#include "common.h"

#define PCACHECAP 100000000
#define PCAP 8000
#define GCAP 8000

unsigned long p[PCAP];
void genp(void);

int pcache[PCACHECAP] = {0};

void iterp(void);
void euler44(void);

int main(int argc, char** argv) {
	timer(euler44);
	return 0;
}

void euler44(void) {
	genp();
	iterp();
}

void genp(void) {
	printf("generating pentagonal cache\n");
	for (unsigned i = 1; i <= PCAP; ++i) {
		p[i] = (i * (3 * i - 1)) / 2;
		printf("p[%u] = %lu\n", i, p[i]);
		if (p[i] >= PCACHECAP) {
			printf("pcache overflow\n");
			return;
		}
		pcache[p[i]] = 1;
	}
	printf("done\n");
}

void iterp(void) {
	for (unsigned i = 1; i <= GCAP - 1; ++i) {
		for (unsigned j = i + 1; j <= GCAP; ++j) {
			if (p[i] + p[j] >= PCACHECAP) {
				printf("pcache read overflow\n");
				return;
			}
			unsigned long large = max(p[i], p[j]), small = min(p[i], p[j]);
			if (pcache[p[i] + p[j]] && pcache[large - small]) {
				printf("match: %lu - %lu (%lu) and %lu + %lu (%lu) are pentagonal\n", large, small, large - small, p[i], p[j], p[i] + p[j]);
			}
		}
	}
}
