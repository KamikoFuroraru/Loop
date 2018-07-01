#include <stdio.h>
#include <stdlib.h>

#include "interpreter.h"

void readFile(char *, char *);
int sumFile(char *);

int main(int argc, char *argv[]) {

    if (argc != 4) {
        printf("Use format like this: Loop.exe input.txt output.txt result.txt\n");
        exit(1);
    }

    char *inputProgram = argv[1];
    char *inputVariables = argv[2];
    char *result = argv[3];

    int amountFile = sumFile(inputProgram);
    char *memory = (char *) malloc(amountFile + 1);         // Выделяет блок памяти и возвращает указатель на начало блока

    if (memory == NULL) {
        printf("Memory allocation error\n");
        exit(2);
    }

    readFile(inputProgram, memory);
    interpret(memory, inputVariables, result);              // memory - начальный символ потока

    return 0;
}

int sumFile(char *fileName) {
    int sum = 0;
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Can't read file\n");
        exit(3);
    }

    int sign;
    while (sign != EOF) {                                   // Возвращает 1, если был достигнут конец файла
        sign = fgetc(file);
        sum++;
    }
    fclose(file);
    return sum;
}

void readFile(char *fileName, char *memory) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Can't read file\n");
        exit(3);
    }
    char *sign = memory;
    while (feof(file) == 0) {
        *sign = (char) getc(file);
        sign++;
    }
    *(sign - 1) = '\0';
    fclose(file);
}
