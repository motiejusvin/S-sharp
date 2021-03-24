#include "parser.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1
#define WARN -2

char *types[] = {"sveikasis","dvejetaine","nesveikasis","rmasyvas","raide"};

char* readfile(FILE* file) {
    char c;
    while ((c = fgetc(file)) != EOF) {
        printf("%c",c); 
    }
    fclose(file);
    printf("\n");
    return 0;
}

