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

    if (*stream == 0) {                                             // �������� ����� ���������
        *word.name = 0;
        word.form = THEEND;
        return;
    }

    if (strchr(":=+-;\n", *stream)) {                               // ����� ������� ��������� ������� � ������
        if (*stream == ':') {                                       // �������� ��������� ������������
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
        else if (*stream == '\n') {                                 //�������� ����� ������
            *t++ = *stream++;
            *t = '\0';
            return;
        }
        else {                                                      // �������� + ��� -
            *t++ = *stream++;
            *t = '\0';
        }
        word.type = OPERATOR;
        return;
    }

    if (isdigit(*stream)) {                                         // �������� �� �����
        while (!strchr(" :+-=;\r\n", *stream)) *t++ = *stream++;
        *t = '\0';
        word.type = CONSTANT;
        return;
    }

    if (isalpha(*stream)) {                                         // �������� �� �����
        while (!strchr(" :+-=\r\n", *stream)) *t++ = *stream++;

        *t = '\0';
        for (int i = 0; *keyword[i].name; i++) {                    // ���������� ���������� ����� � ��������� � ������, ��� ��� ��� ����������
            if (strcmp(keyword[i].name, word.name) == 0) word.form = keyword[i].form; // ���������� ���������� ������ ���� �������� (���������� 0, ���� ����� ���������)
        }

        if (word.form) word.type = KEYWORD;
        else word.type = VARIABLE;

        return;
    }
    printf("Syntax error\n");
    exit(6);
}
