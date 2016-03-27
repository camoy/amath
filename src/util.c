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
	char *text = malloc(sizeof(char) * strlen(str) + 1);
	n->text = text;
	strcpy(n->text, str);
	return n;
}

struct node *mk_concat(struct node *s0, struct node *s1)
{
	struct node *n = mk_empty(NODE_SIMPLE);
	asprintf(&n->text, "%s%s", s0->text, s1->text);
	return n;
}

struct node *mk_group(char *l, char *e, char *r)
{
	struct node *n = mk_empty(NODE_GROUP);
	asprintf(&n->text, "<mrow><mo>%s</mo>%s<mo>%s</mo></mrow>", l, e, r);
	asprintf(&n->inner, "<mrow>%s</mrow>", e);
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

/* unary functions */

#define UNARY_FN(name, n_type, str) \
	void name(struct node *s0) \
	{ \
		inner(s0); \
		asprintf(&s0->text, str, s0->text); \
		s0->type = n_type; \
	} \

UNARY_FN(msqrt, NODE_SIMPLE, "<msqrt>%s</msqrt>")
UNARY_FN(mtext, NODE_SIMPLE, "<mtext>%s</mtext>")
UNARY_FN(ul, NODE_SIMPLE, "<munder>%s<mo>_</mo></munder>")
UNARY_FN(cancel, NODE_SIMPLE, "<menclose notation=\"updiagonalstrike\">%s</menclose>")

void accent(struct node *s0, char *a0)
{
	inner(s0);
	s0->type = NODE_SIMPLE;
	asprintf(&s0->text, "<mover>%s<mo>%s</mo></mover>", s0->text, a0);
}

void font(struct node *n, char *s0, struct node *t0)
{
	inner(t0);
	n->type = NODE_SIMPLE;
	asprintf(&n->text, "<mstyle mathvariant=\"%s\">%s</mstyle>", s0, t0->text);
}

/* binary functions */

#define MK_BIN_FN(name, n_type, str) \
	struct node *mk_##name(struct node *s0, struct node *s1) \
	{ \
		struct node *n = mk_empty(n_type); \
		inner(s0); \
		inner(s1); \
		asprintf(&n->text, str, s0->text, s1->text); \
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
		return n; \
	} \

MK_BIN_SP_FN(color, NODE_SIMPLE, "<mstyle mathcolor=\"%s\">%s</mstyle>")
MK_BIN_SP_FN(sub, NODE_SIMPLE, "<msub>%s%s</msub>")
MK_BIN_SP_FN(under, NODE_SIMPLE, "<munder>%s%s</munder>")
MK_BIN_SP_FN(sup, NODE_SIMPLE, "<msup>%s%s</msup>")

/* ternary functions */

#define MK_TER_FN(name, n_type, str) \
	struct node *mk_##name(struct node *s0, struct node *s1, struct node *s2) \
	{ \
		struct node *n = mk_empty(n_type); \
		inner(s0); \
		inner(s1); \
		inner(s2); \
		asprintf(&n->text, str, s0->text, s1->text, s2->text); \
		return n; \
	} \

MK_TER_FN(subsup, NODE_SIMPLE, "<msubsup>%s%s%s</msubsup>")
MK_TER_FN(underover, NODE_SIMPLE, "<munderover>%s%s%s</munderover>")

/* matrix functions */
void matrix(struct node *n, char *l, char *r0, char *r)
{
	n->type = NODE_SIMPLE;
	asprintf(&n->text, "<mrow><mo>%s</mo><mtable>%s</mtable><mo>%s</mo></mrow>", l, r0, r);
}

void row(struct node *n, char *r0)
{
	asprintf(&n->text, "<mtr>%s</mtr>", r0);
}

void cell(struct node *n, char *s0)
{
	asprintf(&n->text, "<mtd>%s</mtd>", s0);
}
