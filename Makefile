CC = gcc
PREFIX = /usr/local
BUILD = build
SRC = src
TEST = test
CFLAGS = -Wall -ansi -g -D _GNU_SOURCE -fPIC -O3
BINARY = $(BUILD)/amath
LIBRARY = $(BUILD)/libamath.so
SOURCES = $(SRC)/amath.c $(SRC)/main.c $(SRC)/util.c
OBJECTS = $(BUILD)/amath.o $(BUILD)/main.o $(BUILD)/util.o
UNITS = "https://raw.githubusercontent.com/asciimath/asciimathml/master/test/unittests.js"

# phony targets

.PHONY: all otest test memory install uninstall clean

all: $(LIBRARY) $(BINARY)

test: $(BINARY)
	@bash $(TEST)/test.sh

otest: $(BINARY) $(TEST)/unittests.js
	@perl -n $(TEST)/otest.pl $(TEST)/unittests.js

memory: $(BINARY)
	@bash $(TEST)/memory.sh

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

# test dependencies

$(TEST)/unittests.js:
	wget $(UNITS) -O $@

.SUFFIXES:
