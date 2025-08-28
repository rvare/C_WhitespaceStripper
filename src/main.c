#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define QUOTECHAR '"'

void process_string(char token);

int main(int argc, char *argv[]) {
	char token;
	
	while ((token=getchar()) != EOF) {
		if (isspace(token))
			continue;
		else if (token == QUOTECHAR)
			process_string(token);
		else
			putchar(token);
	}

	return EXIT_SUCCESS;
}

/*
Purpose: Handles the case when double quotation mark is encountered.
Precondition: token is a is a double quotation mark.
Postcondition: A closing double quotation marks has been encountered.
Invarient: None
*/
void process_string(char token) {
	do
		putchar(token);
	while ((token = getchar()) != QUOTECHAR);
	putchar(token); // Print the last quote symbol
}
