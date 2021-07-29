#ifndef CLAM_COMMAND_H
#define CLAM_COMMAND_H

/* Read a line from stdin and store it in COMMAND (split by space), return 0 in
 * case of error, 1 otherwise. */
int cmd_split(char* input);

/* Get an item, return NULL if the item doesn't exist */
char* cmd_get(unsigned int idx);

/* Set an item, return 0 if the item doesn't exist, 1 otherwise. DO NOT use this
 * function to add items to COMMAND. */
int cmd_set(unsigned int idx, char* value);

/* Remove an item, return 0 if the item doesn't exist, 1 otherwise */
int cmd_rem(unsigned int idx);

/* Add an item in a specified index, return 0 if it couldn't be added */
int cmd_add(unsigned int idx, char* value);

/* Add an item at the end */
void cmd_append(char* value);

/* Empty the COMMAND list */
void cmd_reset();

/* Print a range of items of the command */
void cmd_printrng(unsigned int from, unsigned int to);

#endif //CLAM_COMMAND_H
