#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int main() 
{
    FILE* file = fopen("dogshit.sa","r");
    printf("%i",readfile(file));
}

