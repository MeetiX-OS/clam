#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "cmd.h"
#include "utils.h"

typedef struct cmditem_t {
	char* value;
	struct cmditem_t* next;
} CmdItem;

/* The command split into words (separator = ' ') implement through a linked
 * list */
CmdItem* COMMAND = NULL;
unsigned int COMMAND_LEN = 0;

/* Return a pointer to the item at the specified index */
CmdItem* cmd_goto(int idx) {
	int i;
	CmdItem* tmp = COMMAND;

	if (idx >= (int) COMMAND_LEN || idx < 0) {
		return NULL;
	}

	for (i = 0; i < idx; i++) {
		tmp = tmp->next;
	}

	return tmp;
}

int cmd_split(char* input) {
	int in_len, i, item_start = 0;

	/* Boolean variables whose value is 1 if there is a double quote " (dqt)
	 * open or a single quote ' (sqt) open */
	int dqt_open = 0, sqt_open = 0;

	in_len = strlen(input);

	for (i = 0; i <= in_len; i++) {
		/* Skip chars preceded by '\' (a.k.a. treat them as any other char) */
		if (i > 0 && input[i - 1] == '\\') continue;

		if (input[i] == '"') {
			if (sqt_open) {
				printf("Syntax error: unexpected '\"' at index %d\n", i);
				return 0;
			}

			dqt_open = 1;
		} else if (input[i] == '\'') {
			/* Ignore it if the double quote is open */
			if (dqt_open) continue;

			sqt_open = 1;
		} else if (input[i] == ' ' || input[i] == '\0') {
			int item_len = i - item_start;
			char* new_item;

			if ((input[i] == ' ' && (dqt_open || sqt_open)) ||
				(i > 0 && input[i-1] == ' ')) {
				continue;
			}

			/* Split */
			new_item = calloc(item_len + 1, sizeof(char));
			utils_checkheap(new_item);
			memcpy(new_item, &input[item_start], (item_len));
			cmd_append(new_item);
			item_start = i + 1;
		}
	}

	return 1;
}

char* cmd_get(unsigned int idx) {
	CmdItem* item = cmd_goto(idx);

	if (item) {
		return item->value;
	} else {
		return NULL;
	}
}

int cmd_set(unsigned int idx, char* value) {
	CmdItem* item = cmd_goto(idx);

	free(item->value);
	item->value = value;

	return 1;
}

int cmd_rem(unsigned int idx) {
	CmdItem* prev, * item;

	prev = cmd_goto(idx - 1);
	item = cmd_goto(idx);

	if (!item) {
		return 0;
	}

	/* Fix pointers according to what exists and what not */
	if (item->next) {
		if (prev) {
			prev->next = item->next;
		} else {
			COMMAND = item;
		}
	} else {
		if (prev) {
			prev->next = NULL;
		} else {
			COMMAND = NULL;
		}
	}

	free(item->value);
	free(item);
	COMMAND_LEN--;
	return 1;
}

int cmd_add(unsigned int idx, char* value) {
	CmdItem* new_item;
	CmdItem* prev;

	if (idx > COMMAND_LEN) {
		return 0;
	}

	new_item = malloc(sizeof(CmdItem));
	utils_checkheap(new_item);
	new_item->next = cmd_goto(idx);
	new_item->value = value;
	prev = cmd_goto(idx - 1);

	if (prev) {
		prev->next = new_item;
	} else {
		COMMAND = new_item;
	}

	COMMAND_LEN++;
	return 1;
}

void cmd_append(char* value) {
	cmd_add(COMMAND_LEN, value);
}

void cmd_reset() {
	CmdItem* tmp = COMMAND;

	while (tmp != NULL) {
		CmdItem* next = tmp->next;
		free(tmp->value);
		free(tmp);
		tmp = next;
	}

	COMMAND = NULL;
	COMMAND_LEN = 0;
}

void cmd_printrng(unsigned int from, unsigned int to) {
	unsigned int i = from;
	CmdItem* tmp = cmd_goto(from);

	while (tmp != NULL) {
		if (i > to) break;
		printf("%s ", tmp->value);
		tmp = tmp->next;
		i++;
	}

	printf("\n");
}
