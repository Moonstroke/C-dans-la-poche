#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


int usage(const char *argv0) {
	fprintf(stderr, "\nUSAGE: %s: [M]-[N] [ (-- | INT_M...) ]\n", argv0);
	fprintf(stderr, "Converts all INT_M values from base M to base N (M, N in range [2, 36])\n\n");
	fprintf(stderr, "Example:\n\t$ %s 10-7 42\n\t60\n\n", argv0);
	fprintf(stderr, "If INT_M is `--', values are read from standard input.\n");
	fprintf(stderr, "If either M or N is omitted, default value is base 10:\n");
	fprintf(stderr, "\t%s -7 42\n", argv0);
	fprintf(stderr, "is equivalent to the example above.\n");

	return 1;
}

void bases(const char arg[], uint8_t *basein, uint8_t *baseout) {
	// TODO voir pour scanf ?
	char *sep = strchr(arg, '-');
	*basein = sep > arg ? (uint8_t)strtoul(arg, &sep, 10) : 10;
	*baseout = *(sep + 1) ? (uint8_t)strtoul(sep + 1, NULL, 10) : 10;
}


void conv_aff(char *entree, const int de, const int vers, const char *chiffres) {

	long x = 0, _x;
	char *ch, sortie[64], *ch1 = sortie, _c;
	if(*entree == '-') {
		ch = entree + 1;
		do {
			x = x * de - (*ch & 15);
		} while(*++ch);
	} else {
		ch = entree;
		do {
			x = x * de + (*ch & 15);
		} while(*++ch);
	}

	// d'après http://stackoverflow.com/a/23840699/6337519
	ch = sortie;
	do {
		_x = x;
		x /= vers; // nécessaire avant `value * base` for integer rounding
		int i = 35 + _x - x * vers;
		*ch++ = chiffres[i];
	} while(x);
	// ici la chaîne de caractères est à l'envers, il faut inverser tous les caractères

	// Application de (l'éventuel) signe -
	if (_x < 0) *ch++ = '-';
	*ch-- = '\0';
	while (ch1 < ch) {
		_c = *ch;
		*ch-- = *ch1;
		*ch1++ = _c;
	}

	printf("%s\n", sortie); 
}

int main(const int argc, char *argv[]) {
	if(argc < 3)
		return usage(argv[0]);
	else {
		const char *chiffres = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz";
		uint8_t m, n;
		bases(argv[1], &m, &n);
		if(m < 2 || m > 36 || n < 2 || n > 36)
			return usage(argv[0]);

		if(!strcmp(argv[2], "--")) { //lire l'entrée standard
			char inp[64];
			while(scanf("%s", inp)) // on ne peut pas utiliser "%li" parce que `inp` n'est pas forcément en base 10
				conv_aff(inp, m, n, chiffres);
		} else
			for(int i = 2; i < argc; i++)
				conv_aff(argv[i], m, n, chiffres);
	}
	return 0;
}
