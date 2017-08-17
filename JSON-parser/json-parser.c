#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *key;
	void *value;
	char type;
	/* Sensible à la casse. b: booléen, d: double, f: réel, i: entier, j: JSON, l: long, s: chaîne
	 * L'équivalent en majuscule correspond à un tableau de ce type.
	 */
} JSON_element;

typedef struct {
	JSON_element *data;
	size_t size;
} JSON;


void put(JSON *json, const char *key, void *val);

void* get(const JSON *json, const char *key);

void str(const JSON *json, char *dest) {
	*dest = '{';
	int i;
	JSON_element *el = json->data;
	while(el) {
		char *elstr;
		char *s;
		switch(el->type) {
			case 'b':
				sprintf(elstr, ",\"%s\":%s", el->key, (*(int*)el->value) ? "true" : "false");
				break;
			case 'd':
				sprintf(elstr, ",\"%s\":%d", el->key, *(double*)el->value);
				break;
			case 'f':
				sprintf(elstr, ",\"%s\":%f", el->key, *(float*)el->value);
				break;
			case 'i':
				sprintf(elstr, ",\"%s\":%i", el->key, *(int*)el->value);
				break;
			case 'j':
				str((JSON*)el->value, s);
				sprintf(elstr, ",\"%s\":%s", el->key, s);
				break;
			case 'l':
				sprintf(elstr, ",\"%s\":%li", el->key, *(long*)el->value);
				break;
			case 's':
				sprintf(elstr, ",\"%s\":\"%s\"", el->key, (char*)el->value);
				break;
			case 'B':
				break;
			case 'D':
				break;
			case 'F':
				break;
			case 'I':
				break;
			case 'J':
				break;
			case 'L':
				break;
			case 'S':
				break;
			default:
				break;
		}
	printf("coucou\n");
		strcat(dest, elstr);
		el++;
	}
	*++dest = '}';
}


JSON* parse(char *src, const int len);

void to_json(JSON *json, char *types, ...) {
	int n = strlen(types);
	json->data[n];

	va_list args;
	va_start(args, types);
	int i = 0;
	while(i < n) {
		char *key = va_arg(args, char*);
		void *val = va_arg(args, void*);
		char type = types[i];
		
		if(type) {
			JSON_element el;
			el.key = key;
			el.value = val;
			el.type = type;
			json->data[i] = el;
		}
		++i;
	}

	va_end(args);
	json->size = n;
}


int main() {
	JSON j;
	to_json(&j, "ssi", "nom", "Dupond", "prenom", "Jean", "age", 42);
	char s[64];

	str(&j, s);
	printf("%s\n", s);

	return 0;
}

