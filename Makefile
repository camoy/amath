.PHONY: all clean

all: main.o parser.o
	$(CC) -o main main.o parser.o

main.o: main.c parser.h scanner.c

scanner.c: scanner.re
	re2c scanner.re > scanner.c

parser.o: parser.h parser.c

parser.h parser.c: parser.y
	lemon parser.y

clean:
	rm -f *.o
	rm -f parser.h parser.c parser.out main
