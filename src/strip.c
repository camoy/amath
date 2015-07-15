#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *strip_brackets(const char *src)
{
	switch(src[6]){
		case '(':
		case '[':
		case '{':
		{
			char *str2;
			char *str = strndup(src+7, sizeof(char)*(strlen(src)-15));
			asprintf(&str2, "<mrow>%s</mrow>", str);
			free(str);
			return str2;
		}
	}
	return strdup(src);
}

char *strip_quotes(const char *src)
{
	if (src[0] == '"')
		return strndup(src+1, sizeof(char)*(strlen(src)-2));
	else
		return strdup(src);
}
