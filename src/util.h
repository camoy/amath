#ifndef UTIL_H
#define UTIL_H

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

struct node *mk_empty(enum node_t type);
void free_node(struct node *n);
struct node *mk_bin(struct node *s0, struct node *s1, char *operator);
struct node *mk_node(enum node_t type, char *str);
void inner(struct node *n);
char *merror(char *input);
void cancel(struct node *s0);
void matrix(struct node *l, struct node *n, struct node *r);
void row(struct node *n);
void cell(struct node *n);
void operator(struct node *n, char *s0);
struct node *mk_identifier(char *s0);
struct node *mk_greek(char *s0);
struct node *mk_op(char *s0);
struct node *mk_underover(char *s0);
struct node *mk_number(char *s0);
void msqrt(struct node *s0);
void mtext(struct node *s0);
void font(char *s0, struct node *t0);
void ul(struct node *s0);
void accent(struct node *s0, struct node *a0);
struct node *mk_group(struct node *l, struct node *e, struct node *r);
struct node *mk_concat(struct node *s0, struct node *s1);
struct node *mk_fraction(struct node *s0, struct node *s1);
struct node *mk_root(struct node *s0, struct node *s1);
struct node *mk_color(struct node *s0, struct node *s1);
struct node *mk_stackrel(struct node *s0, struct node *s1);
struct node *mk_sub(struct node *s0, struct node *s1);
struct node *mk_under(struct node *s0, struct node *s1);
struct node *mk_sup(struct node *s0, struct node *s1);
struct node *mk_subsup(struct node *s0, struct node *s1, struct node *s2);
struct node *mk_ter(struct node *s0, struct node *s1, struct node *s2);
struct node *mk_ubrace(struct node *s0, struct node *s1);
struct node *mk_obrace(struct node *s0, struct node *s1);

#endif