#include <stdio.h>

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
	
	return 0;
}

void help() {
	puts(
	"Help menu"
	);
}

