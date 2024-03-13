#include <stdio.h>
#include <unistd.h>
#include <string.h>


int v1read(char* pstart) {
	if(0 != strncmp(pstart, "TAG", 3))
		return 0;

	write(1, "ID3v1 Info:		-----------------------\n", 38);
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
	write(1, "\n---------------------------------------\n", 41);
	return 1;
}

