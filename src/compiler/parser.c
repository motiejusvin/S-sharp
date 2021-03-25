#include "parser.h"

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SUCCESS 1
#define ERROR -1
#define WARN -2
#define MAXTYPE 5
#define MAXSTRING 1024
#define MAXVARS 32000
int varindx = 0;

struct Variable {
    char vartype[MAXSTRING];
    char varname[MAXSTRING];
    char varval[MAXSTRING];
} variable;

char types[MAXTYPE][64] = {"sveikasis", "dvejetaine", "nesveikasis", "siulas",
                           "raide"};
struct Variable vars[MAXVARS];

int skip32(char* a, int p) {
    while (a[p] == 32) {
        p++;
    }
    return p;
}

char* readfile(FILE* file) {
    int linepos = 0;                  // possition in the line array
    bool we = false;                  // was equal
    short pos = 0;                    // position for array
    int linec = 0;                    // line number
    size_t len = 0;                   // size_t: cannot be negative
    char* line;                       // lines content
    ssize_t read;                     // ssize_t: same as size_t,but can have -1
    char* type = malloc(MAXSTRING);   // type of the variable
    char* name = malloc(MAXSTRING);   // name of the variable
    char* value = malloc(MAXSTRING);  // value of the varible
    if (file == NULL) {
        printf("\nFile not found. Exiting...\n");
        exit(ERROR);
    }
    clock_t start = clock();
    while ((read = getline(&line, &len, file)) !=
           -1) {  // Kol yra i ka ziureti, tol daryk....
        if (varindx > MAXVARS - 1) {
            varindx = 0;
        }
        linec++;
        if (read > 0) {
            while (line[linepos] != 32) {
                type[pos] = line[linepos];
                linepos++, pos++;
            }
            pos = 0;
            linepos = skip32(line, linepos);
            while (line[linepos] != 32) {
                name[pos] = line[linepos];
                linepos++, pos++;
            }
            pos = 0;
            if (strcmp(type, "siulas") == 0) {
                while (line[linepos] != 34) {
                    linepos++;
                }
                linepos++;
                while (line[linepos] != 34) {
                    value[pos] = line[linepos];
                    pos++, linepos++;
                }
            } else if (strcmp(type, "nesveikasis") == 0 ||
                       strcmp(type, "sveikasis") == 0) {
                while (line[linepos] != '=') {
                    linepos++;
                }
                linepos++;
                skip32(line, linepos);
                linepos++;
                while (line[linepos] != 32) {
                    if (line[linepos] >= 48 && line[linepos] <= 57) {
                        value[pos] = line[linepos];
                    } else if (line[linepos] == '\n') {
                        break;
                    } else {
                        printf("WRONG TYPE. Got: %c,which is not an integer\n",
                               linepos[line]);
                        return "ERROR";
                        exit(0);
                    }
                    pos++, linepos++;
                }
            } else {
                while (line[linepos] != '=') {
                    linepos++;
                }
                linepos++;
                while (line[linepos] != 32) {
                    value[pos] = line[linepos];
                    pos++, linepos++;
                }
            }
            strcpy(vars[varindx].vartype, type);
            strcpy(vars[varindx].varname, name);
            strcpy(vars[varindx].varval, value);

            for (int l = 0; l < MAXTYPE; l++) {
                if (strcmp(types[l], type) == 0) {
                    printf("Found %s with name %s,value %s in line %i\n",
                           vars[varindx].vartype, vars[varindx].varname,
                           vars[varindx].varval, linec);
                    break;
                }
            }
            /*
            For debuging
            */
            if (strlen(vars[varindx].vartype) > 5 &&
                strlen(vars[varindx].varname) > 0) {
                varindx++;
            } else {
                return "ERROR";
            }
            linepos = 0, pos = 0;
            memset(name, '\0', sizeof(&name));
            memset(value, '\0', sizeof(&value));
            memset(type, '\0', sizeof(&type));
            if (line[0] == '/') {
                printf("\n");
            }
        }
    }
    clock_t end = clock();
    printf("\ntime to execute:%f s\n",
           (double)((end - start) / (double)CLOCKS_PER_SEC));
    fclose(file);
    free(line);
    return "SUCCESS";
}

