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
    bool we = false;
    short pos = 0;
    int linec = 0;
    size_t len = 0;  // size_t: cannot be negative
    char* line = NULL;
    int preve = 0;
    ssize_t read;  // ssize_t: same as size_t,but can have -1
    char* fw = malloc(MAXSTRING);
    char* name = malloc(MAXSTRING);
    char* value = malloc(MAXSTRING);
    if (file == NULL) {
        printf("\nFile not found. Exiting...\n");
        exit(ERROR);
    }

    while ((read = getline(&line, &len, file)) != -1) {
        linec++;
        for (int l = 0; l < read; l++) {
            if (line[l] != ' ') {
                fw[l] = line[l];
                preve++;
            } else {
                printf("\n");
                break;
            }
        }
        if (fw[0] != NULL) {
            for (int l = preve + 1; l < read; l++) {
                if (line[l] != ' ') {
                    name[pos] = line[l];
                    pos++;
                    preve++;
                } else {
                    pos = 0;
                    break;
                }
            }
        }
        if (name != NULL) {
            for (int l = preve + 1; l < read; l++) {
                if (we == false && line[l] == '=') {
                    we = true;
                    l++;
                } else if (we == true) {
                    if (line[l] != ' ') {
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
                printf("Found %s with name %s,value %s in line %i", types[l],
                       name, value, linec);
            }
        }
        preve = 0;
        memset(name, NULL, sizeof(name));
        memset(value, NULL, sizeof(value));
        memset(fw, NULL, sizeof(fw));
        if (line[0] == '/') {
            printf("\n");
        }
        if (line) {
            free(line);  // memory managament
        }
    }

    fclose(file);
    return "SUCCESS";
}

