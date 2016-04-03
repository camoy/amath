#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "amath.h"

#define BUF_SIZE	1024

int main(int argc, char *argv[])
{
	int i, ns = 0;
	char buffer[BUF_SIZE];
	char *content = "";

	/* flags */
	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "--xml-ns")) ns = 1;
	}

	/* read stdin */
	while (fgets(buffer, BUF_SIZE, stdin))
		asprintf(&content, "%s%s", content, buffer);

	/* print result */
	char *result = amath_to_mathml(content);

	if (ns)
		printf("<math xmlns=\"http://www.w3.org/1998/Math/MathML\">%s</math>\n", result);
	else
		printf("<math>%s</math>\n", result);

	/* free memory */
	if (strlen(result) > 0) free(result);
	if (strlen(content) > 0) free(content);
}
