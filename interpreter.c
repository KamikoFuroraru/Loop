#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "parser.h"
#include "executor.h"

char *stream;
int loopNumber;
struct words word;

void writeResult(char*, char*);

void interpret(char *programStream, char *outputVariables, char *result) {

    stream = programStream;
    loopNumber = 0;

    while (word.form != THEEND) {
        initWord();

        if (word.type == VARIABLE) assignment();

        if (word.type == KEYWORD) {
            switch (word.form) {
                case LOOP:
                    exeLoop();
                    break;
                case END:
                    exeEnd();
                    break;
                default:
                    break;
            }
        }
    }
    if (loopNumber != 0) {
        printf("Can't find END in LOOP construction or excess ; construction\n");
        exit(4);
    }
    writeResult(outputVariables, result);
}

void writeResult(char *outputVariables, char *result) {                     // Записывает результат
    FILE *inputFile, *outputFile;
    inputFile = fopen(outputVariables, "r");
    outputFile = fopen(result, "w");
    if (inputFile == NULL) {
        printf("Can't read file\n");
        exit(3);
    }
    char name[100];
    char *sign = name;
    while (feof(inputFile) == 0) {
        *sign = (char) getc(inputFile);
        if (*sign == '\n' || feof(inputFile)) {
            *sign = '\0';
            struct variable *var = findVar(name);
            if (var == NULL) {
                sign++;
                continue;
            }
            fprintf(outputFile, "%s = %d\n", (*var).name, (*var).value);
            sign = name;
        } else sign++;
    }
}
