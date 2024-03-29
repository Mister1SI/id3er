#include <stdio.h>
#include <sys/io.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "../h/id3.h"

void help();

int main(int argc, char** argv) {
	int edit_mode;
	char* filename;
	char field;
	switch(argc) {
		case 1:
			help();
			return 0;
		case 2:
			edit_mode = 0;
			filename = argv[1];
			break;
		case 3:
			edit_mode = 1;
			filename = argv[1];
			field = argv[2][0];
			break;
		default:
			puts("Incorrect number of arguments");
			help();
			return 1;
	}
	
	// Open and map the file
	int fd = open(filename, O_RDWR);
	if(fd == -1) {
		puts("Failed to open file");
		return 2;
	}
	struct stat st;
	fstat(fd, &st);
	long filesize = st.st_size;
	void* filemap = mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(filemap == MAP_FAILED) {
		puts("Failed mapping");
		return 3;
	}
	
	char* pv1data = filemap + (filesize - 128);
	id3read(pv1data, filemap, filename, strlen(filename));

	if(edit_mode == 1) {
		switch(field) {
			case 't':
				id3edit(pv1data+3, 30, "title", 5);
				break;
			case 'a':
				id3edit(pv1data+33, 30, "artist", 6);
				break;
			case 'l':
				id3edit(pv1data+63, 30, "album", 5);
				break;
			case 'y':
				id3edit(pv1data+93, 30, "year", 4);
				break;
			case 'c':
				id3edit(pv1data+97, 30, "comment", 7);
				break;
			default:
				puts("Unknown field.");
				return 1;
		}
	}

	munmap(filemap, filesize);
	return 0;
}

void help() {
	puts(
	"id3er: an id3 reader and editor\n"
	"usage:\n"
	"\tid3er\n"
	"\tid3er	<filename>\n"
	"\tid3er	<filename>	[t a l y c]\n\n"
	"0 arguments:	Show help\n"
	"1 argument:	List data\n"
	"2 arguments:	Modify a field:\n"
	"\tt...Title\n"
	"\ta...Artist\n"
	"\tl...Album\n"
	"\ty...Year\n"
	"\tc...Comment\n"
	);
}



