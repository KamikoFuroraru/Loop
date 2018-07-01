#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

// ���������
// ���� ����
#define KEYWORD 1
#define OPERATOR 3
#define VARIABLE 5
#define CONSTANT 7

// ����� ����
#define LOOP 2
#define DO 4
#define END 6
#define THEEND 8

void initWord();

struct words {
    char name[100];             // ������� �������� ������� 100
    int type;
    int form;
};

struct keywords {
    char name[5];               // ����� ������� = 4 + 1 = \0
    int form;
};

#endif // PARSER_H_INCLUDED
