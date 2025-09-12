#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

#define QUOTECHAR '"'

void process_string(char, FILE *);

int main(int argc, char *argv[]) {
	FILE *file_ptr = NULL;
	char token;

	if (argc == 1) {
		fprintf(stderr, "ERROR: No file given\n");
		return 1;
	}

	file_ptr = fopen(argv[1], "r");
	if (file_ptr == NULL) {
		fprintf(stderr, "ERROR: %s\n", strerror(errno));
		return 1;
	}
	
	while ((token=fgetc(file_ptr)) != EOF) {
		if (isspace(token))
			continue;
		else if (token == QUOTECHAR)
			process_string(token, file_ptr);
		else
			putchar(token);
	}

	return EXIT_SUCCESS;
}

/*
Purpose: Handles the case when double quotation mark is encountered.
Precondition: token is a double quotation mark.
Postcondition: A closing double quotation marks has been encountered.
Invarient: None
*/
void process_string(char token, FILE *file_ptr) {
	do
		putchar(token);
	while ((token = fgetc(file_ptr)) != QUOTECHAR);
	putchar(token); // Print the last quote symbol
}
