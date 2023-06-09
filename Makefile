main: main.o matchUserInput.o FilesystemChecks.o
	gcc main.o matchUserInput.o FilesystemChecks.o -o main

main.o: main.c
	gcc -c main.c
FilesystemChecks.o: FilesystemChecks.c FilesystemChecks.h
	gcc -c FilesystemChecks.c
matchUserInput.o: matchUserInput.c matchUserInput.h
	gcc -c matchUserInput.c
	
clean:
	rm *.o main
