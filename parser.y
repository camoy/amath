%include{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "strip.c"
}

%token_type {char*}

%syntax_error
{
	printf("Problem");
}

start ::= e(A) .
{
	printf(A);
}

v(A) ::= IDENTIFIER(B) .
{
	char *str;
	asprintf(&str, "<mi>%s</mi>", B);
	A = str;
}
v(A) ::= NUMBER(B) .
{
	char *str;
	asprintf(&str, "<mn>%s</mn>", B);
	A = str;
}
v(A) ::= OPERATOR(B) .
{
	char *str;
	asprintf(&str, "<mo>%s</mo>", B);
	A = str;
}

l(A) ::= LEFT(B). { A = B; }
r(A) ::= RIGHT(B). { A = B; }

s(A) ::= v(B). { A = B; }
s(A) ::= l(B) e(C) r(D) .
{
	char *str;
	asprintf(&str, "<mrow>%s%s%s</mrow>", B, C, D);
	A = str;
}

s(A) ::= ACCENT_OVER(B) s(C) .
{
	char *str;
	asprintf(&str, "<mover>%s<mo>%s</mo></mover>", C, B);
	A = str;
}

s(A) ::= ACCENT_UNDER(B) s(C) .
{
	char *str;
	asprintf(&str, "<munder>%s<mo>%s</mo></munder>", C, B);
	A = str;
}

s(A) ::= UNARY(B) s(C) .
{
	char *str;
	asprintf(&str, "<m%s>%s</m%s>", B, strip_brackets(C), B);
	A = str;
}

s(A) ::= BINARY(B) s(C) s(D) .
{
	char *str;
	asprintf(&str, "<m%s>%s%s</m%s>", B, strip_brackets(C), strip_brackets(D), B);
	A = str;
}

i(A) ::= s(B). { A = B; }
i(A) ::= s(B) SUB s(C) .
{
	char *str;
	asprintf(&str, "<msub>%s%s</msub>", B, strip_brackets(C));
	A = str;
}
i(A) ::= s(B) SUP s(C) .
{
	char *str;
	asprintf(&str, "<msup>%s%s</msup>", B, strip_brackets(C));
	A = str;
}
i(A) ::= s(B) SUB s(C) SUP s(D) .
{
	char *str;
	asprintf(&str, "<msubsup>%s%s%s</msubsup>", B, strip_brackets(C), strip_brackets(D));
	A = str;
}
i(A) ::= OPERATOR_UNDER_OVER(B) SUB s(C) SUP s(D) .
{
	char *str;
	asprintf(&str, "<munderover><mo>%s</mo>%s%s</munderover>", B, strip_brackets(C), strip_brackets(D));
	A = str;
}

e(A) ::= i(B). { A = B; }
e(A) ::= i(B) e(C) .
{
	char *str;
	asprintf(&str, "%s%s", B, C);
	A = str;
}
e(A) ::= i(B) DIV i(C) .
{
	char *str;
	asprintf(&str, "<mfrac>%s%s</mfrac>", strip_brackets(B), strip_brackets(C));
	A = str;
}
