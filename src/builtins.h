#ifndef CLAM_BUILTINS_H
#define CLAM_BUILTINS_H

/* Initialize BUILTINS */
void builtins_init();

/* If the COMMAND[0] is builtin, executes it and return 1, otherwise return 0 */
int builtins_exec();

#endif //CLAM_BUILTINS_H
