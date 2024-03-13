#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int v1read(char* pstart, char* filename, int lfilename) {
	if(0 != strncmp(pstart, "TAG", 3))
		return 0;

	char* last_line = malloc(52);
	*last_line = '\n';
	*(last_line + 51) = '\n';
	if(lfilename <= 50) {
		memcpy(last_line + 1, filename, lfilename);
		for(int i = lfilename + 1; i < 50; i++) {
			*(last_line + i) = '-';
		}
	} else {
		memcpy(last_line + 1, filename, 47);
		memcpy(last_line + 48, "...", 3);
	}

	write(1, "ID3v1 Info----------------------------------------\n", 51);
	write(1, "\tTitle:\t\t", 9);
	write(1, pstart + 3, 30);
	write(1, "\n\tArtist:\t\t", 11);
	write(1, pstart + 33, 30);
	write(1, "\n\tAlbum:\t\t", 10);
	write(1, pstart + 63, 30);
	write(1, "\n\tYear:\t\t", 9);
	write(1, pstart + 93, 4);
	write(1, "\n\tComment:\t", 11);
	write(1, pstart + 97, 30);
	write(1, last_line, 52);

	free(last_line);
	return 1;
}

