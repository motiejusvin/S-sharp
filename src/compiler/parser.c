#include "parser.h"

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mlib.h"

#define SUCCESS 1
#define ERROR -1
#define WARN -2
#define MAXTYPE 5
#define MAXSTRING 1024
#define MAXVARS 32000
#define MAXFUNC 1
int varindx = 0;

struct Variable {
    char vartype[MAXSTRING];
    char varname[MAXSTRING];
    char varval[MAXSTRING];
} variable;

char types[MAXTYPE][64] = {"sveikasis", "dvejetaine", "nesveikasis", "siulas",
                           "raide"};

char Functions[MAXFUNC][256] = {"prntc"};
struct Variable vars[MAXVARS];

int skip32(char* a, int p) {
    while (a[p] == 32) {
        p++;
    }
    return p;
}

int parsevar(char* line, int linec, int linepos) {
    char* name = malloc(MAXSTRING);
    char* value = malloc(MAXSTRING);
    int pos = 0;
    linepos = skip32(line, linepos);
    while (line[linepos] != 32) {
        name[pos] = line[linepos];
        linepos++, pos++;
    }
    pos = 0;
    if (strcmp(vars[varindx].vartype, "siulas") == 0) {
        while (line[linepos] != 34) {
            linepos++;
        }
        linepos++;
        while (line[linepos] != 34) {
            value[pos] = line[linepos];
            pos++, linepos++;
        }
    } else if (strcmp(vars[varindx].vartype, "nesveikasis") == 0 ||
               strcmp(vars[varindx].vartype, "sveikasis") == 0) {
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
                return ERROR;
                exit(0);
            }
            pos++, linepos++;
        }
    } else if (strcmp(vars[varindx].vartype, "raide") == 0) {
        while (line[linepos] != 39) {
            linepos++;
        }
        linepos++;
        value[pos] = line[linepos];
        linepos++;
        if (line[linepos] != 39) {
            printf("WRONG TYPE. Got string instead of a char\n");
            return ERROR;
            exit(0);
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
    strcpy(vars[varindx].varname, name);
    strcpy(vars[varindx].varval, value);
    for (int l = 0; l < MAXTYPE; l++) {
        if (strcmp(types[l], vars[varindx].vartype) == 0) {
            printf("Found %s with name %s,value %s in line %i\n",
                   vars[varindx].vartype, vars[varindx].varname,
                   vars[varindx].varval, linec);
            break;
        }
    }
    /*
    For debuging
   */
    if (line[0] == '/') {
        printf("");
    }
    if (strlen(vars[varindx].vartype) >= 5 &&
        strlen(vars[varindx].varname) > 0) {
        return SUCCESS;
    } else {
        return ERROR;
    }
}

int isvar(char* input, int linec,int read) {
    char* type = malloc(MAXTYPE);
    int pos = 0;
    int linepos = 0;
    while (input[pos] != 32 || pos < read) {
        type[pos] = input[linepos];
        linepos++, pos++;
    }
    linepos = skip32(input,linepos);
    pos = 0;
    for (int x = 0; x < MAXTYPE; x++) {
        if (strcmp(type,types[x]) == 0) {
            strcpy(vars[varindx].vartype, type);
            int pv = parsevar(input,linec,linepos);
            if (pv == 1) {
                varindx++;
                return 1;
                break;
            } else {
                return ERROR;
            }
        }
    }
    //memset(type,'\0',sizeof(type));
    return 0;
}
char* readfile(FILE* file) {
    int linepos = 0;  // possition in the line array
    bool we = false;  // was equal
    short pos = 0;    // position for array
    int linec = 0;    // line number
    size_t len = 0;   // size_t: cannot be negative
    bool isvariable = false;
    char* line;                      // lines content
    ssize_t read;                    // ssize_t: same as size_t,but can have -1
    char* type = malloc(MAXSTRING);  // type of the variable
    int islinevar = 0;
    
    struct func {
        char function[MAXSTRING];
        char cont[MAXSTRING];
    } vart;
    
    if (file == NULL) {
        printf("\nFile not found. Exiting...\n");
        exit(ERROR);
    }
    clock_t start = clock();
    while ((read = getline(&line, &len, file)) !=
           -1) {  // Kol yra i ka ziureti, tol daryk....
        isvariable = false;
        islinevar = 0;
        if (varindx > MAXVARS - 1) {
            varindx = 0;
        }
        linec++;
        if (read > 0) {
            
            islinevar = isvar(line, linec,read);
            if (islinevar == 1) {
                isvariable = true;
            } else if (islinevar == 0) {
                isvariable = false;
            }
            else{
                return "ERROR";
            }
            pos = 0;
            if (!isvariable) {
                linepos = 0;
                pos = 0;
                while (line[linepos] != 40) {
                    vart.function[pos] = line[linepos];
                    linepos++, pos++;
                }
                if (strcmp(vart.function, "išvesti") == 0) {
                    while (line[linepos] != 34) {
                        linepos++;
                    }
                    linepos++;
                    pos = 0;
                    while (line[linepos] != 34) {
                        vart.cont[pos] = line[linepos];
                        linepos++, pos++;
                    }
                    prntc(vart.cont);
                }
            }
        }

        pos = 0;
        linepos = 0;
        memset(type, '\0', sizeof(&type));
        memset(vart.function, '\0', sizeof(vart.function));
        memset(vart.cont, '\0', sizeof(vart.cont));
    }

    /*
     clock_t end = clock();
    printf("\ntime to execute:%f s\n",
          (double)((end - start) / (double)CLOCKS_PER_SEC));

   For checking performace
   */

    fclose(file);
    free(line);
    return "SUCCESS";
}

