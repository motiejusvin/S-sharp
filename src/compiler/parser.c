#include "parser.h"

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUCCESS 1
#define ERROR -1
#define WARN -2
#define MAXTYPE 5
#define MAXSTRING 128
char types[MAXTYPE][64] = {"sveikasis", "dvejetaine", "nesveikasis", "rmasyvas",
                           "raide"};

char* readfile(FILE* file) {
    bool we = false; //was equal
    short pos = 0;
    int linec = 0;
    size_t len = 0;  // size_t: cannot be negative
    char* line;
    int preve = 0; //Previous char location
    ssize_t read;  // ssize_t: same as size_t,but can have -1
    char* fw = malloc(MAXSTRING);
    char* name = malloc(MAXSTRING);
    char* value = malloc(MAXSTRING);
    if (file == NULL) {
        printf("\nFile not found. Exiting...\n");
        exit(ERROR);
    }

    while ((read = getline(&line, &len, file)) != -1) { //Kol yra i ka ziureti, tol daryk....
        linec++;
        if(read > 0){
            for (int l = 0; l < read; l++) {
                if (line[l] != 32) {
                    fw[l] = line[l];
                    preve++;
                } else {
                    printf("\n");
                    break;
                }
            }
        
            if (fw) {
                for (int l = preve + 1; l < read; l++) {
                    if (line[l] != 32) {
                        name[pos] = line[l];
                        pos++;
                        preve++;
                    } else {
                        pos = 0;
                        break;
                    }
                }
            }
            if (name) {
                for (int l = preve + 1; l < read; l++) {
                    if (!we && line[l] == '=') {
                        we = true;
                        l++;
                    } else if (we) {
                        if (line[l] != 32) {
                            value[pos] = line[l];
                            pos++;
                        } else {
                            pos = 0;
                            break;
                        }
                    }
                }
            }
            for (int l = 0; l < MAXTYPE; l++) {
                if (strcmp(types[l], fw) == 0) {
                    printf("Found %s with name %s,value %s in line %i\n", types[l],
                        name, value, linec);
                    break;
                }
            }
            preve = 0;
            memset(name, 0, sizeof(name));
            memset(value, 0, sizeof(value));
            memset(fw, 0, sizeof(fw));
            if (line[0] == '/') {
                printf("\n");
            }
        }
    }
    if(line){
        free(line);
    }
    fclose(file);
    return "\nSUCCESS";
}

