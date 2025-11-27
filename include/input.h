#ifndef INPUTS_H
#define INPUTS_H
#define LIMIT_OVERFLOW 3
#define ONLY_NUMBERS 4
#define CRITICAL_ERROR 5
#define EMPTY_INPUT 1
#define SUCESS 0
#include <stddef.h>

int str_input(char *string, size_t size);
int int_input(void *dest_variable, char *buffer);
int number_input(void *dest_variable, int (*type_input)(void *dest_variable, char *buffer));
int double_input(void *dest_variable, char *buffer);
void persistent_number_input(void *dest_variable, int (*type_input)(void *dest_variable, char *buffer));
#endif