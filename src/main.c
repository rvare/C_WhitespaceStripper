#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define DOUBLE_QUOTECHAR '\"'
#define SINGLE_QUOTECHAR '\''

void process_string(char, FILE *);

int main(int argc, char *argv[]) {
	FILE *file_ptr = NULL;
	char token;

	if (argc == 1) {
		fprintf(stderr, "ERROR with command arguments: No file given\n");
		return 1;
	}

	file_ptr = fopen(argv[1], "r");
	if (file_ptr == NULL) {
		perror("ERROR opening file");
		return 1;
	}
	
	while ((token=fgetc(file_ptr)) != EOF) {
		if (isspace(token))
			continue;
		else if (token == SINGLE_QUOTECHAR || token == DOUBLE_QUOTECHAR) {
			putchar(token);
			process_string(token, file_ptr);
		}
		else
			putchar(token);
	}

	if (ferror(file_ptr))
		perror("ERROR with file");

	fclose(file_ptr);

	return 0;
}

/*
Purpose: Handles the case when double quotation mark is encountered.
Precondition: token is a double quotation mark.
Postcondition: A closing double quotation marks has been encountered.
Invarient: None
*/
void process_string(char terminate_quote, FILE *file_ptr) {
	int token;
	bool escape_flag = false;

	while ((token=fgetc(file_ptr)) != terminate_quote || escape_flag == true) {
		if (feof(file_ptr) || token == EOF)
			return;
		escape_flag = token == '\\' ? true : false;
		putchar(token);
	}
	putchar(token); // Print the last quote symbol
}
