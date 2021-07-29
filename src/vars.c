#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>

#include "vars.h"
#include "interface.h"
#include "defines.h"
#include "utils.h"
#include "txtutils.h"
#include "cmd.h"

/* Linked list with pointers on both the next and previous */
typedef struct var_t {
	char* name;
	char* value;
	struct var_t* next;
} Var;

/* Pointer to the first variable */
Var* VARS = NULL;

/* Number of variables declared */
int VARS_LEN = 0;

void vars_init() {
	char* username = interface_get_user();
	char* home_path = calloc(strlen(username) + 8, sizeof(char));

	utils_checkheap(home_path);

	strcpy(home_path, "/Users/");
	strcat(home_path, username);
	
	vars_set("USER", username);
	vars_set("HOME", home_path);
	vars_set("CWD", home_path);
}

/* Returns a pointer to the variable if it exists, NULL otherwise */
Var* vars_exists(char* name) {
	Var* tmp = VARS;

	while (tmp != NULL) {
		if (strcmp(tmp->name, name) == 0) {
			return tmp;
		}

		tmp = tmp->next;
	}

	return NULL;
}

/* Return a pointer to the first invalid character for a variable name, NULL if
 * the whole string is valid as a variable name */
char* vars_is_valid(char* name) {
	int i, name_len, valid_chr_len;

	/* Valid characters for the variable name (except for alphanumeric chars),
	 * may be modified in future */
	char* valid_chr = "_";

	name_len = strlen(name);
	valid_chr_len = strlen(valid_chr);

	for (i = 0; i < name_len; i++) {
		if (!isalnum(name[i])) {
			int j, is_valid = 0;

			/* Check if the string contains only valid chars */
			for (j = 0; j < valid_chr_len; j++) {
				if (name[i] == valid_chr[j])
					is_valid = 1;
			}

			if (!is_valid)
				return &name[i];
		}
	}

	return NULL;
}

/* Return a pointer to the first character of a variable name (excluding the '$'
 * char), NULL if there are no variables */
char* vars_first(char* str) {
	int idx_start = 0, str_len;

	/* Current occurrence of character */
	char* occ;

	assert(str != NULL);
	str_len = strlen(str);

	while ((occ = strchr(&str[idx_start], '$'))) {
		/* Index of occurrence in string */
		int idx = occ - str;

		/* Conditions to satisfy to be identified as a variable name */
		int cond1 = idx < str_len - 1 &&
			(isalnum(str[idx + 1]) || str[idx + 1] == '_');
		int cond2 = idx > 0 && str[idx - 1] != '\\';

		if (cond2 || cond1) {
			return occ + 1;
		}
	}

	return NULL;
}

int vars_set(char* name, char* value) {
	Var* variable = vars_exists(name);

	if (!variable) {
		Var* tmp;

		if (vars_is_valid(name)) {
			printf("Error: `%s` is not a valid variable name\n", name);
			return 0;
		}

		/* Create a new variable */
		tmp = malloc(sizeof(Var));

		utils_checkheap(tmp);

		tmp->name = name;
		tmp->value = value;

		/* Put the variable as first item in the list */
		tmp->next = VARS;

		VARS = tmp;

	} else {
		variable->value = value;
	}

	return 1;
}

int vars_rem(char* name) {
	Var* variable = vars_exists(name);

	if (!variable) {
		/* Variable does not exist */
		return 0;
	} else {
		/* Fix the pointers */
		if (VARS == variable) {
			VARS = variable->next;
		} else {
			Var* tmp = VARS;

			/* Search the previous item */
			while (tmp != NULL && tmp->next != variable) {
				tmp = tmp->next;
			}

			tmp->next = variable->next;
		}

		/* Free the space allocated */
		free(variable);
	}

	return 1;
}

char* vars_get(char* name) {
	Var* variable = vars_exists(name);

	if (!variable) {
		return NULL;
	}

	return variable->value;
}

unsigned int vars_replace(char** str) {
	/* Occurrence of a variable */
	char* var_occ = *str;
	int str_len, vars_found = 0;

	while ((var_occ = vars_first(var_occ)) && strlen(var_occ) > 0) {
		char* varname, * value;
		int varname_len;

		/* First invalid character */
		char *first_inv = vars_is_valid(var_occ);

		str_len = strlen(*str);

		varname_len = strlen(var_occ);

		if (first_inv) {
			/* first_inv is not NULL, so there is an invalid character in
			 * position (first_inv - str) */
			varname_len -= str_len - (first_inv - *str);
		}

		varname = calloc(varname_len, sizeof(char));
		utils_checkheap(varname);
		memcpy(varname, var_occ, varname_len);
		value = vars_get(varname);

		if (value) {
			/* Remove '$' */
			txtutils_remove(str, (var_occ - 1) - *str, (var_occ - 1) - *str);

			txtutils_replace(str, varname, value);
		} else {
			if (first_inv)
				txtutils_remove(str, (var_occ - 1) - *str,
					(first_inv - 1) - *str);
			else
				txtutils_remove(str, (var_occ - 1) - *str, str_len - 1);
		}

		free(varname);
		vars_found++;
	}

	return vars_found;
}
