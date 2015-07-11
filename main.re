#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

void* ParseAlloc(void* (*allocProc)(size_t));
void Parse(void*, int, const char*);
void ParseFree(void*, void(*freeProc)(void*));

int scan(char *s, int l)
{
	void *parser = ParseAlloc(malloc);
        char *p = s;
        char *q = 0;

#define YYCTYPE         char
#define YYCURSOR        p
#define YYLIMIT         (s+l)
#define YYMARKER        q
#define YYFILL(n)
#define TOKEN 		strndup(t, YYCURSOR - t)
#define PARSE(a, b)	Parse(parser, a, b); continue;

        for(;;)
        {
		char *t = YYCURSOR;
/*!re2c
        re2c:indent:top = 2;

        [0-9]+'.'?[0-9]*{ PARSE(NUMBER, TOKEN) }
	[ \t]+		{ continue; }

	"alpha"		{ PARSE(IDENTIFIER, "\u03B1") }
	"beta"		{ PARSE(IDENTIFIER, "\u03B2") }
	"chi"		{ PARSE(IDENTIFIER, "\u03C7") }
	"delta"		{ PARSE(IDENTIFIER, "\u03B4") }
	"Delta"		{ PARSE(IDENTIFIER, "\u0394") }
	"epsi"		{ PARSE(IDENTIFIER, "\u03B5") }
	"varepsilon"	{ PARSE(IDENTIFIER, "\u025B") }
	"eta"		{ PARSE(IDENTIFIER, "\u03B7") }
	"gamma"		{ PARSE(IDENTIFIER, "\u03B3") }
	"Gamma"		{ PARSE(IDENTIFIER, "\u0393") }
	"iota"		{ PARSE(IDENTIFIER, "\u03B9") }
	"kappa"		{ PARSE(IDENTIFIER, "\u03BA") }
	"lambda"	{ PARSE(IDENTIFIER, "\u03BB") }
	"Lambda"	{ PARSE(IDENTIFIER, "\u039B") }
	"lamda"		{ PARSE(IDENTIFIER, "\u03BB") }
	"Lamda"		{ PARSE(IDENTIFIER, "\u039B") }
	"mu"		{ PARSE(IDENTIFIER, "\u03BC") }
	"nu"		{ PARSE(IDENTIFIER, "\u03BD") }
	"omega"		{ PARSE(IDENTIFIER, "\u03C9") }
	"Omega"		{ PARSE(IDENTIFIER, "\u03A9") }
	"phi"		{ PARSE(IDENTIFIER, "\u03D5") }
	"varphi"	{ PARSE(IDENTIFIER, "\u03C6") }
	"Phi"		{ PARSE(IDENTIFIER, "\u03A6") }
	"pi"		{ PARSE(IDENTIFIER, "\u03C0") }
	"Pi"		{ PARSE(IDENTIFIER, "\u03A0") }
	"psi"		{ PARSE(IDENTIFIER, "\u03C8") }
	"Psi"		{ PARSE(IDENTIFIER, "\u03A8") }
	"rho"		{ PARSE(IDENTIFIER, "\u03C1") }
	"sigma"		{ PARSE(IDENTIFIER, "\u03C3") }
	"Sigma"		{ PARSE(IDENTIFIER, "\u03A3") }
	"tau"		{ PARSE(IDENTIFIER, "\u03C4") }
	"theta"		{ PARSE(IDENTIFIER, "\u03B8") }
	"varthetaut"	{ PARSE(IDENTIFIER, "\u03D1") }
	"Theta"		{ PARSE(IDENTIFIER, "\u0398") }
	"upsilon"	{ PARSE(IDENTIFIER, "\u03C5") }
	"xi"		{ PARSE(IDENTIFIER, "\u03BE") }
	"Xi"		{ PARSE(IDENTIFIER, "\u039E") }
	"zeta"		{ PARSE(IDENTIFIER, "\u03B6") }

	"+"		{ PARSE(OPERATOR, "+") }
	"-"		{ PARSE(OPERATOR, "-") }
	"*"		{ PARSE(OPERATOR, "\u22C5") }
	"**"		{ PARSE(OPERATOR, "\u2217") }
	"***"		{ PARSE(OPERATOR, "\u22C6") }
	"//"		{ PARSE(OPERATOR, "/") }
	"\\\\"		{ PARSE(OPERATOR, "\\") }
	"setminus"	{ PARSE(OPERATOR, "\\") }
	"xx"		{ PARSE(OPERATOR, "\u00D7") }
	"-:"		{ PARSE(OPERATOR, "\u00F7") }
	"divide"	{ PARSE(OPERATOR, "-:") }
	"@"		{ PARSE(OPERATOR, "\u2218") }
	"o+"		{ PARSE(OPERATOR, "\u2295") }
	"ox"		{ PARSE(OPERATOR, "\u2297") }
	"o."		{ PARSE(OPERATOR, "\u2299") }
	"sum"		{ PARSE(OPERATOR_UNDER_OVER, "\u2211") }
	"prod"		{ PARSE(OPERATOR_UNDER_OVER, "\u220F") }
	"^^"		{ PARSE(OPERATOR, "\u2227") }
	"^^^"		{ PARSE(OPERATOR_UNDER_OVER, "\u22C0") }
	"vv"		{ PARSE(OPERATOR, "\u2228") }
	"vvv"		{ PARSE(OPERATOR_UNDER_OVER, "\u22C1") }
	"nn"		{ PARSE(OPERATOR, "\u2229") }
	"nnn"		{ PARSE(OPERATOR_UNDER_OVER, "\u22C2") }
	"uu"		{ PARSE(OPERATOR, "\u222A") }
	"uuu"		{ PARSE(OPERATOR_UNDER_OVER, "\u22C3") }

	"="		{ PARSE(OPERATOR, "=") }
	"!="		{ PARSE(OPERATOR, "\u2260") }
	":="		{ PARSE(OPERATOR, ":=") }
	"lt"		{ PARSE(OPERATOR, "<") }
	"<="		{ PARSE(OPERATOR, "\u2264") }
	"lt="		{ PARSE(OPERATOR, "\u2264") }
	"gt"		{ PARSE(OPERATOR, ">") }
	">="		{ PARSE(OPERATOR, "\u2265") }
	"gt="		{ PARSE(OPERATOR, "\u2265") }
	"-<"		{ PARSE(OPERATOR, "\u227A") }
	"-lt"		{ PARSE(OPERATOR, "\u227A") }
	">-"		{ PARSE(OPERATOR, "\u227B") }
	"-<="		{ PARSE(OPERATOR, "\u2AAF") }
	">-="		{ PARSE(OPERATOR, "\u2AB0") }
	"in"		{ PARSE(OPERATOR, "\u2208") }
	"!in"		{ PARSE(OPERATOR, "\u2209") }
	"sub"		{ PARSE(OPERATOR, "\u2282") }
	"sup"		{ PARSE(OPERATOR, "\u2283") }
	"sube"		{ PARSE(OPERATOR, "\u2286") }
	"supe"		{ PARSE(OPERATOR, "\u2287") }
	"-="		{ PARSE(OPERATOR, "\u2261") }
	"~="		{ PARSE(OPERATOR, "\u2245") }
	"~~"		{ PARSE(OPERATOR, "\u2248") }
	"prop"		{ PARSE(OPERATOR, "\u221D") }

	"and"		{ PARSE(OPERATOR, "and") }
	"or"		{ PARSE(OPERATOR, "or") }
	"not"		{ PARSE(OPERATOR, "\u00AC") }
	"=>"		{ PARSE(OPERATOR, "\u21D2") }
	"if"		{ PARSE(OPERATOR, "if") }
	"<=>"		{ PARSE(OPERATOR, "\u21D4") }
	"AA"		{ PARSE(OPERATOR, "\u2200") }
	"EE"		{ PARSE(OPERATOR, "\u2203") }
	"_|_"		{ PARSE(OPERATOR, "\u22A5") }
	"TT"		{ PARSE(OPERATOR, "\u22A4") }
	"|--"		{ PARSE(OPERATOR, "\u22A2") }
	"|=="		{ PARSE(OPERATOR, "\u22A8") }

	"int"		{ PARSE(OPERATOR, "\u222B") }
	"oint"		{ PARSE(OPERATOR, "\u222E") }
	"del"		{ PARSE(OPERATOR, "\u2202") }
	"grad"		{ PARSE(OPERATOR, "\u2207") }
	"+-"		{ PARSE(OPERATOR, "\u00B1") }
	"..."		{ PARSE(OPERATOR, "...") }
	":."		{ PARSE(OPERATOR, "\u2234") }
	"/_"		{ PARSE(OPERATOR, "\u2220") }
	"/_\\"		{ PARSE(OPERATOR, "\u25B3") }
	"'"		{ PARSE(OPERATOR, "\u2032") }
	"tilde"		{ PARSE(OPERATOR, "~") }
	"\\ "		{ PARSE(OPERATOR, "\u00A0") }
	"quad"		{ PARSE(OPERATOR, "\u00A0\u00A0") }
	"qquad"		{ PARSE(OPERATOR, "\u00A0\u00A0\u00A0\u00A0") }
	"cdots"		{ PARSE(OPERATOR, "\u22EF") }
	"vdots"		{ PARSE(OPERATOR, "\u22EE") }
	"ddots"		{ PARSE(OPERATOR, "\u22F1") }
	"diamond"	{ PARSE(OPERATOR, "\u22C4") }
	"square"	{ PARSE(OPERATOR, "\u25A1") }
	"|__"		{ PARSE(OPERATOR, "\u230A") }
	"__|"		{ PARSE(OPERATOR, "\u230B") }
	"|~"		{ PARSE(OPERATOR, "\u2308") }
	"~|"		{ PARSE(OPERATOR, "\u2309") }
	"O/"		{ PARSE(IDENTIFIER, "\u2205") }
	"oo"		{ PARSE(IDENTIFIER, "\u221E") }
	"aleph"		{ PARSE(IDENTIFIER, "\u2135") }
	"CC"		{ PARSE(IDENTIFIER, "\u2102") }
	"NN"		{ PARSE(IDENTIFIER, "\u2115") }
	"QQ"		{ PARSE(IDENTIFIER, "\u211A") }
	"RR"		{ PARSE(IDENTIFIER, "\u211D") }
	"ZZ"		{ PARSE(IDENTIFIER, "\u2124") }

	"sin"		{ PARSE(IDENTIFIER, "sin") }
	"cos"		{ PARSE(IDENTIFIER, "cos") }
	"tan"		{ PARSE(IDENTIFIER, "tan") }
	"csc"		{ PARSE(IDENTIFIER, "csc") }
	"sec"		{ PARSE(IDENTIFIER, "sec") }
	"cot"		{ PARSE(IDENTIFIER, "cot") }
	"sinh"		{ PARSE(IDENTIFIER, "sinh") }
	"cosh"		{ PARSE(IDENTIFIER, "cosh") }
	"tanh"		{ PARSE(IDENTIFIER, "tanh") }
	"log"		{ PARSE(IDENTIFIER, "log") }
	"ln"		{ PARSE(IDENTIFIER, "ln") }
	"det"		{ PARSE(IDENTIFIER, "det") }
	"dim"		{ PARSE(IDENTIFIER, "dim") }
	"lim"		{ PARSE(IDENTIFIER, "lim") }
	"mod"		{ PARSE(IDENTIFIER, "mod") }
	"gcd"		{ PARSE(IDENTIFIER, "gcd") }
	"lcm"		{ PARSE(IDENTIFIER, "lcm") }
	"min"		{ PARSE(IDENTIFIER, "min") }
	"max"		{ PARSE(IDENTIFIER, "max") }

	"uarr"		{ PARSE(OPERATOR, "\u2191") }
	"darr"		{ PARSE(OPERATOR, "\u2193") }
	"rarr"		{ PARSE(OPERATOR, "\u2192") }
	"->"		{ PARSE(OPERATOR, "\u2192") }
	">->"		{ PARSE(OPERATOR, "\u21A3") }
	"->>"		{ PARSE(OPERATOR, "\u21A0") }
	">->>"		{ PARSE(OPERATOR, "\u2916") }
	"|->"		{ PARSE(OPERATOR, "\u21A6") }
	"larr"		{ PARSE(OPERATOR, "\u2190") }
	"harr"		{ PARSE(OPERATOR, "\u2194") }
	"rArr"		{ PARSE(OPERATOR, "\u21D2") }
	"lArr"		{ PARSE(OPERATOR, "\u21D0") }
	"hArr"		{ PARSE(OPERATOR, "\u21D4") }

	"hat"		{ PARSE(ACCENT_OVER, "^") }
	"bar"		{ PARSE(ACCENT_OVER, "\u00AF") }
	"ul"		{ PARSE(ACCENT_UNDER, "\u0332") }
	"vec"		{ PARSE(ACCENT_OVER, "\u2192") }
	"dot"		{ PARSE(ACCENT_OVER, ".") }
	"ddot"		{ PARSE(ACCENT_OVER, "..") }

	"sqrt"		{ PARSE(UNARY, "sqrt") }
	"text"		{ PARSE(UNARY, "text") }

	"frac"		{ PARSE(BINARY, "frac") }
	"root"		{ PARSE(BINARY, "root") }
	"stackrel"	{ PARSE(BINARY, "over") }

	"/"		{ PARSE(DIV, 0) }
	"_"		{ PARSE(SUB, 0) }
	"^"		{ PARSE(SUP, 0) }

	"(" | "[" | "{"	{ PARSE(LEFT, TOKEN) }
	")" | "]" | "}"	{ PARSE(RIGHT, TOKEN) }

        [A-Za-z]+	{ PARSE(IDENTIFIER, TOKEN) }
        "\000"          { Parse(parser, 0, 0); ParseFree(parser, free); printf("\n"); return 0; }
        [^]             { Parse(parser, 0, 0); ParseFree(parser, free); return 1; }
*/
        }
}

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		return scan(argv[1], strlen(argv[1]));
	}
	else
	{
		fprintf(stderr, "%s <expr>\n", argv[0]);
		return 1;
	}
}
