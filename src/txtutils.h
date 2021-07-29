#ifndef CLAM_TXTUTILS_H
#define CLAM_TXTUTILS_H

/* Remove a part of a string (indexes from and to are included) and resize the
 * string. Return 1 if the part has been removed correctly, 0 otherwise. The
 * variable str MUST be allocated in heap.*/
int txtutils_remove(char** str, unsigned int from, unsigned int to);

/* Replace txt1 with txt2 in str. Return the number of replacements done. The
 * variable str MUST be allocated in heap. */
unsigned int txtutils_replace(char** str, char* txt1, char* txt2);

/* Check if input syntax is correct, return 1 if it is, 0 otherwise */
int txtutils_checkinput(char* input);

/* Copy a string and return its clone (allocated in heap). Return NULL either if
 * the string could not be copied or if the original string was NULL.*/
char* txtutils_copystr(char* str);

#endif //CLAM_TXTUTILS_H
