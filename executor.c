#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "parser.h"
#include "executor.h"

char *stream;
int amountOfVar = 0;                                        // Количество переменных
int loopNumber;                                             // Индекс начала стека

struct loopStack loop[30];                                  // Стек для цикла. Возьмем за глубину 30 вложений
struct words word;
struct variable *memoryPointer;                             // Указатель начала хренения в памяти

void loopPush(struct loopStack stack) {                     // Положить элемент в стек
    if (loopNumber > 30) {
        printf("Exceeded allowed number of cycles\n");
        exit(7);
    }
    loop[loopNumber] = stack;
    loopNumber++;
}

struct loopStack loopPop() {                                // Взять элемент с вершины стека
    loopNumber--;
    if (loopNumber < 0) {
        printf("Can't find END in LOOP construction or excess ; construction\n");
        exit(4);
    }
    return (loop[loopNumber]);
}

struct variable *findVar(char *name) {                      // Ищет переменную по имени
    int i = 1;
    struct variable *t = memoryPointer;
    while (i <= amountOfVar) {
        if (!strcmp(name, (*t).name)) return t;             // Сравниваем пару символов
        i++;
        t++;
    }
    return NULL;
}

struct variable *addVar(char *name) {                       // Добавляет переменную
    amountOfVar++;
    memoryPointer = (struct variable *) realloc(memoryPointer, sizeof(struct variable) * amountOfVar); // Перераспределение блоков памяти
    struct variable *bufferPointer = memoryPointer;

    int i = 1;
    while (i < amountOfVar) {
        bufferPointer++;
        i++;
    }

    struct variable *result = bufferPointer;
    strcpy((*result).name, name);                           // Копируем
    (*result).value = 0;

    return result;
}

void cond(int *result) {                                    // Проверяет текущее слово
    struct variable *var = findVar(word.name);

    switch (word.type) {
        case VARIABLE:
            if (var == NULL || (*var).value == 0) *result = 0;
            *result = (*var).value;
            initWord();
            return;
        case CONSTANT:
            *result = atoi(word.name);                       // Преобразуем строку в int
            initWord();
            if (*word.name != ';') {
                printf("Can't find ; construction\n");
                exit(8);
            }
            return;
        default:
            printf("Syntax error\n");
            exit(6);
        }
}

void operation(char operator, int *a, int *b) {              // Операции
    switch (operator) {
        case '-':
            *a = *a - *b;
            break;
        case '+':
            *a = *a + *b;
            break;
        default:
            break;
    }
}

void doOperation(int *result) {                             // Выполняет операции
    initWord();
    char operator;
    cond(result);

    int hold;
    if ((operator = *word.name) == '+' || (operator = *word.name) == '-') {
        initWord();
        cond(&hold);
        operation(operator, result, &hold);
    }
}

void assignment() {                                          // Присваивает значение переменной
    int value;
    struct variable *var;

    if ((var = findVar(word.name)) == 0) var = addVar(word.name);
    initWord();                                             // Считывает символ равенства
    doOperation(&value);                                    // Выполняет операцию или считывает присваемое значение
    (*var).value = value;                                   // Присвоить значение
}

void exeLoop() {
    struct loopStack stack;

    stack.index = 1;                                        // Начало отсчета цикла
    int loopIterations = 0;                                 // Переменная счетчика

    doOperation(&loopIterations);                           // Считывает управляющую переменную

    stack.count = loopIterations;

    if (stack.count < stack.index) {
        int counter = 0;

        while (word.form != END || counter != 0) {
            switch (word.form){
                case THEEND:
                    printf("Syntax error\n");
                    exit(6);
                    break;
                case LOOP:
                    counter++;
                    break;
                case END:
                    counter--;
                    break;
                default:
                    break;
            }
            initWord();
        }
    }
    if (word.form != DO) {
        printf("Can't find DO in LOOP construction or excess ; construction\n");
        exit(4);
    }
    stack.bodyLoop = stream;
    loopPush(stack);
}

void exeEnd() {
    struct loopStack stack;

    stack = loopPop();                                     // Считываем информацию о цикле

    stack.index++;
    if (stack.index > stack.count) return;                 // Завершаем

    loopPush(stack);                                       // Запомнаем информацию
    stream = stack.bodyLoop;
}
