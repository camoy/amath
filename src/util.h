#ifndef UTIL_H
#define UTIL_H

struct greg_data {
	const char *input;
	char *result;
};

char *inner(char *src);
char *merror(char *input); 
void matrix(char **v, char *l, char *r0, char *r);
void row(char **v, char *r0);
void cell(char **v, char *s0);
void msqrt(char **v, char *s0);
void text(char **v, char *s0);
void font(char **v, char *s0, char *t0);
void cancel(char **v, char *s0);
void accent(char **v, char *s0, char *a0);
void accent_under(char **v, char *s0, char *a0);
void group(char **v, char *l, char *e, char *r);
void concat(char **v, char *s0, char *e0);
void operator(char **v, char *s0);
void greek(char **v, char *s0);
void identifier(char **v, char *s0);
void number(char **v, char *s0);
void fraction(char **v, char *s0, char *s1);
void root(char **v, char *s0, char *s1);
void color(char **v, char *s0, char *s1);
void stackrel(char **v, char *s0, char *s1);
void sub(char **v, char *s0, char *s1);
void under(char **v, char *s0, char *s1);
void sup(char **v, char *s0, char *s1);
void underover(char **v, char *s0, char *s1, char *s2);
void subsup(char **v, char *s0, char *s1, char *s2);
void ubrace(char **v, char *s0, char *s1);
void obrace(char **v, char *s0, char *s1);

#endif