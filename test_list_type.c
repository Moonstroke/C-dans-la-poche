#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct int_list {
	int capacity;
	int _size;
	int *data;
};


void new(struct int_list* l, const int nb) {
	l->capacity = nb;
	l->_size = 0;
	l->data = calloc(nb, sizeof(nb));
}

int append(struct int_list *l, const int n) {
	if(l->_size > l->capacity) {
		l->data = realloc(l->data, l->capacity * 2 * sizeof(int));
	}
	*(l->data + l->_size) = n;
	return ++l->_size;
}

int get(const struct int_list *l, const int i) {
	return l->data[i];
}

int size(const struct int_list *l) {
	return l->_size;
}

int* to_int_array(const struct int_list *l) {
	return l->data;
}

void print(const struct int_list *l) {
	printf("[%i", *l->data);
	int *i = l->data;
	//char *el;
	while(*++i) {
		printf(", %i", *i);
	}
	printf("%c", ']');
}

char* str(const struct int_list* l) {
	char *s = malloc(64 * sizeof(char));
	sprintf(s, "[%i", *l->data);
	int *i = l->data;
	char *el = malloc(5 * sizeof(char));
	while(*++i) {
		sprintf(el, ", %i", *i);
		strcat(s, el);
	}
	strcat(s, "]");
	free(el);

	return s;
}


int main(int argc, char *argv[]) {
	if(argc == 1) {
		fprintf(stderr, "USAGE: %s ARGS...\nWhere ARGS will be the elements inserted in the list\nInvalid integers => 0\n", argv[0]);
		return 1;
	}
	struct int_list l;
	new(&l, argc - 1);

	char **a = argv;
	int n;
	while(*++a) {
		sscanf(*a, "%d", &n);
		append(&l, n);
	}
	char *s = str(&l);
	printf("str() =   \"%s\"\n", s);
	printf("print() = \"");
	print(&l);
	printf("\"\n");
	return 0;
}

