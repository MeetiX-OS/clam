#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

void utils_checkheap(void* var) {
	if (!var) { /* equal to `var == NULL` */
		printf("heap space allocation failed\n");
		exit(EXIT_FAILURE);
	}
}
