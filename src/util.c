#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

/* basic functions */

struct node *mk_empty(enum node_t type)
{
	struct node *n = malloc(sizeof(struct node));
	n->type = type;
	return n;
}

struct node *mk_node(enum node_t type, char *str)
{
	struct node *n = mk_empty(type);
	n->text = strdup(str);
	return n;
}

void free_node(struct node *n)
{
	if (n->type == NODE_GROUP && n->inner != n->text) {
		free(n->inner);
	}
	free(n->text);
	free(n);
}

struct node *mk_concat(struct node *s0, struct node *s1)
{
	struct node *n = mk_empty(NODE_SIMPLE);
	asprintf(&n->text, "%s%s", s0->text, s1->text);
	free_node(s0);
	free_node(s1);
	return n;
}

struct node *mk_group(struct node *l, struct node *e, struct node *r)
{
	struct node *n = mk_empty(NODE_GROUP);
	asprintf(&n->text, "<mrow><mo>%s</mo>%s<mo>%s</mo></mrow>", l->text, e->text, r->text);
	asprintf(&n->inner, "<mrow>%s</mrow>", e->text);
	free_node(l);
	free_node(e);
	free_node(r);
	return n;
}


/* helper functions */

char *merror(char *input)
{
	char *error;
	asprintf(&error, "<merror>Error on input \"%s\".</merror>", input);
	return error;
}

void inner(struct node *n)
{
	if (n->type == NODE_GROUP) {
		if (n->text != n->inner) {
			free(n->text);
		}
		n->text = n->inner;
	}
}

/* const functions */

#define MK_FN(name, n_type, str) \
	struct node *mk_##name(char *s0) \
	{ \
		struct node *n = mk_empty(n_type); \
		asprintf(&n->text, str, s0); \
		return n; \
	} \

MK_FN(number, NODE_IDENTIFIER, "<mn>%s</mn>")
MK_FN(op, NODE_IDENTIFIER, "<mo>%s</mo>")
MK_FN(greek, NODE_IDENTIFIER, "<mi>&%s;</mi>")
MK_FN(identifier, NODE_IDENTIFIER, "<mi>%s</mi>")
MK_FN(underover, NODE_UNDEROVER, "<mo>%s</mo>")

/* unary functions */

#define UNARY_FN(name, n_type, str) \
	struct node *name(struct node *s0) \
	{ \
		struct node *n = mk_empty(n_type); \
		inner(s0); \
		asprintf(&n->text, str, s0->text); \
		free_node(s0); \
		return n; \
	} \

UNARY_FN(msqrt, NODE_SIMPLE, "<msqrt>%s</msqrt>")
UNARY_FN(mtext, NODE_SIMPLE, "<mtext>%s</mtext>")
UNARY_FN(ul, NODE_SIMPLE, "<munder>%s<mo>_</mo></munder>")
UNARY_FN(cancel, NODE_SIMPLE, "<menclose notation=\"updiagonalstrike\">%s</menclose>")

struct node *accent(struct node *s0, const char *accent)
{
	struct node *n = mk_empty(NODE_SIMPLE);
	inner(s0);
	asprintf(&n->text, "<mover>%s<mo>%s</mo></mover>", s0->text, accent);
	free_node(s0);
	return n;
}

struct node *font(struct node *s0, const char *font)
{
	struct node *n = mk_empty(NODE_SIMPLE);
	inner(s0);
	asprintf(&n->text, "<mstyle mathvariant=\"%s\">%s</mstyle>", font, s0->text);
	free_node(s0);
	return n;
}

/* binary functions */

#define MK_BIN_FN(name, n_type, str) \
	struct node *mk_##name(struct node *s0, struct node *s1) \
	{ \
		struct node *n = mk_empty(n_type); \
		inner(s0); \
		inner(s1); \
		asprintf(&n->text, str, s0->text, s1->text); \
		free_node(s0); \
		free_node(s1); \
		return n; \
	} \

MK_BIN_FN(fraction, NODE_SIMPLE, "<mfrac>%s%s</mfrac>")
MK_BIN_FN(root, NODE_SIMPLE, "<mroot>%s%s</mroot>")
MK_BIN_FN(stackrel, NODE_SIMPLE, "<mover>%s%s</mover>")
MK_BIN_FN(ubrace, NODE_SIMPLE, "<munder><munder>%s<mo>&#x23DF;</mo></munder>%s</munder>")
MK_BIN_FN(obrace, NODE_SIMPLE, "<mover><mover>%s<mo>&#x23DE;</mo></mover>%s</mover>")

/* special binary functions */

#define MK_BIN_SP_FN(name, n_type, str) \
	struct node *mk_##name(struct node *s0, struct node *s1) \
	{ \
		struct node *n = mk_empty(n_type); \
		inner(s1); \
		asprintf(&n->text, str, s0->text, s1->text); \
		free_node(s0); \
		free_node(s1); \
		return n; \
	} \

MK_BIN_SP_FN(color, NODE_SIMPLE, "<mstyle mathcolor=\"%s\">%s</mstyle>")
MK_BIN_SP_FN(sup, NODE_SIMPLE, "<msup>%s%s</msup>")

struct node *mk_sub(struct node *s0, struct node *s1)
{
	struct node *n = mk_empty(NODE_SIMPLE);
	inner(s1);
	if (s0->type == NODE_UNDEROVER) {
		asprintf(&n->text, "<munder>%s%s</munder>", s0->text, s1->text);
	}
	else {
		asprintf(&n->text, "<msub>%s%s</msub>", s0->text, s1->text);
	}
	free_node(s0);
	free_node(s1);
	return n;
}

/* ternary function */

struct node *mk_ter(struct node *s0, struct node *s1, struct node *s2)
{
	struct node *n = mk_empty(NODE_SIMPLE);
	inner(s0);
	inner(s1);
	inner(s2);
	if (s0->type == NODE_UNDEROVER) {
		asprintf(&n->text, "<munderover>%s%s%s</munderover>", s0->text, s1->text, s2->text);
	}
	else {
		asprintf(&n->text, "<msubsup>%s%s%s</msubsup>", s0->text, s1->text, s2->text);
	}
	free_node(s0);
	free_node(s1);
	free_node(s2);
	return n;
}

/* matrix functions */

void matrix(struct node *l, struct node *n, struct node *r)
{
	char *str_o = n->text;
	asprintf(&n->text, "<mrow><mo>%s</mo><mtable>%s</mtable><mo>%s</mo></mrow>", l->text, n->text, r->text);
	free_node(l);
	free_node(r);
	free(str_o);
}

void row(struct node *n)
{
	char *str_o = n->text;
	asprintf(&n->text, "<mtr>%s</mtr>", n->text);
	free(str_o);
}

void cell(struct node *n)
{
	char *str_o = n->text;
	asprintf(&n->text, "<mtd>%s</mtd>", n->text);
	free(str_o);
}
