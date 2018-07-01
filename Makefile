Loop.exe : main.o interpreter.o parser.o executor.o
	gcc -o Loop main.o interpreter.o parser.o executor.o
main.o : main.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o main.o main.c
interpreter.o : interpreter.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o interpreter.o interpreter.c
parser.o : parser.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o parser.o parser.c
executor.o : executor.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o executor.o executor.c
