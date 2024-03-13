#include <stdio.h>
#include <string.h>
#include <sys/io.h>
#include <unistd.h>
void v1edit(char* dest, char* src, int n, char* field, int lfield) {
	printf("Enter new ");
	fflush(stdout);
	write(1, field, lfield);
	printf(": ");
	fflush(stdout);

	char buf[30];
	read(0, buf, 30);
	memcpy(dest, src, n);

}

