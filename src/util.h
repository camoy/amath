#ifndef UTIL_H
#define UTIL_H

/* data types */

enum node_t {
	NODE_RAW,
	NODE_UNDEROVER,
	NODE_OP,
	NODE_TEXT,
	NODE_NUMBER,
	NODE_IDENTIFIER,
	NODE_GROUP,
	NODE_SIMPLE,
	NODE_UNKNOWN
};

struct node {
	enum node_t type;
	char *text;
	char *inner;
};

struct greg_data {
	const char *input;
	struct node *result;
};

/* basic functions */

struct node *mk_empty(enum node_t type);
struct node *mk_node(enum node_t type, char *str);
struct node *mk_str(char *str);
void free_node(struct node *n);
struct node *mk_concat(struct node *s0, struct node *s1);
struct node *mk_group(struct node *l, struct node *e, struct node *r);

/* helper functions */

char *merror(char *input);
void inner(struct node *n);

/* const functions */

struct node *mk_number(char *s0);
struct node *mk_op(char *s0);
struct node *mk_greek(char *s0);
struct node *mk_id(char *s0);
struct node *mk_underover(char *s0);

/* unary functions */

struct node *msqrt(struct node *s0);
struct node *mtext(struct node *s0);
struct node *ul(struct node *s0);
struct node *cancel(struct node *s0);
struct node *accent(struct node *s0, const char *accent);
struct node *font(struct node *s0, const char *font);
struct node *color(struct node *s0, const char *color);

/* binary functions */

struct node *mk_frac(struct node *s0, struct node *s1);
struct node *mk_root(struct node *s0, struct node *s1);
struct node *mk_stackrel(struct node *s0, struct node *s1);
struct node *mk_ubrace(struct node *s0, struct node *s1);
struct node *mk_obrace(struct node *s0, struct node *s1);

/* special binary functions */

struct node *mk_color(struct node *s0, struct node *s1);
struct node *mk_sup(struct node *s0, struct node *s1);
struct node *mk_sub(struct node *s0, struct node *s1);

/* ternary function */

struct node *mk_ter(struct node *s0, struct node *s1, struct node *s2);

/* matrix functions */

struct node *matrix(struct node *l, struct node *s0, struct node *r);
struct node *row(struct node *s0);
struct node *cell(struct node *s0);

#endif