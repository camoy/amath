%include{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "strip.h"
#include "types.h"
}

%token_type {struct amath_node*}
%extra_argument {char **f}

%syntax_error
{
	printf("Problem");
	exit(0);
}

start ::= e(B) .
{
	*f = B->str;
	free(B);
}

v(A) ::= IDENTIFIER(B) .
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;
	asprintf(&str, "<mi>%s</mi>", B->str);
	new->str = str;
	free(B->str); free(B);
	A = new;
}
v(A) ::= NUMBER(B) .
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;
	asprintf(&str, "<mn>%s</mn>", B->str);
	new->str = str; new->extra = B->extra;
	free(B->str); free(B);
	A = new;
}
v(A) ::= OPERATOR(B) .
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;
	asprintf(&str, "<mo>%s</mo>", B->str);
	new->str = str; new->extra = B->extra;
	A = new;
}
v(A) ::= TEXT(B) .
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;
	char *unquoted = strip_quotes(B->str);
	asprintf(&str, "<mtext>%s</mtext>", unquoted);
	new->str = str; new->extra = B->extra;
	free(unquoted); free(B->str); free(B);
	A = new;
}

s(A) ::= v(B). { A = B; }
s(A) ::= LEFT(B) e(C) RIGHT(D) .
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;
	asprintf(&str, "<mrow>%s%s%s</mrow>", B->str, C->str, D->str);
	new->str = str;
	free(C->str); free(C);
	A = new;
}

s(A) ::= ACCENT(B) s(C) .
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;

	if (B->extra == AMATH_over)
		asprintf(&str, "<mover>%s<mo>%s</mo></mover>", C->str, B->str);
	else
		asprintf(&str, "<munder>%s<mo>%s</mo></munder>", C->str, B->str);

	new->str = str;
	free(C->str); free(C);
	A = new;
}

s(A) ::= UNARY(B) s(C) .
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;
	char *unbracketed = strip_brackets(C->str);
	asprintf(&str, "<m%s>%s</m%s>", B->str, unbracketed, B->str);
	new->str = str;
	free(unbracketed); free(C->str); free(C);
	A = new;
}

s(A) ::= BINARY(B) s(C) s(D) .
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;
	char *unbracketed_C = strip_brackets(C->str);
	char *unbracketed_D = strip_brackets(D->str);

	/* TODO: maybe use B == syms[SYM_sqrt], check header deps */
	if(strcmp("sqrt", B->str) == 0)
		asprintf(&str, "<m%s>%s%s</m%s>", B->str, unbracketed_C, unbracketed_D, B->str);
	else
		asprintf(&str, "<m%s>%s%s</m%s>", B->str, unbracketed_D, unbracketed_C, B->str);

	new->str = str;
	free(C->str); free(C); free(D->str); free(D); free(unbracketed_C); free(unbracketed_D);
	A = new;
}

i(A) ::= s(B). { A = B; }
i(A) ::= s(B) DIV s(C) .
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;
	char *unbracketed_B = strip_brackets(B->str);
	char *unbracketed_C = strip_brackets(C->str);
	asprintf(&str, "<mfrac>%s%s</mfrac>", unbracketed_B, unbracketed_C);
	new->str = str;
	free(B->str); free(B); free(C->str); free(C); free(unbracketed_B); free(unbracketed_C);
	A = new;
}
i(A) ::= s(B) SUB s(C) .
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;
	char *unbracketed = strip_brackets(C->str);
	if (B->extra == AMATH_underover)
		asprintf(&str, "<munder>%s%s</munder>", B->str, unbracketed);
	else
		asprintf(&str, "<msub>%s%s</msub>", B->str, unbracketed);
	new->str = str;
	free(B->str); free(B); free(C->str); free(C); free(unbracketed);
	A = new;
}
i(A) ::= s(B) SUP s(C) .
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;
	char *unbracketed = strip_brackets(C->str);
	asprintf(&str, "<msup>%s%s</msup>", B->str, unbracketed);
	new->str = str;
	free(B->str); free(B); free(C->str); free(C); free(unbracketed);
	A = new;
}
i(A) ::= s(B) SUB s(C) SUP s(D) .
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;
	char *unbracketed_C = strip_brackets(C->str);
	char *unbracketed_D = strip_brackets(D->str);
	if (B->extra == AMATH_underover)
		asprintf(&str, "<munderover>%s%s%s</munderover>", B->str, unbracketed_C, unbracketed_D);
	else
		asprintf(&str, "<msubsup>%s%s%s</msubsup>", B->str, unbracketed_C, unbracketed_D);
	new->str = str;
	free(B->str); free(B);
	free(C->str); free(C); free(D->str); free(D); free(unbracketed_C); free(unbracketed_D);
	A = new;
}
i(A) ::= matrixList(B). { A = B; }

matrixList(A) ::= LEFT(B) commaList(C) COMMA matrixListLoop(D) RIGHT(E).
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;
	asprintf(&str, "<mrow><mo>%s</mo><mtable>%s%s</mtable><mo>%s</mo></mrow>", B->str, C->str, D->str, E->str);
	new->str = str;
	free(C->str); free(C); free(D->str); free(D);
	A = new;

}

matrixListLoop(A) ::= commaList(B). { A = B; }
matrixListLoop(A) ::= commaList(B) COMMA matrixListLoop(C).
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;
	asprintf(&str, "%s%s", B->str, C->str);
	new->str = str;
	free(B->str); free(B); free(C->str); free(C);
	A = new;
}

commaList(A) ::= LEFT i(B) COMMA commaListLoop(C) RIGHT.
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;
	asprintf(&str, "<mtr><mtd>%s</mtd>%s</mtr>", B->str, C->str);
	new->str = str;
	free(B->str); free(B); free(C->str); free(C);
	A = new;

}

commaListLoop(A) ::= i(B).
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;
	asprintf(&str, "<mtd>%s</mtd>", B->str);
	new->str = str;
	free(B->str); free(B);
	A = new;
}

commaListLoop(A) ::= i(B) COMMA commaListLoop(C).
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;
	asprintf(&str, "<mtd>%s</mtd>%s", B->str, C->str);
	new->str = str;
	A = new;
}

e(A) ::= i(B). { A = B; }
e(A) ::= i(B) e(C) .
{
	struct amath_node *new = malloc(sizeof(struct amath_node));
	char *str;
	asprintf(&str, "%s%s", B->str, C->str);
	new->str = str;
	free(B->str); free(C->str);
	free(B); free(C);
	A = new;
}
