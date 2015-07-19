#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

struct amath_node *scan(char **cursor_ptr, int l);
void* ParseAlloc(void* (*allocProc)(size_t));
void Parse(void*, int, struct amath_node*, char**);
void ParseFree(void*, void(*freeProc)(void*));

char *amath_asciimath_to_mathml(char *text, size_t len)
{
	void *parser = ParseAlloc(malloc);
	char **cursor_ptr = &text;
	struct amath_node *cur_node;
	char *f;

	do {
		cur_node = scan(cursor_ptr, len);
		if (cur_node->extra == AMATH_ignore)
			continue;
		Parse(parser, cur_node->token, cur_node, &f);
	} while (cur_node->token != 0);

	ParseFree(parser, free);

	return f;
}
