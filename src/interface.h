#ifndef CLAM_INTERFACE_H
#define CLAM_INTERFACE_H

/*
 * While all the code in other modules can be executed by almost any operating
 * system, this module contains wrappers for OS-specific functions which have to
 * handle different behaviours. The decision of writing those functions in a
 * separate module was taken in order to both ease the program porting and
 * keep the code clean.
 */

/* Execute a program, return 1 if the program has been successfully executed, 0
 * otherwise */
int interface_exec_program(char* path);

/* Get the user running the shell, NULL if it could not be get */
char* interface_get_user();

#endif //CLAM_INTERFACE_H
