#include <stdio.h>
#include "util.h"
#include "amath.h"

#include "amath.leg.c"

struct peg_data *mk_peg_data(const char *input)
{
	struct peg_data *D = malloc(sizeof(struct peg_data));

	if (D == NULL)
		return NULL;

	D->input = input;
	D->result = mk_empty(NODE_RAW);

	return D;
}

char *amath_to_mathml(const char *text)
{
	yycontext g;
	char *result;
	struct peg_data *data;

	data = mk_peg_data(text);

	if (strlen(text) <= 0 || data == NULL)
		return NULL;

	memset(&g, 0, sizeof(yycontext));
	g.data = data;
	while (yyparse(&g));
	result = strdup(data->result->text);
	yyrelease(&g);
	free_node(data->result);
	free(data);

	return result;
}
