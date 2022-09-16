#include <stdio.h>
#include <stdlib.h>

int is_printable(char c) {
	return (c >= 32) && (c <= 126);
}

void print_row(char row[16], int i, int current_line) {
	int j;

	printf("%08x | ", current_line * 0x10);

	for (j = 0; j < 16; j++) {
		if (j < i) printf("%02x", (unsigned char) row[j]);
		else printf("  ");

		if (j + 1 < 16) printf(" ");
	}

	printf(" |");

	for (j = 0; j < 16; j++) {
		if (j < i)
			if (is_printable(row[j])) putchar(row[j]);
			else putchar('.');
		else putchar(' ');
	}

	printf("|\n");
}

int main(int argc, char* argv[]) {
	FILE* stream;
	char row[16];
	int i;
	int j;
	int current_line = 0;
	char c;

	if (argc > 1) stream = fopen(argv[1], "rb");
	else stream = stdin;

	if (stream == NULL) return 0;

	i = 0;

	printf("           00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
	printf("         +-------------------------------------------------+----------------+\n");

	for (;;) {
		c = fgetc(stream);

		if (feof(stream)) break;

		row[i] = c;

		if (i == 15) {
			print_row(row, i + 1, current_line);

			i = -1;
			current_line++;
		}

		i++;
	}

	if (i > 0) {
		print_row(row, i, current_line);
	}

	if (stream != stdin) fclose(stream);
	return 0;
}
