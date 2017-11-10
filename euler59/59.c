/* project euler: problem 59 */
#include "common.h"

void euler59(void);

int main(int argc, char** argv) {
	timer(euler59);
	return 0;
}

void euler59(void) {
	FILE* f = fopen("cipher.txt", "r");

	if (!f) return;
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

	char buf[size], *s = NULL;
	fread(buf, size, 1, f);
	fclose(f);

	char* data = malloc(2);
	int data_len = 1;

	data[0] = strtol(strtok(buf, ","), NULL, 0);
	data[1] = 0;

	while ((s = strtok(NULL, ","))) {
		int byte = strtol(s, NULL, 10);

		data = realloc(data, ++data_len + 1);
		data[data_len - 1] = byte;
		data[data_len] = 0;
	}

	printf("parsed %d bytes\n", data_len);
	printf("grinding keys\n");

	for (char a = 'a'; a <= 'z'; ++a) {
	for (char b = 'b'; b <= 'z'; ++b) {
	for (char c = 'c'; c <= 'z'; ++c) {
		int cnt = 0, arr[3] = {a, b, c};
		printf("%c%c%c:", a, b, c);
		for (int i = 0; i < data_len; ++i) {
			int p = (data[i] ^ arr[cnt++ % 3]);
			printf("%c", isprint(p) ? p : '.');
		}
		printf("\n--\n");
	}
	}
	}

	/* after analysis the key is 'god' */

	int a = 'g', b = 'o', c = 'd';
	int cnt = 0, arr[3] = {a, b, c}, sum = 0;
	printf("%c%c%c:", a, b, c);
	for (int i = 0; i < data_len; ++i) {
		int p = (data[i] ^ arr[cnt++ % 3]);
		printf("%c", isprint(p) ? p : '.');
		sum += p;
	}
	printf("\n--\n");
	printf("final sum: %d\n", sum);

	free(data);
}
