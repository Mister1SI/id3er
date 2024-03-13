#include <stdio.h>
#include <sys/io.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "../h/v1.h"

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
	void* filemap = mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if(filemap == MAP_FAILED) {
		puts("Failed mapping");
		return 3;
	}
	close(fd);
	
	char* pv1data = filemap + filesize - 128;
	v1read(pv1data);

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
	"1 argument:	List data\n"
	"2 arguments	Modify a field:\n"
	"\tt...Title\n"
	"\ta...Artist\n"
	"\tl...Album\n"
	"\ty...Year\n"
	"\tc...Comment\n"
	);
}

