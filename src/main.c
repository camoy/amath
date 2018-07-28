#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "amath.h"

#define BUF_SIZE	1024

int main(int argc, char *argv[])
{
	char buffer[BUF_SIZE];
	char *content = "";

	/* read stdin */
	while (fgets(buffer, BUF_SIZE, stdin))
		asprintf(&content, "%s%s", content, buffer);

	/* print result */
	char *result = amath_to_mathml(content);

	printf("%s\n", result);

	/* free memory */
	if (strlen(result) > 0) free(result);
	if (strlen(content) > 0) free(content);

	return 0;
}
