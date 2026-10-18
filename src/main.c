/*
Whitespace Strirpper (aka whtstrp) v2 A program that strips whitespace
characters from a file.
Copyright (C) 2026 Richard Ernest Varela <richardvare13@gmail.com>

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

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BACKSLASH_CHAR		'\\'
#define DOUBLE_QUOTECHAR	'\"'
#define SINGLE_QUOTECHAR	'\''
#define LEFT_ANGLE_BRACKET	'<'
#define RIGHT_ANGLE_BRACKET	'>'

typedef struct {
	bool custom_set;
	bool strip_carriage_return;
	bool strip_newlines;
	bool strip_spaces;
	bool strip_tabs;
	bool xml_format;
} CmdFlags;

void show_version();
void show_help();
void parse_cmd_args(char*, CmdFlags*);
void strip_whitespace(FILE *);
void custom_strip(FILE *, CmdFlags*);
void process_xml_format(FILE *);
void process_angle_brackets(FILE *);
void process_string(char, FILE *);

int main(int argc, char *argv[]) {
	FILE *file_ptr = NULL;
	CmdFlags cmd_flags = {0};

	if (argc == 1) {
		fprintf(stderr, "ERROR: No arguments given. See --help for details.\n");
		return EXIT_FAILURE;
	}

	if (argv[1][0] == '-')
		parse_cmd_args(argv[1], &cmd_flags);

	file_ptr = fopen(argv[argc-1], "r");
	if (file_ptr == NULL) {
		perror("ERROR opening file");
		return EXIT_FAILURE;
	}

	if (cmd_flags.custom_set)
		if (cmd_flags.xml_format)
			process_xml_format(file_ptr);
		else
			custom_strip(file_ptr, &cmd_flags);
	else
		strip_whitespace(file_ptr);

	fclose(file_ptr);

	if (ferror(file_ptr)) {
		perror("ERROR closing file");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/* Show version and copyright information when --version is used. */
void show_version() {
	puts(	"Whitespace Strirpper (aka whtstrp) v2 Copyright (C) 2026 Richard Ernest Varela\n"
			"License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n"
			"This program comes with ABSOLUTELY NO WARRANTY.\n"
			"This is free software: you are free to change and redistribute it."
			);
}

/* Display help information when --version is used. */
void show_help() {
	puts(	"Usage: whtstrp [OPTION] [FILE]\n"
			"Strips whitespaces characters from FILE, and prints the results to standard output.\n\n"
			"Options:\n"
			"    -n         strip newline characters\n"
			"    -r         strip carriage returns\n"
			"    -s         strip spaces\n"
			"    -t         strip tabs\n"
			"    --help     display this help and exit\n"
			"    --version  output version and copyright information, then exits"
			);
}

/*
Purpose: Prases cmd args.
Precondition: The address in cmd_flags points to a CmdFlags, and args points to argv[1] from main.
Postcondition: all flags processed and booleans in cmd_flags could be set to true, or exit as
	failure on unrecognized arg.
Invarient(s): None
*/
void parse_cmd_args(char *args, CmdFlags* cmd_flags) {
	if (strcmp(args, "--version") == 0) {
		show_version();
		exit(EXIT_SUCCESS);
	}

	if (strcmp(args, "--help") == 0) {
		show_help();
		exit(EXIT_SUCCESS);
	}

	for (register size_t i = 1; args[i] != '\0'; ++i) {
		switch (args[i]) {
			case 'n':
				cmd_flags->strip_newlines = true;
				break;
			case 'r':
				cmd_flags->strip_carriage_return = true;
				break;
			case 's':
				cmd_flags->strip_spaces = true;
				break;
			case 't':
				cmd_flags->strip_tabs = true;
				break;
			case 'x':
				cmd_flags->xml_format = true;
				break;
			default:
				puts("Unrecognized arg\n");
				exit(EXIT_FAILURE);
				break;
		}
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
		else if (token == LEFT_ANGLE_BRACKET) {
			putchar(token);
			process_angle_brackets(file_ptr);
		}
		else
			putchar(token);
		escape_flag = (token == BACKSLASH_CHAR) ? true : false;
	}

	if (ferror(file_ptr)) {
		perror("ERROR with file");
		exit(EXIT_FAILURE);
	}
}

/*
Purpose: Custome whitespace stripping
Precondition: file_ptr points to a valid file descriptor, and cmd_flags points to a CmdFlags
	structure.
Postcondition: All whitespace characters, as defined by cmd_flags, are ingnored.
Invarient(s): file_ptr, cmd_flags.
*/
void custom_strip(FILE *file_ptr, CmdFlags *cmd_flags) {
	register char token;
	register bool escape_flag = false;

	while ((token=fgetc(file_ptr)) != EOF) {
		if (cmd_flags->strip_newlines && token == '\n')
			continue;
		else if (cmd_flags->strip_carriage_return && token == '\r')
			continue;
		else if (cmd_flags->strip_spaces && token == ' ')
			continue;
		else if (cmd_flags->strip_tabs && token == '\t')
			continue;
		else if ((token == SINGLE_QUOTECHAR || token == DOUBLE_QUOTECHAR) && escape_flag == false) {
			putchar(token);
			process_string(token, file_ptr);
		}
		else if (token == LEFT_ANGLE_BRACKET) {
			putchar(token);
			process_angle_brackets(file_ptr);
		}
		else
			putchar(token);
		escape_flag = (token == BACKSLASH_CHAR) ? true : false;
	}

	if (ferror(file_ptr)) {
		perror("ERROR with file");
		exit(EXIT_FAILURE);
	}
}

/*
Purpose: Handles XML and XML like formats.
Precondition: xml_format in cmd_flags set to true.
Postcondition: All whitespace characters, except for those between <> and alpha-numeric characters.
Invarient(s): None
*/
void process_xml_format(FILE *file_ptr) {
	register int token, prev;

	while ((token=fgetc(file_ptr)) != EOF) {
		if (token == '<') {
			if (prev == ' ') {
				fflush(file_ptr);
				putchar('\b');
				prev = '\0';
			}
			putchar(token);
			process_angle_brackets(file_ptr);
		}
		else if (isalnum(token)) {
			putchar(token);
			while ((token=fgetc(file_ptr)) != '\n' && token != EOF) {
				putchar(token);
				prev = token;
			}
			if (prev != '>' && token != EOF) {
				putchar(' ');
				prev = ' ';
			}
		}
	}

	if (ferror(file_ptr)) {
		perror("ERROR with file");
		exit(EXIT_FAILURE);
	}
}

/*
Purpose: Handles the case when angle brackets are encountered.
Precondition: token is a left angle bracket '<'.
Postcondition: A closing right angle bracket '>' is encountered.
Invarient(s): None
*/
void process_angle_brackets(FILE *file_ptr) {
	register int token;
	register bool escape_flag = false;

	while ((token=fgetc(file_ptr)) != RIGHT_ANGLE_BRACKET) {
		if (feof(file_ptr) || token == EOF)
			return;
		else if ((token == SINGLE_QUOTECHAR || token == DOUBLE_QUOTECHAR) && escape_flag == false) {
			putchar(token);
			process_string(token, file_ptr);
		}
		else
			putchar(token);
		escape_flag = (token == BACKSLASH_CHAR) ? true : false;
	}
	putchar(token); // Print right angle bracket
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
