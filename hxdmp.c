#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	FILE* stream;
	char row[16];
	int i;
	int j;
	int current_line = 0;
	char c;

	if (argc > 1) stream = fopen(argv[1], "rb");
	else stream = stdin;

	i = 0;

	printf("       00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");

	for (;;) {
		c = fgetc(stream);

		if (feof(stream)) break;

		row[i] = c;

		if (i == 15) {
			printf("%06x ", current_line * 0x10);

			for (j = 0; j < 16; j++) {
				printf("%02x", row[j]);

				if (j + 1 < 16)
					printf(" ");
			}

			printf(" |");

			for (j = 0; j < 16; j++) {
				if (isspace(row[j]) && !(row[j] == ' ')) putchar('.');
				else putchar(row[j]);
			}

			printf("|\n");

			i = -1;
			current_line++;
		}

		i++;
	}

	if (i > 0) {
	printf("%06x ", current_line);

	for (j = 0; j < 16; j++) {
		if (j < i) printf("%02x", row[j]);
		else printf("  ");

		if (j + 1 < 16) printf(" ");
	}

	printf(" |");

	for (j = 0; j < 16; j++) {
		if (j < i)
			if (isspace(row[j])) putchar('.');
			else putchar(row[j]);
		else putchar(' ');
	}

	printf("|\n");
	}

	if (stream != stdin) fclose(stream);
	return 0;
}
