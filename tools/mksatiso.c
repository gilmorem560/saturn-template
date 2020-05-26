#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int ret_val = EXIT_SUCCESS;
	FILE *iso = NULL;
	FILE *header = NULL;
	unsigned char *buffer = NULL;
	long header_size = 0;
	size_t read_size = 0;
	
	/* invalid command line */
	if (argc != 3) {
		fputs("mksatiso <file.iso> <header.bin>\n", stderr);
		return EXIT_FAILURE;
	}
	
	/* open iso */
	iso = fopen(argv[1], "r+b");
		if (iso == NULL) {
			fprintf(stderr, "mksatiso: could not open %s\n", argv[1]);
			return EXIT_FAILURE;
		}
		
	/* open header (typically ip.bin) */
	header = fopen(argv[2], "rb");
		if (header == NULL) {
			fclose(iso);
			fprintf(stderr, "mksatiso: could not open %s\n", argv[2]);
			return EXIT_FAILURE;
		}
		
	/* determine header length */
	fseek(header, 0, SEEK_END);
	header_size = ftell(header);
	
	/* overwrite iso header */
	if (header_size > 0) {
		fseek(header, 0, SEEK_SET);
		buffer = malloc(header_size);
		read_size = fread(buffer, sizeof (char), header_size, header);
		if (read_size != header_size) {
			fprintf(stderr, "mksatiso: header read error\n");
			ret_val = EXIT_FAILURE;
		}
		read_size = fwrite(buffer, sizeof (char), header_size, iso);
		if ((ret_val == EXIT_SUCCESS) && (read_size != header_size)) {
			fprintf(stderr, "mksatiso: iso write error\n");
			ret_val = EXIT_FAILURE;
		}
		free(buffer);
	}
	
	/* tidy up */
	fclose(header);
	fclose(iso);
	return ret_val;
}
