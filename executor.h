#ifndef EXECUTOR_H_INCLUDED
#define EXECUTOR_H_INCLUDED

struct variable {
    char name[100];         // Возьмем например длинной 100
    int value;
};

struct loopStack {
    int index;              // Счетчик цикла
    int count;              // Конечное значение
    char *bodyLoop;
};

void loopPush(struct loopStack);
struct loopStack loopPop();
struct variable *findVar(char*);

void assignment();
void exeLoop();
void exeEnd();

#endif // EXECUTOR_H_INCLUDED
