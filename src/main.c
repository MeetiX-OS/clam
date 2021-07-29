#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtins.h"
#include "interface.h"
#include "vars.h"
#include "utils.h"
#include "cmd.h"
#include "defines.h"
#include "txtutils.h"

/* TODO:
 *  - Make large functions smaller by creating other small functions;
 */

/* Run program whose name is in COMMAND[0] */
void run_program() {
	char* first_item = cmd_get(0);
	if (!interface_exec_program(first_item)) {
		/* There is nothing to run */
		printf("Error: `%s` is not a builtin command or an executable" \
			" program\n", first_item);
	}
}

void replace_vars_cmd() {
	int i;
	char* nth_item;

	for (i = 0; i < MAX_COMMAND_WORDS; i++) {
		nth_item = txtutils_copystr(cmd_get(i));

		if (nth_item && vars_replace(&nth_item))
			cmd_set(i, nth_item);
	}
}

/* Read a string from input */
char* get_input() {
	int buff_len = 512, idx = 0;
	char c;
	char* input;
	char* buffer = calloc(buff_len, sizeof(char));

	utils_checkheap(buffer);

	while ((c = getchar()) != '\n') {
		if (idx == buff_len - 2) {
			/* Resize buffer of 1.5 times its current size to contain new
			 * chars */
			buff_len += buff_len/2;
			buffer = realloc(buffer, buff_len);

			utils_checkheap(buffer);
		}

		buffer[idx++] = c;
	}

	/* Copy the buffer in a string of correct size*/
	input = calloc(strlen(buffer) + 1, sizeof(char));
	utils_checkheap(input);
	strcpy(input, buffer);

	free(buffer);

	return input;
}

/* Initialize everything */
void init() {
	builtins_init();
	vars_init();
}

int main() {
	init();

	/* Actually not an endless loop, see the "exit" builtin */
	for (;;) {
		char* input;

		printf("> ");
		fflush(NULL);

		/* Get input from stdin */
		input = get_input();

		if (!txtutils_checkinput(input)) {
			continue;
		}

		/* Split the input by spaces */
		if (!cmd_split(input)) {
			continue;
		}

		/* Replace the variables with their values */
		replace_vars_cmd();

		/* Run a builtin if it is a builtin, otherwise run a program */
		if (!builtins_exec()) {
			/* Run the program */
			run_program();
		}

		/* Clean the COMMAND array */
		cmd_reset();

		free(input);
	}

	return 0;
}