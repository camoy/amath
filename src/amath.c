#include <stdio.h>
#include "util.h"
#include "amath.h"

#include "amath.leg.c"

struct greg_data *mk_greg_data(const char *input)
{
	struct greg_data *D = malloc(sizeof(struct greg_data));

	if (D == NULL)
		return NULL;

	D->input = input;
	D->result = mk_node(NODE_RAW, "");

	return D;
}

char *amath_to_mathml(const char *text)
{
	GREG g;
	char *result;
	struct greg_data *data;

	data = mk_greg_data(text);

	if (strlen(text) <= 0 || data == NULL)
		return NULL;

	yyinit(&g);
	g.data = data;
	while (yyparse(&g));
	result = data->result->text;
	yydeinit(&g);

	return result;
}
