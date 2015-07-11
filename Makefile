.PHONY: all clean

all: main.o parser.o
	$(CC) -o main main.o parser.o

main.o: main.c parser.h

main.c: main.re
	re2c main.re > main.c

parser.o: parser.h parser.c

parser.h parser.c: parser.y
	lemon parser.y

clean:
	rm -f *.o
	rm -f parser.h parser.c parser.out main main.c
