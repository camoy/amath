#include <string.h>

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
