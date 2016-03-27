#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

struct node *mk_node(char *str)
{
	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	text = malloc(sizeof(char) * strlen(str) + 1);
	n->type = NODE_OP;
	n->text = text;
	strcpy(n->text, str);

	return n;
}

/* use memcpy */
struct node *mk_dup(struct node *a)
{
	return mk_node(a->text);
}

void inner(struct node *n)
{
	if (n->type == NODE_GROUP) {
		n->text = n->inner;
	}
}

char *merror(char *input)
{
	char *error = "";
	asprintf(&error, "<merror>Error on input \"%s\".</merror>", input);
	return error;
}

void cancel(struct node *s0)
{
	inner(s0);
	asprintf(&s0->text, "<menclose notation=\"updiagonalstrike\">%s</menclose>", s0->text);
	s0->type = NODE_SIMPLE;
}

void matrix(struct node *n, char *l, char *r0, char *r)
{
	n->type = NODE_SIMPLE;
	asprintf(&n->text, "<mrow><mo>%s</mo><mtable>%s</mtable><mo>%s</mo></mrow>", l, r0, r);
}

void row(struct node *n, char *r0)
{
	n->type = NODE_SIMPLE;
	asprintf(&n->text, "<mtr>%s</mtr>", r0);
}

void cell(struct node *n, char *s0)
{
	n->type = NODE_SIMPLE;
	asprintf(&n->text, "<mtd>%s</mtd>", s0);
}

void operator(struct node *n, char *s0)
{
	n->type = NODE_OP;
	asprintf(&n->text, "<mo>%s</mo>", s0);
}

struct node *mk_identifier(char *s0)
{
	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	text = malloc(sizeof(char) * strlen(s0) + 1);
	n->type = NODE_ID;
	asprintf(&n->text, "<mi>%s</mi>", s0);

	return n;
}

struct node *mk_greek(char *s0)
{
	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	text = malloc(sizeof(char) * strlen(s0) + 1);
	n->type = NODE_ID;
	asprintf(&n->text, "<mi>&%s;</mi>", s0);

	return n;
}

struct node *mk_op(char *s0)
{
	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	text = malloc(sizeof(char) * strlen(s0) + 1);
	n->type = NODE_ID;
	asprintf(&n->text, "<mo>%s</mo>", s0);

	return n;
}

struct node *mk_number(char *s0)
{
	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	text = malloc(sizeof(char) * strlen(s0) + 1);
	n->type = NODE_ID;
	asprintf(&n->text, "<mn>%s</mn>", s0);

	return n;
}

void msqrt(struct node *s0)
{
	inner(s0);
	asprintf(&s0->text, "<msqrt>%s</msqrt>", s0->text);
	s0->type = NODE_SIMPLE;
}

void mtext(struct node *s0)
{
	asprintf(&s0->text, "<mtext>%s</mtext>", s0->text);
	s0->type = NODE_SIMPLE;
}


void font(struct node *n, char *s0, struct node *t0)
{
	inner(t0);
	n->type = NODE_SIMPLE;
	asprintf(&n->text, "<mstyle mathvariant=\"%s\">%s</mstyle>", s0, t0->text);
}

void accent_under(struct node *s0, char *a0)
{
	inner(s0);
	asprintf(&s0->text, "<munder>%s<mo>%s</mo></munder>", s0->text, a0);
	s0->type = NODE_SIMPLE;
}

void accent(struct node *s0, char *a0)
{
	inner(s0);
	asprintf(&s0->text, "<mover>%s<mo>%s</mo></mover>", s0->text, a0);
	s0->type = NODE_SIMPLE;
}

struct node *mk_group(char *l, char *e, char *r)
{
	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	text = malloc(sizeof(char) * (strlen(l) + strlen(e) + strlen(r)) + 1);
	n->type = NODE_GROUP;
	asprintf(&n->text, "<mrow><mo>%s</mo>%s<mo>%s</mo></mrow>", l, e, r);
	asprintf(&n->inner, "<mrow>%s</mrow>", e);

	return n;
}

struct node *mk_concat(char *s0, char *e0)
{
	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	text = malloc(sizeof(char) * strlen(s0) + 1);
	n->type = NODE_UNKNOWN;
	asprintf(&n->text, "%s%s", s0, e0);

	return n;
}

struct node *mk_fraction(struct node *s0, struct node *s1)
{
	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	n->type = NODE_SIMPLE;
	inner(s0);
	inner(s1);
	asprintf(&n->text, "<mfrac>%s%s</mfrac>", s0->text, s1->text);

	return n;
}

struct node *mk_bin(struct node *s0, struct node *s1, char *operator)
{
	if (!strcmp("frac", operator)) {
		return mk_fraction(s0, s1);
	}
	else if (!strcmp("root", operator)) {
		return mk_root(s0, s1);
	}
	else if (!strcmp("stackrel", operator)) {
		return mk_stackrel(s0, s1);
	}
}

struct node *mk_root(struct node *s0, struct node *s1)
{
	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	n->type = NODE_SIMPLE;
	inner(s0);
	inner(s1);
	asprintf(&n->text, "<mroot>%s%s</mroot>", s0->text, s1->text);

	return n;
}

struct node *mk_color(struct node *s0, struct node *s1)
{
	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	n->type = NODE_SIMPLE;
	inner(s1);
	asprintf(&n->text, "<mstyle mathcolor=\"%s\">%s</mstyle>", s0->text, s1->text);

	return n;
}

struct node *mk_stackrel(struct node *s0, struct node *s1)
{
	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	n->type = NODE_SIMPLE;
	inner(s0);
	inner(s1);
	asprintf(&n->text, "<mover>%s%s</mover>", s0->text, s1->text);

	return n;
}

struct node *mk_sub(struct node *s0, struct node *s1)
{
	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	n->type = NODE_SIMPLE;
	inner(s1);
	asprintf(&n->text, "<msub>%s%s</msub>", s0->text, s1->text);

	return n;
}

struct node *mk_under(struct node *s0, struct node *s1)
{
	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	n->type = NODE_SIMPLE;
	inner(s1);
	asprintf(&n->text, "<munder>%s%s</munder>", s0->text, s1->text);

	return n;
}

struct node *mk_sup(struct node *s0, struct node *s1)
{	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	n->type = NODE_SIMPLE;
	inner(s1);
	asprintf(&n->text, "<msup>%s%s</msup>", s0->text, s1->text);

	return n;
}

struct node *mk_subsup(struct node *s0, struct node *s1, struct node *s2)
{
	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	n->type = NODE_SIMPLE;
	inner(s0);
	inner(s1);
	inner(s2);
	asprintf(&n->text, "<msubsup>%s%s%s</msubsup>", s0->text, s1->text, s2->text);

	return n;
}

struct node *mk_underover(struct node *s0, struct node *s1, struct node *s2)
{
	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	n->type = NODE_SIMPLE;
	inner(s0);
	inner(s1);
	inner(s2);
	asprintf(&n->text, "<munderover>%s%s%s</munderover>", s0->text, s1->text, s2->text);

	return n;
}

struct node *mk_ubrace(struct node *s0, struct node *s1)
{
	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	n->type = NODE_SIMPLE;
	inner(s0);
	inner(s1);
	asprintf(&n->text, "<munder><munder>%s<mo>&#x23DF;</mo></munder>%s</munder>", s0->text, s1->text);

	return n;
}

struct node *mk_obrace(struct node *s0, struct node *s1)
{
	struct node *n;
	char *text;

	n = malloc(sizeof(struct node));
	n->type = NODE_SIMPLE;
	inner(s0);
	inner(s1);
	asprintf(&n->text, "<mover><mover>%s<mo>&#x23DE;</mo></mover>%s</mover>", s0->text, s1->text);

	return n;
}
