/*
Whitespace Strirpper (aka whtstrp) A program that strips whitespace
characters from a file.
Copyright (C) 2025 Richard Ernest Varela <richardvare13@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>. 
*/

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

	if (strcmp(argv[1], "--version") == 0) {
		printf("Whitespace Strirpper (aka whtstrp) Copyright (C) 2025 Richard Ernest Varela\n"
				"License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n"
				"This program comes with ABSOLUTELY NO WARRANTY.\n"
				"This is free software: you are free to change and redistribute it.\n"
				);
		return 0;
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
