#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void process_string(char token);

int main(int argc, char *argv[]) {
	char token;
	
	while ((token =  getchar()) != EOF) {
		if (isspace(token))
			continue;
		else if (token == '"')
			process_string(token);
		else
			putchar(token);
	}

	return EXIT_SUCCESS;
}

void process_string(char token) {
	do
		putchar(token);
	while ((token = getchar()) != '"');
	putchar(token); // Print the last quote symbol
}
