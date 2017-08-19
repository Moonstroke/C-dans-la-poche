#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void df(char*);

int main(int argc, char **argv) {
	char str[80];

	if(argc == 1) {
		printf(">> ");
		scanf("%80s", str);
		df(str);
	} else {
		int i = 0;
		while(++i < argc) {
			df(argv[i]);
		}
	}
}

void df(char *s) {
	uint8_t x = 0;
	char c;
	while(c = *s++) {
		if(c == 'i')
			x++;
		else if(c == 'd')
			x--;
		else if(c == 's')
			x *= x;
		else if(c == 'o')
			printf("%d\n", x);
		else printf("\n");
	}
}
