#include <stdio.h>
#include <string.h>
#include <sys/io.h>
#include <unistd.h>
#include <stdlib.h>

void rmnl(char* s, int n) {
	for(int i = 0; i < n; i++) {
		if(s[i] == '\n')
			s[i] = 0;
	}
}

void v1edit(char* dest, int n, char* field, int lfield) {
	printf("Enter new ");
	fflush(stdout);
	write(1, field, lfield);
	printf(": ");
	fflush(stdout);

	char* buf = malloc(30);
	memset(buf, 0, 30);
	read(0, buf, 30);
	rmnl(buf, 30);
	memcpy(dest, buf, n);

}



