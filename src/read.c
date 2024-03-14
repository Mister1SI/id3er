#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void id3read(char* pv1start, char* filename, int lfilename) {
	char* last_line = malloc(53);
	*last_line = '\n';
	*(last_line + 52) = '\n';
	if(lfilename <= 50) {
		memcpy(last_line + 1, filename, lfilename);
		for(int i = lfilename + 1; i < 51; i++) {
			*(last_line + i) = '-';
		}
	} else {
		memcpy(last_line + 1, filename, 47);
		memcpy(last_line + 48, "...", 3);
	}
	
	if(0 != strncmp(pv1start, "TAG", 3)) {
		write(1, "ID3v1 Info----------------------------------------\n", 51);
		write(1, "\tNo ID3v1 tag found.", 20);
		write(1, last_line, 53);
		return;
	}

	write(1, "ID3v1 Info----------------------------------------\n", 51);
	write(1, "\tTitle:\t\t", 9);
	write(1, pv1start + 3, 30);
	write(1, "\n\tArtist:\t\t", 11);
	write(1, pv1start + 33, 30);
	write(1, "\n\tAlbum:\t\t", 10);
	write(1, pv1start + 63, 30);
	write(1, "\n\tYear:\t\t", 9);
	write(1, pv1start + 93, 4);
	write(1, "\n\tComment:\t", 11);
	write(1, pv1start + 97, 30);
	write(1, last_line, 53);

	free(last_line);
}
