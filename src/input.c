#include "../include/input.h"
#include "../include/new_string.h"
#include <stddef.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>



int str_input(char *string, size_t size){
    int ascii = 0;
    int index = 0;

    if (string != NULL && size > 0){
        while((ascii = getchar()) != '\n' && ascii != EOF){
            if (index < size - 1){
                string[index] = (char) ascii;
                index++;
            }
        }

        string[index] = '\0';
        return 0;
    }

    return 1;
}


int number_input(void *dest_variable, int (*type_input)(void *dest_variable, char *buffer)){
    String buffer;
    errno = 0;
    char *end;
    if (str_input(buffer, STRING_LENGHT) == 0){
        if (buffer[0] != '\0'){
            int status = type_input(dest_variable, buffer);
            return  status;
        }
        return EMPTY_INPUT;
    }
    return CRITICAL_ERROR;
}


int double_input(void *dest_variable, char *buffer){
    double *tmp_p = (double*) dest_variable; 
    char *end;    
    errno = 0;

    double temp_var = strtod(buffer, &end);
    if (errno == ERANGE){
        return LIMIT_OVERFLOW;
    } if (*end != '\0'){
        return ONLY_NUMBERS;
    } 
    *tmp_p = temp_var;
    return SUCESS;
}

int int_input(void *dest_variable, char *buffer){
    int *tmp_var = (int*) dest_variable;
    char *end;
    errno = 0;
    long temp_var = strtol(buffer, &end, 10);
    
    if (errno == ERANGE){
        return LIMIT_OVERFLOW;
    } if (*end != '\0'){
        return ONLY_NUMBERS;
    } if (temp_var > INT_MAX || temp_var < INT_MIN){
        return LIMIT_OVERFLOW;
    }
    
    *tmp_var = (long) temp_var;
    return SUCESS;
}


void persistent_number_input(void *dest_variable, int (*type_input)(void *dest_variable, char *buffer)){
    int break_while = 1;
    while (break_while){
        int status = number_input(dest_variable, type_input);
        switch (status) {
            case EMPTY_INPUT:
                printf("Digite algo. Tente novamente: ");
                break;
            case LIMIT_OVERFLOW:
                printf("Limite ultrapassado. Tente novamente: ");
                break;
            case ONLY_NUMBERS:
                printf("Digite apenas numeros. Tente novamente: ");
                break;
            case SUCESS:
                break_while = 0;
                break;
        }
    }

}   

