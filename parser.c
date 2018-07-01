#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "parser.h"

char *stream;
struct words word;
struct keywords keyword[3] = {{"LOOP", LOOP}, {"DO", DO}, {"END", END}};

void initWord() {
    char *t = word.name;
    word.form = 0;
    word.type = 0;

    while (*stream == ' ' || *stream == '\t') stream++;

    if (*stream == 0) {                                             // Проверка конца программы
        *word.name = 0;
        word.form = THEEND;
        return;
    }

    if (strchr(":=+-;\n", *stream)) {                               // Поиск первого вхождения символа в строку
        if (*stream == ':') {                                       // Проверка оператора присваивания
            *t++ = *stream++;
            if (*stream == '=') {
                *t++ = *stream++;
                *t = '\0';
            } else {
                printf("Expected = in construction := \n");
                exit(5);
            }
        }
        else if (*stream == '=') {
            printf("Expected := construction\n");
            exit(5);
        }
        else if (*stream == '\n') {                                 //Проверка конца строки
            *t++ = *stream++;
            *t = '\0';
            return;
        }
        else {                                                      // Оператор + или -
            *t++ = *stream++;
            *t = '\0';
        }
        word.type = OPERATOR;
        return;
    }

    if (isdigit(*stream)) {                                         // Проверка на число
        while (!strchr(" :+-=;\r\n", *stream)) *t++ = *stream++;
        *t = '\0';
        word.type = CONSTANT;
        return;
    }

    if (isalpha(*stream)) {                                         // Проверка на слово
        while (!strchr(" :+-=\r\n", *stream)) *t++ = *stream++;

        *t = '\0';
        for (int i = 0; *keyword[i].name; i++) {                    // Сравниваем полученное слово с ключевыми и решаем, оно это или переменная
            if (strcmp(keyword[i].name, word.name) == 0) word.form = keyword[i].form; // Сравниваем поочередно каждую пару символов (возвращает 0, если слова идентичны)
        }

        if (word.form) word.type = KEYWORD;
        else word.type = VARIABLE;

        return;
    }
    printf("Syntax error\n");
    exit(6);
}
