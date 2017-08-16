#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strcmp

#define MAXLEN 80

/* 4 for field name "data", 1 for "=" */
#define EXTRA 5

/* 1 for added line break, 1 for trailing NUL */
#define MAXINPUT MAXLEN + EXTRA + 2


int escape(char *src, char *dest) {
	if(!src || !dest)
		return 0;
	int i = 0;
	for(; *src; src++, dest++)
		switch(*src) {
			case '&':
				*dest = '&';
				*++dest = 'a';
				*++dest = 'm';
				*++dest = 'p';
				*++dest = ';';
				++i;
				break;
			case '<':
				*dest = '&';
				*++dest = 'l';
				*++dest = 't';
				*++dest = ';';
				i++;
				break;
			case '>':
				*dest = '&';
				*++dest = 'g';
				*++dest = 't';
				*++dest = ';';
				i++;
				break;
			default:
				*dest = *src;
		}
	*++dest = '\0';
	return i;
}

void urldecode(char *src, const char *end, char *dest) {
	for(; src != end; src++, dest++) {
		if(*src == '+')
			*dest = ' ';
		else if(*src == '%') {
			int code;
			if(sscanf(src + 1, "%2x", &code) != 1) code = '?';
			*dest = code;
			src += 2;
		}
		else
			*dest = *src;
	}
	*dest = '\n';
	*++dest = '\0';
}

int main() {
	char *lang = "en", *charset = "UTF-8", *method, *lenstr, input[MAXINPUT], data[MAXINPUT];
	long len;


	printf("<!DOCTYPE html>");
	printf("<html lang=\"%s\">", lang);
	printf("<head>");
	printf("<meta charset=\"%s\"/>", charset);

	method = getenv("REQUEST_METHOD");
	if(!method) {
		printf("<title>Method not found</title>");
		printf("</head>");

		printf("<p>ERROR: the request method could not be found. Make sure you have the <code>REQUEST_METHOD</code> environment variable set to a non-null value</p>");
	} else if(!strcmp(method, "GET")) {
		printf("<title>Form</title>");
		printf("</head>");

		printf("<body>");
		printf("<h1>My CGI C page</h1>");
		printf("<form method=\"POST\"><label for=\"data\">Enter data here</label>");
		printf("<input type=\"text\" name=\"data\" id=\"data\" maxlength=\"%i\"/>", MAXLEN);
		printf("</form>");
	} else if(!strcmp(method, "POST")) {
		printf("<title>Response</title>");
		printf("</head>");

		printf("<body>");
		lenstr = getenv("CONTENT_LENGTH");
		if(lenstr == NULL || sscanf(lenstr, "%ld", &len) != 1) {
			printf("<p>WARNING: the content length could not be retrieved succesfully. Make sure you have the <code>CONTENT_LENGTH</code> env var set to a non-null value</p>");
			len = MAXINPUT;
		} else if(len > MAXLEN) {
			len = MAXINPUT;
		}
		fgets(input, len + 1, stdin);
		urldecode(input + EXTRA, input + len, data);
		printf("<p>Your data is: <tt>%s</tt></p>", data);
	} else {
		printf("<title>Unknown method</title>");
		printf("</head>");

		printf("<body>");
		printf("<p>ERROR: The method <code>%s</code> is not suported</p>", method);
	}
	printf("</body>");
	printf("</html>\n");

	return 0;
}
