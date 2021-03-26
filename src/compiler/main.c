#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

int main(int args, char* argv[]) {
    if (args > 1) {
        FILE* file = fopen(argv[1], "r");
        printf("%s", readfile(file));
    } else {
        FILE* file = fopen("./src/compiler/dogshit.sa", "r");
        printf("\n%s", readfile(file));
    }
}

