#ifndef UTIL_H
#define UTIL_H

enum node_t {
	NODE_RAW,
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

struct node *mk_bin(struct node *s0, struct node *s1, char *operator);
struct node *mk_node(enum node_t type, char *str);
void inner(struct node *n);
char *merror(char *input);
void cancel(struct node *s0);
void matrix(struct node *n, char *l, char *r0, char *r);
void row(struct node *n, char *r0);
void cell(struct node *n, char *s0);
void operator(struct node *n, char *s0);
struct node *mk_identifier(char *s0);
struct node *mk_greek(char *s0);
struct node *mk_op(char *s0);
struct node *mk_number(char *s0);
void msqrt(struct node *s0);
void mtext(struct node *s0);
void font(struct node *n, char *s0, struct node *t0);
void ul(struct node *s0);
void accent(struct node *s0, char *a0);
struct node *mk_group(char *l, char *e, char *r);
struct node *mk_concat(struct node *s0, struct node *s1);
struct node *mk_fraction(struct node *s0, struct node *s1);
struct node *mk_root(struct node *s0, struct node *s1);
struct node *mk_color(struct node *s0, struct node *s1);
struct node *mk_stackrel(struct node *s0, struct node *s1);
struct node *mk_sub(struct node *s0, struct node *s1);
struct node *mk_under(struct node *s0, struct node *s1);
struct node *mk_sup(struct node *s0, struct node *s1);
struct node *mk_subsup(struct node *s0, struct node *s1, struct node *s2);
struct node *mk_underover(struct node *s0, struct node *s1, struct node *s2);
struct node *mk_ubrace(struct node *s0, struct node *s1);
struct node *mk_obrace(struct node *s0, struct node *s1);

#endif