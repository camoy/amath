%include{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "strip.c"
#include "symtypes.h"
}

%token_type {const struct sym*}

%syntax_error
{
	printf("Problem");
}

start ::= e(A) .
{
	printf("%s", A->str);
}

v(A) ::= IDENTIFIER(B) .
{
	struct sym *new = malloc(sizeof(struct sym));
	char *str;
	asprintf(&str, "<mi>%s</mi>", B->str);
	new->str = str;
	A = new;
}
v(A) ::= NUMBER(B) .
{
	struct sym *new = malloc(sizeof(struct sym));
	char *str;
	asprintf(&str, "<mn>%s</mn>", B->str);
	new->str = str;
	A = new;
}
v(A) ::= OPERATOR(B) .
{
	struct sym *new = malloc(sizeof(struct sym));
	char *str;
	asprintf(&str, "<mo>%s</mo>", B->str);
	new->str = str;
	A = new;
}
v(A) ::= TEXT(B) .
{
	struct sym *new = malloc(sizeof(struct sym));
	char *str;
	asprintf(&str, "<mtext>%s</mtext>", B->str);
	new->str = str;
	A = new;
}

s(A) ::= v(B). { A = B; }
s(A) ::= LEFT(B) e(C) RIGHT(D) .
{
	struct sym *new = malloc(sizeof(struct sym));
	char *str;
	asprintf(&str, "<mrow>%s%s%s</mrow>", B->str, C->str, D->str);
	new->str = str;
	A = new;
}

s(A) ::= ACCENT(B) s(C) .
{
	struct sym *new = malloc(sizeof(struct sym));
	char *str;

	if (B->pos == 2) /* TOK_over */
		asprintf(&str, "<mover>%s<mo>%s</mo></mover>", C->str, B->str);
	else
		asprintf(&str, "<munder>%s<mo>%s</mo></munder>", C->str, B->str);

	new->str = str;
	A = new;
}

s(A) ::= UNARY(B) s(C) .
{
	struct sym *new = malloc(sizeof(struct sym));
	char *str;
	asprintf(&str, "<m%s>%s</m%s>", B->str, strip_brackets(C->str), B->str);
	new->str = str;
	A = new;
}

s(A) ::= BINARY(B) s(C) s(D) .
{
	struct sym *new = malloc(sizeof(struct sym));
	char *str;
	asprintf(&str, "<m%s>%s%s</m%s>", B->str, strip_brackets(C->str), strip_brackets(D->str), B->str);
	new->str = str;
	A = new;
}

i(A) ::= s(B). { A = B; }
i(A) ::= s(B) INFIX(C) s(D) .
{
	struct sym *new = malloc(sizeof(struct sym));
	char *str;
	asprintf(&str, "<m%s>%s%s</m%s>", C->str, strip_brackets(B->str), strip_brackets(D->str), C->str);
	new->str = str;
	A = new;
}

e(A) ::= i(B). { A = B; }
e(A) ::= i(B) e(C) .
{
	struct sym *new = malloc(sizeof(struct sym));
	char *str;
	asprintf(&str, "%s%s", B->str, C->str);
	new->str = str;
	A = new;
}
