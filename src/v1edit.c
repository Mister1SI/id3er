#include <stdio.h>
#include <string.h>
#include <sys/io.h>
#include <unistd.h>
#include <stdlib.h>

void v1edit(char* dest, int n, char* field, int lfield) {
	printf("Enter new ");
	fflush(stdout);
	write(1, field, lfield);
	printf(": ");
	fflush(stdout);

	char* buf = malloc(30);
	memset(buf, 0, 30);
	read(0, buf, 30);
	memcpy(dest, buf, n);

}

