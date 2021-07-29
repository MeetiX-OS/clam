#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "txtutils.h"
#include "utils.h"

int txtutils_remove(char** str, unsigned int from, unsigned int to) {
	unsigned int str_len, substr_len = to - from + 1;

	assert(*str != NULL);

	str_len = strlen(*str);

	assert(from <= to && to < str_len);

	if (to < str_len - 1) {
		/* There are some chars to shift left after the removed string */
		memmove(&(*str)[from], &(*str)[to + 1], str_len - to - 1);
	}

	memset(&(*str)[str_len - substr_len], 0, substr_len);

	str_len = strlen(*str);
	*str = realloc(*str, str_len + 1);
	utils_checkheap(*str);

	return 1;
}

unsigned int txtutils_replace(char** str, char* txt1, char* txt2) {
	int i, str_len, txt1_len, txt2_len, repl_numb = 0;
	char* substr;

	assert(*str != NULL && txt1 != NULL && txt2 != NULL);

	str_len = strlen(*str);
	txt1_len = strlen(txt1);
	txt2_len = strlen(txt2);

	if (txt1_len > str_len)
		return 0;

	substr = calloc(txt1_len + 1, sizeof(char));
	utils_checkheap(substr);

	for (i = 0; i <= str_len - txt1_len; i++) {
		memcpy(substr, &(*str)[i], txt1_len);

		if (strcmp(substr, txt1) == 0) {
			/* Text match */
			int new_str_len = str_len - txt1_len + txt2_len;
			char* new_str;

			new_str = calloc(new_str_len + 1, sizeof(char));
			utils_checkheap(new_str);

			/* Paste the new string */
			memcpy(new_str, &*(str)[i], i);
			strcat(new_str, txt2);
			strcat(new_str, &(*str)[i + txt1_len]);

			free(*str);
			*str = new_str;

			repl_numb++;
		}
	}

	free(substr);

	return repl_numb;
}

int txtutils_checkinput(char* input) {

	/* Boolean variables whose value is 1 if there is a double quote " (dqt)
	 * open or a single quote ' (sqt) open */
	int dqt_open = 0, sqt_open = 0;

	int i, in_len;

	if (strlen(input) == 0) {
		return 0;
	}

	in_len = strlen(input);

	for (i = 0; i < in_len; i++) {
		if (input[i] == '"') {
			dqt_open = !dqt_open;
		} else if (input[i] == '\'') {
			if (!dqt_open) {
				sqt_open = !sqt_open;
			}
		}
	}

	if (dqt_open || sqt_open) {
		if (dqt_open)
			printf("Syntax error: odd amount of double quotes `\"`\n");
		else if (sqt_open)
			printf("Syntax error: odd amount of single quotes `'`\n");

		return 0;
	}

	return 1;
}

char* txtutils_copystr(char* str) {
	int str_len;
	char* new_str;

	if (!str) return NULL;

	str_len = strlen(str);
	new_str = calloc(str_len + 1, sizeof(char));
	utils_checkheap(new_str);
	strcpy(new_str, str);

	return new_str;
}
