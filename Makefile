CC = gcc
BUILD = build
SRC = src
BINARY = $(BUILD)/amath
SOURCES = $(wildcard $(SRC)/*.c)
HEADERS = $(wildcard $(SRC)/*.h)
OBJECTS = $(patsubst $(SRC)/%.c,$(BUILD)/%.o,$(SOURCES))

all: $(BINARY)

$(SRC)/parser.c: $(SRC)/parser.y
	lemon $<

$(SRC)/scanner.c: $(SRC)/scanner.re
	re2c $< > $@

$(BINARY): $(OBJECTS)
	$(CC) -o $(BINARY) $(OBJECTS)

$(BUILD)/%.o: $(SRC)/%.c $(BUILD)
	$(CC) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)

.PHONY: all clean
