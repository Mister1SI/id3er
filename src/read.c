#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void id3read(char* pv1start, char* pv2start, char* filename, int lfilename) {
	char* filename_line = malloc(53);
	*filename_line = '\n';
	*(filename_line + 52) = '\n';
	if(lfilename <= 50) {
		memcpy(filename_line + 1, filename, lfilename);
		for(int i = lfilename + 1; i < 51; i++) {
			*(filename_line + i) = '-';
		}
	} else {
		memcpy(filename_line + 1, filename, 47);
		memcpy(filename_line + 48, "...", 3);
	}
	
	write(1, "ID3v1 Info----------------------------------------\n", 51);
	if(0 != strncmp(pv1start, "TAG", 3)) {
		write(1, "\tNo ID3v1 tag found.", 20);
		write(1, filename_line, 53);
		return;
	}
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
	
	write(1, "\nID3v2 Info----------------------------------------\n", 52);
	write(1, "\tNo ID3v2 tag found.", 20);

	write(1, filename_line, 53);

	free(filename_line);
}

