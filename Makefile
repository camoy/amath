CC = gcc
PREFIX = /usr/local
BUILD = build
SRC = src
CFLAGS = -g -D _GNU_SOURCE -fPIC
BINARY = $(BUILD)/amath
LIBRARY = $(BUILD)/libamath.so
SOURCES = $(wildcard $(SRC)/*.c)
HEADERS = $(wildcard $(SRC)/*.h)
OBJECTS = $(patsubst $(SRC)/%.c,$(BUILD)/%.o,$(SOURCES))

all: $(LIBRARY) $(BINARY)

test:
	@bash test/test.sh

install: $(LIBRARY) $(BINARY)
	install -m 0755 $(BINARY) $(PREFIX)/bin
	install -m 0755 $(LIBRARY) $(PREFIX)/lib
	install -m 0644 $(SRC)/amath.h $(PREFIX)/include

uninstall:
	rm -f $(PREFIX)/bin/amath
	rm -f $(PREFIX)/lib/libamath.so
	rm -f $(PREFIX)/include/amath.h

$(SRC)/amath.c: $(SRC)/amath.leg
	leg -o $@ $<

$(BINARY): $(OBJECTS)
	$(CC) -o $(BINARY) $(OBJECTS)

$(LIBRARY): $(OBJECTS)
	$(CC) -shared -o $(LIBRARY) $(filter-out $(BUILD)/main.o, $(OBJECTS))

$(BUILD)/%.o: $(SRC)/%.c $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)

.PHONY: all test install uninstall clean
