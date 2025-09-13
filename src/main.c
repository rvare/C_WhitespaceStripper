#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define DOUBLE_QUOTECHAR	'\"'
#define SINGLE_QUOTECHAR	'\''
#define BACKSLASH_CHAR		'\\'

void process_string(char, FILE *);

int main(int argc, char *argv[]) {
	FILE *file_ptr = NULL;
	char token;
	bool escape_flag = false;

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
		else if ((token == SINGLE_QUOTECHAR || token == DOUBLE_QUOTECHAR) && escape_flag == false) {
			putchar(token);
			process_string(token, file_ptr);
		}
		else
			putchar(token);
		escape_flag = (token == BACKSLASH_CHAR) ? true : false;
	}

	if (ferror(file_ptr))
		perror("ERROR with file");

	fclose(file_ptr);

	return 0;
}

/*
Purpose: Handles the case when double quotation mark is encountered.
Precondition: token is either a single or double quotation mark.
Postcondition: A closing single or double quotation mark, not escaped, has been encountered.
Invarient: None
*/
void process_string(char terminate_quote, FILE *file_ptr) {
	register int token;
	register bool escape_flag = false;

	while ((token=fgetc(file_ptr)) != terminate_quote || escape_flag == true) {
		if (feof(file_ptr) || token == EOF)
			return;
		escape_flag = (token == BACKSLASH_CHAR) ? true : false;
		putchar(token);
	}
	putchar(token); // Print the last quote symbol
}
