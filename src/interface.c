#include <stdlib.h>
#include <string.h>

#include "interface.h"
#include "utils.h"

int interface_exec_program(char* path) {
	/* TODO */

	return 0;
}

char* interface_get_user() {
	/* TODO */

	char* user = calloc(6, sizeof(char));

	utils_checkheap(user);

	strcpy(user, "pippo");

	return user;
}