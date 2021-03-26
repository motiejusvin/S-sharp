#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

#define SUCCESS 1
#define ERROR -1
#define WARN -2
#define MAXTYPE 5
#define MAXSTRING 1024
#define MAXVARS 32000

int prntc(char *input) {
    if (input) {
        printf("%s", input);
        return SUCCESS;
    }
    else{
        return ERROR;
    }
}
