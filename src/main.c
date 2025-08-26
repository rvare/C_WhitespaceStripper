#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
	char token;
	
	while ((token =  getchar()) != EOF) {
		if (isspace(token)) {
			continue;
		}
		else if (token == '"') {
			do
				putchar(token);
			while ((token = getchar()) != '"');
			putchar(token);
		}
		else {
			putchar(token);
		}
	}

	return EXIT_SUCCESS;
}
