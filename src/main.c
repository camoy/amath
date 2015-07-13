#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "amath.h"

#define AMATH_VERSION_STRING	"0.0.0"
#define AMATH_COPYRIGHT_STRING	"2015 Cameron Moy"
#define BUF_SIZE	1024

int main(int argc, char *argv[])
{
	char buffer[BUF_SIZE];
	char *content = "";

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--version") == 0) {
			printf("amath %s\n", AMATH_VERSION_STRING);
			printf("(c) %s\n", AMATH_COPYRIGHT_STRING);
			exit(0);
		}
	}

	while (fgets(buffer, BUF_SIZE, stdin))
		asprintf(&content, "%s%s", content, buffer);

	char *result = amath_asciimath_to_mathml(content, strlen(content));
	printf("%s\n", result);

	free(content);
	free(result);
}
