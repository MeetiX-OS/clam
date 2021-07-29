#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "builtins.h"
#include "vars.h"
#include "defines.h"
#include "cmd.h"

#define BUILTINS_NUMB 5

/* Builtin commands */
static struct { char* name; void (*func)(void); } BUILTINS[BUILTINS_NUMB] = {0};

void builtins_cd() {
	if (!cmd_get(1)) {
		/* If no arguments are provided, go HOME */
		char* home = vars_get("HOME");
		vars_set("CWD", home);
	} else {
		vars_set("CWD", cmd_get(1));
	}
}

void builtins_echo() {
	extern unsigned int COMMAND_LEN;
	if (!cmd_get(1)) {
		printf("\n");
	} else {
		cmd_printrng(1, COMMAND_LEN);
	}
}

void builtins_pwd() {
	printf("%s\n", vars_get("CWD"));
}

void builtins_set() {
	char* cmd_item1, * cmd_item2, * varname, * value;

	if (!cmd_get(2)) {
		/* COMMAND contains less than 3 items */
		printf("Usage: set NAME VALUE\n");
		return;
	}

	cmd_item1 = cmd_get(1);
	cmd_item2 = cmd_get(2);

	varname = calloc(strlen(cmd_item1) + 1, sizeof(char));
	value = calloc(strlen(cmd_item2) + 1, sizeof(char));

	strcpy(varname, cmd_item1);
	strcpy(value, cmd_item2);

	vars_set(varname, value);
}

void builtins_exit() {
	printf("bye bye\n");
	exit(EXIT_SUCCESS);
}

void builtins_init() {
	/* Change directory */
	BUILTINS[0].name = "cd";
	BUILTINS[0].func = builtins_cd;

	/* Print a message */
	BUILTINS[1].name = "echo";
	BUILTINS[1].func = builtins_echo;

	/* Print the working directory*/
	BUILTINS[2].name = "pwd";
	BUILTINS[2].func = builtins_pwd;

	/* Set a variable */
	BUILTINS[3].name = "set";
	BUILTINS[3].func = builtins_set;

	BUILTINS[4].name = "exit";
	BUILTINS[4].func = builtins_exit;
}

int builtins_exec() {
	int i;

	for (i = 0; i < BUILTINS_NUMB; i++) {
		if (strcmp(BUILTINS[i].name, cmd_get(0)) == 0) {
			BUILTINS[i].func();
			return 1;
		}
	}

	return 0;
}

