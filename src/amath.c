#include <stdio.h>
#include "util.h"
#include "amath.h"

#include "amath.leg.c"

struct greg_data *mk_greg_data(const char *input)
{
	struct greg_data *D = malloc(sizeof(struct greg_data));

	D->input = input;
	D->result = NULL;

	return D;
}

char *amath_to_mathml(const char *text)
{
	GREG g;
	char *result;

	if (strlen(text) <= 0)
		return NULL;

	yyinit(&g);
	g.data = mk_greg_data(text);
	while (yyparse(&g));
	result = ((struct greg_data*) g.data)->result;
	yydeinit(&g);

	return result;
}
