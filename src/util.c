#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

char *input = "";

char *inner(char *src)
{
	char *a, *b, *c;
	a = strstr(src, "</mo>") + 5;
	b = strstr(src + strlen(src) - 22, "<mo>");
	*b = '\0';
	asprintf(&c, "<mrow>%s</mrow>", a);
	return c;
}

char *merror(char *input)
{
	char *error = "";
	asprintf(&error, "<merror>Error on input \"%s\".</merror>", input);
	return error;
}

void cancel(char **v, char *s0)
{
	asprintf(v, "<menclose notation=\"updiagonalstrike\">%s</menclose>", s0);
}

void matrix(char **v, char *l, char *r0, char *r)
{
	asprintf(v, "<mrow><mo>%s</mo><mtable>%s</mtable><mo>%s</mo></mrow>", l, r0, r);
}

void row(char **v, char *r0)
{
	asprintf(v, "<mtr>%s</mtr>", r0);
}

void cell(char **v, char *s0)
{
	asprintf(v, "<mtd>%s</mtd>", s0);
}

void operator(char **v, char *s0)
{
	asprintf(v, "<mo>%s</mo>", s0);
}

void greek(char **v, char *s0)
{
	asprintf(v, "<mi>&%s;</mo>", s0);
}

void identifier(char **v, char *s0)
{
	asprintf(v, "<mi>%s</mi>", s0);
}

void number(char **v, char *s0)
{
	asprintf(v, "<mn>%s</mn>", s0);
}

void msqrt(char **v, char *s0)
{
	asprintf(v, "<msqrt>%s</msqrt>", s0);
}

void text(char **v, char *s0)
{
	asprintf(v, "<mtext>%s</mtext>", s0);
}

void font(char **v, char *s0, char *t0)
{
	asprintf(v, "<mstyle mathvariant=\"%s\">%s</mstyle>", s0, t0);
}

void accent_under(char **v, char *s0, char *a0)
{
	asprintf(v, "<munder>%s<mo>%s</mo></munder>", s0, a0);
}

void accent(char **v, char *s0, char *a0)
{
	asprintf(v, "<mover>%s<mo>%s</mo></mover>", s0, a0);
}

void group(char **v, char *l, char *e, char *r)
{
	asprintf(v, "<mrow><mo>%s</mo>%s<mo>%s</mo></mrow>", l, e, r);
}

void concat(char **v, char *s0, char *e0)
{
	asprintf(v, "%s%s", s0, e0);
}

void fraction(char **v, char *s0, char *s1)
{
	asprintf(v, "<mfrac>%s%s</mfrac>", s0, s1);
}

void root(char **v, char *s0, char *s1)
{
	asprintf(v, "<mroot>%s%s</mroot>", s0, s1);
}

void color(char **v, char *s0, char *s1)
{
	asprintf(v, "<mstyle mathcolor=\"%s\">%s</mstyle>", s0, s1);
}

void stackrel(char **v, char *s0, char *s1)
{
	asprintf(v, "<mover>%s%s</mover>", s0, s1);
}

void sub(char **v, char *s0, char *s1)
{
	asprintf(v, "<msub>%s%s</msub>", s0, s1);
}

void under(char **v, char *s0, char *s1)
{
	asprintf(v, "<munder><mo>%s</mo>%s</munder>", s0, s1);
}

void sup(char **v, char *s0, char *s1)
{
	asprintf(v, "<msup>%s%s</msup>", s0, s1);
}

void subsup(char **v, char *s0, char *s1, char *s2)
{
	asprintf(v, "<msubsup>%s%s%s</msubsup>", s0, s1, s2);
}

void underover(char **v, char *s0, char *s1, char *s2)
{
	asprintf(v, "<munderover><mo>%s</mo>%s%s</munderover>", s0, s1, s2);
}

void ubrace(char **v, char *s0, char *s1)
{
	asprintf(v, "<munder><munder>%s<mo>&#x23DF;</mo></munder>%s</munder>", s0, s1);
}

void obrace(char **v, char *s0, char *s1)
{
	asprintf(v, "<mover><mover>%s<mo>&#x23DE;</mo></mover>%s</mover>", s0, s1);
}
