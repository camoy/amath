#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "amath.h"

#define BUF_SIZE	1024

int main(int argc, char *argv[])
{
	int i;
	int ns = 0;
	char buffer[BUF_SIZE];
	char *content = "";

	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "--xml-ns"))
			ns = 1;
	}

	while (fgets(buffer, BUF_SIZE, stdin))
		asprintf(&content, "%s%s", content, buffer);

	char *result = amath_to_mathml(content);
	if (!ns)
		printf("<math>%s</math>\n", result);
	else
		printf("<math xmlns=\"http://www.w3.org/1998/Math/MathML\">%s</math>\n", result);

	if (strlen(result) > 0) free(result);
	if (strlen(content) > 0) free(content);
}
