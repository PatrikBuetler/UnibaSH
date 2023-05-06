main: main.o matchUserInput.o
	gcc main.o matchUserInput.o -o main

main.o: main.c
	gcc -c main.c

matchUserInput.o: matchUserInput.c matchUserInput.h
	gcc -c matchUserInput.c
	
clean:
	rm *.o main
