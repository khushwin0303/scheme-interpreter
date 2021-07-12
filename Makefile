#To run, put this file together with lexer.h, and lexer.c
#in the same directory. Run "make". Then the executable
#is "schemer," which just takes a line of input and
#breaks it up into tokens.

scheme: main.o parser.o lexer.o listFunctions.o
	gcc -o scheme main.o parser.o lexer.o listFunctions.o

main.o: main.c
	gcc -c main.c

parser.o: parser.c
	gcc -c parser.c

lexer.o: lexer.c
	gcc -c lexer.c

listFunctions.o: listFunctions.c
	gcc -c listFunctions.c

clean:
	rm -f *~ *.o *.a

#^^^^^^This space must be a TAB!!.

