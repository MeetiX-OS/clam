#ifndef CLAM_VARS_H
#define CLAM_VARS_H

/*
 * Shell variables:
 *  - "HOME": user home
 *  - "CWD": current working directory
 */

/* Initialize some variables */
void vars_init();

/* Set the value for a variable or declare a variable. Return 1 on successful
 * set, 0 otherwise. */
int vars_set(char* name, char* value);

/* Remove a variable. Return 1 on successful remove, 0 otherwise. */
int vars_rem(char* name);

/* Get the value of a variable */
char* vars_get(char* name);

/* Replace the variables ("$varname") in COMMAND. Return the number of variables
 * found in str (both declared and unknown). */
unsigned int vars_replace(char** str);

#endif //CLAM_VARS_H
