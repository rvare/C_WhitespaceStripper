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

typedef struct {
	bool custom_set;
	bool strip_tabs;
	bool strip_newlines;
} CmdFlags;

void parse_cmd_args(char *argv, CmdFlags* cmd_flags);
void process_string(char, FILE *);
void show_version();
void strip_whitespace(FILE *);
void custom_strip(FILE *, CmdFlags* cmd_flags);

int main(int argc, char *argv[]) {
	FILE *file_ptr = NULL;
	CmdFlags cmd_flags = {0};

	if (argc == 1) {
		fprintf(stderr, "ERROR with command arguments: No file given\n");
		return 1;
	}

	if (strcmp(argv[1], "--version") == 0) {
		show_version();
		return 0;
	}

	if (argv[1][0] == '-')
		parse_cmd_args(argv[1], &cmd_flags);

	file_ptr = fopen(argv[argc-1], "r");
	if (file_ptr == NULL) {
		perror("ERROR opening file");
		return 1;
	}

	if (cmd_flags.custom_set)
		custom_strip(file_ptr, &cmd_flags);
	else
		strip_whitespace(file_ptr);

	if (ferror(file_ptr)) {
		perror("ERROR with file");
		return 1;
	}

	fclose(file_ptr);

	return 0;
}

/*
Purpose: Handles the case when single or double quotation mark is encountered.
Precondition: token is either a single or double quotation mark.
Postcondition: A closing single or double quotation mark, not escaped, has been encountered.
Invarient(s): None
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

void show_version() {
	printf(	"Whitespace Strirpper (aka whtstrp) 2.0 Copyright (C) 2026 Richard Ernest Varela\n"
			"License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n"
			"This program comes with ABSOLUTELY NO WARRANTY.\n"
			"This is free software: you are free to change and redistribute it.\n"
			);
}

/*
Purpose: Prases cmd args.
Precondition: The address in cmd_flags points to a CmdFlags, and args points to argv[1] from main.
Postcondition: all flags processed and booleans in cmd_flags could be set to true, or exit as failure on unrecognized arg.
Invarient(s): None
*/
void parse_cmd_args(char *args, CmdFlags* cmd_flags) {
	register size_t i = 1;
	while (args[i] != '\0') {
		switch (args[i]) {
			case 'n':
				printf("Strip new lines\n");
				cmd_flags->strip_newlines = true;
				break;
			case 't':
				printf("Strip tabs lines\n");
				cmd_flags->strip_tabs = true;
				break;
			default:
				printf("Unrecognized arg\n");
				exit(EXIT_FAILURE);
				break;
		}
		++i;
	}
	cmd_flags->custom_set = true;
}

/*
Purpose: Default whitespace stripping
Precondition: file_ptr points to a valid file descriptor.
Postcondition: All whitespace characters that isspace knows have been stripped.
Invarient(s): file_ptr
*/
void strip_whitespace(FILE *file_ptr) {
	register char token;
	register bool escape_flag = false;

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
}

/*
Purpose: Custome whitespace stripping
Precondition: file_ptr points to a valid file descriptor, and cmd_flags points to a CmdFlags structure.
Postcondition: All whitespace characters, as defined by cmd_flags, are ingnored.
Invarient(s): file_ptr, cmd_flags.
*/
void custom_strip(FILE *file_ptr, CmdFlags *cmd_flags) {
	register char token;
	register bool escape_flag = false;

	while ((token=fgetc(file_ptr)) != EOF) {
		if (cmd_flags->strip_newlines && token == '\n')
			continue;
		else if (cmd_flags->strip_tabs && token == '\t')
			continue;
		else if ((token == SINGLE_QUOTECHAR || token == DOUBLE_QUOTECHAR) && escape_flag == false) {
			putchar(token);
			process_string(token, file_ptr);
		}
		else
			putchar(token);
		escape_flag = (token == BACKSLASH_CHAR) ? true : false;
	}
}
