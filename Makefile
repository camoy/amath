CC = gcc
PREFIX = /usr/local
BUILD = build
SRC = src
CFLAGS = -Wall -ansi -g -D _GNU_SOURCE -fPIC -O3
BINARY = $(BUILD)/amath
LIBRARY = $(BUILD)/libamath.so
SOURCES = $(SRC)/amath.c $(SRC)/main.c $(SRC)/util.c
OBJECTS = $(BUILD)/amath.o $(BUILD)/main.o $(BUILD)/util.o

# phony targets

.PHONY: all test memory install uninstall clean

all: $(LIBRARY) $(BINARY)

test:
	@bash test/test.sh

test/converter: test/converter.leg
	leg test/converter.leg -o test/converter.c
	$(CC) test/converter.c -o test/converter

test/unittests.js:
	wget 'https://raw.githubusercontent.com/asciimath/asciimathml/master/test/unittests.js' -O test/unittests.js

test/official_tests.txt: test/unittests.js test/converter
	test/converter < test/unittests.js > test/official_tests.txt

otest: test/official_tests.txt
	@bash test/official_tests.sh

memory:
	@bash test/memory.sh

install: all
	install -m 0755 $(BINARY) $(PREFIX)/bin
	install -m 0755 $(LIBRARY) $(PREFIX)/lib
	install -m 0644 $(SRC)/amath.h $(PREFIX)/include

uninstall:
	rm -f $(PREFIX)/bin/amath
	rm -f $(PREFIX)/lib/libamath.so
	rm -f $(PREFIX)/include/amath.h

clean:
	rm -rf $(BUILD)

# binary and library

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

$(LIBRARY): $(OBJECTS)
	$(CC) -shared -o $@ $(filter-out $(BUILD)/main.o, $^)

# object files

$(BUILD)/%.o: $(SRC)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

# C dependencies

$(SRC)/amath.c: $(SRC)/amath.leg.c
	touch $@

$(SRC)/amath.leg.c: $(SRC)/amath.leg
	leg -o $@ $<

.SUFFIXES:
