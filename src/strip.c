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
			char *str = malloc(sizeof(char)*(strlen(src)-14));
			strlcat(str, src+7, sizeof(char)*(strlen(src)-14));
			asprintf(&str2, "<mrow>%s</mrow>", str);
			return str2;
		}
	}
	return (char*)src;
}

char *strip_quotes(const char *src)
{
	if (src[0] == '"')
		return strndup(src+1, sizeof(char)*(strlen(src)-2));
	else
		return (char*)src;
}
