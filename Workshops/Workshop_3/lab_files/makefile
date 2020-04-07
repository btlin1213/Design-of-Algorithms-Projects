main: racecar.o racecar_test.o
	gcc -Wall -o program racecar.o racecar_test.o
racecar.o: racecar.c racecar.h
	gcc -Wall -c racecar.c
racecar_test.o: racecar_test.c racecar.h
	gcc -Wall -c racecar_test.c

list_program: list.o test.o
	gcc -Wall -o list_program list.o test.o
list.o: list.c list.h
	gcc -Wall -c list.c
test.o: test.c list.h
	gcc -Wall -c test.c