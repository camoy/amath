#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "scanner.c"

void* ParseAlloc(void* (*allocProc)(size_t));
void Parse(void*, int, const struct sym*);
void ParseFree(void*, void(*freeProc)(void*));

int main(int argc, char **argv)
{
	void *parser = ParseAlloc(malloc);
	char **cursor_ptr;
	const struct sym *my_sym;
	int l;

	if (argc > 1) {
		cursor_ptr = &argv[1];
		l = strlen(argv[1]);
		do {
			my_sym = scan(cursor_ptr, l);
			Parse(parser, my_sym->type, my_sym);
		} while (my_sym != &syms[SYM_EOL]);
		ParseFree(parser, free);
	}
	else {
		fprintf(stderr, "%s <expr>\n", argv[0]);
		return 1;
	}
}
