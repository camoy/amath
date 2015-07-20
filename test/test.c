#include <stdio.h>
#include <string.h>
#include "minunit.h"
 
char *amath_asciimath_to_mathml(char *text, size_t len);
int tests_run = 0;

static char * test_subscripts() {
	char *expr = "x^2+y_1+z_12^34";
	char *against = "<msup><mi>x</mi><mn>2</mn></msup><mo>+</mo><msub><mi>y</mi><mn>1</mn></msub><mo>+</mo><msubsup><mi>z</mi><mn>12</mn><mn>34</mn></msubsup>";
	mu_assert("FAILED: subscripts", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_function() {
	char *expr = "sin^-1(x)";
	char *against = "<msup><mo>sin</mo><mn>-1</mn></msup><mrow>(<mi>x</mi>)</mrow>";
	mu_assert("FAILED: function", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_deriv() {
	char *expr = "d/dxf(x)=lim_(h->0)(f(x+h)-f(x))/h";
	char *against = "<mfrac><mi>d</mi><mrow><mi>d</mi><mi>x</mi></mrow></mfrac><mrow><mi>f</mi><mrow><mo>(</mo><mi>x</mi><mo>)</mo></mrow></mrow><mo>=</mo><munder><mo>lim</mo><mrow><mi>h</mi><mo>→</mo><mn>0</mn></mrow></munder><mfrac><mrow><mrow><mi>f</mi><mrow><mo>(</mo><mi>x</mi><mo>+</mo><mi>h</mi><mo>)</mo></mrow></mrow><mo>-</mo><mrow><mi>f</mi><mrow><mo>(</mo><mi>x</mi><mo>)</mo></mrow></mrow></mrow><mi>h</mi></mfrac>";
	mu_assert("FAILED: deriv", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_taylor() {
	char *expr = "f(x)=sum_(n=0)^oo(f^((n))(a))/(n!)(x-a)^n";
	char *against = "<mrow><mi>f</mi><mrow><mo>(</mo><mi>x</mi><mo>)</mo></mrow></mrow><mo>=</mo><mrow><munderover><mo>∑</mo><mrow><mi>n</mi><mo>=</mo><mn>0</mn></mrow><mo>∞</mo></munderover></mrow><mfrac><mrow><mrow><msup><mi>f</mi><mrow><mrow><mo>(</mo><mi>n</mi><mo>)</mo></mrow></mrow></msup><mrow><mo>(</mo><mi>a</mi><mo>)</mo></mrow></mrow></mrow><mrow><mi>n</mi><mo>!</mo></mrow></mfrac><msup><mrow><mo>(</mo><mi>x</mi><mo>-</mo><mi>a</mi><mo>)</mo></mrow><mi>n</mi></msup>";
	mu_assert("FAILED: taylor", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_integral() {
	char *expr = "int_0^1f(x)dx";
	char *against = "<mrow><msubsup><mo>∫</mo><mn>0</mn><mn>1</mn></msubsup></mrow><mrow><mi>f</mi><mrow><mo>(</mo><mi>x</mi><mo>)</mo></mrow></mrow><mrow><mi>d</mi><mi>x</mi></mrow>";
	mu_assert("FAILED: integral", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_matrix() {
	char *expr = "[[a,b],[c,d]]((n),(k))";
	char *against = "<mrow><mo>[</mo><mtable><mtr><mtd><mi>a</mi></mtd><mtd><mi>b</mi></mtd></mtr><mtr><mtd><mi>c</mi></mtd><mtd><mi>d</mi></mtd></mtr></mtable><mo>]</mo></mrow><mrow><mo>(</mo><mtable><mtr><mtd><mi>n</mi></mtd></mtr><mtr><mtd><mi>k</mi></mtd></mtr></mtable><mo>)</mo></mrow>";
	mu_assert("FAILED: matrix", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_piecewise() {
	char *expr = "x/x={(1,if x!=0),(\"undefined\",if x=0):}";
	char *against = "<mfrac><mi>x</mi><mi>x</mi></mfrac><mo>=</mo><mrow><mo>{</mo><mtable columnalign=\"left\"><mtr><mtd><mn>1</mn></mtd><mtd><mrow><mspace width=\"1ex\"></mspace><mo>if</mo><mspace width=\"1ex\"></mspace></mrow><mi>x</mi><mo>≠</mo><mn>0</mn></mtd></mtr><mtr><mtd><mrow><mtext>undefined</mtext></mrow></mtd><mtd><mrow><mspace width=\"1ex\"></mspace><mo>if</mo><mspace width=\"1ex\"></mspace></mrow><mi>x</mi><mo>=</mo><mn>0</mn></mtd></mtr></mtable></mrow>";
	mu_assert("FAILED: piecewise", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_frac() {
	char *expr = "a//b";
	char *against = "<mi>a</mi><mo>/</mo><mi>b</mi>";
	mu_assert("FAILED: frac", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_nested_frac() {
	char *expr = "(a/b)/(c/d)";
	char *against = "<mfrac><mrow><mfrac><mi>a</mi><mi>b</mi></mfrac></mrow><mrow><mfrac><mi>c</mi><mi>d</mi></mfrac></mrow></mfrac>";
	mu_assert("FAILED: nested_frac", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_slash_frac() {
	char *expr = "a/b/c/d";
	char *against = "<mfrac><mi>a</mi><mi>b</mi></mfrac><mo>/</mo><mfrac><mi>c</mi><mi>d</mi></mfrac>";
	mu_assert("FAILED: slash_frac", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_nested_brack() {
	char *expr = "((a*b))/c";
	char *against = "<mfrac><mrow><mrow><mo>(</mo><mi>a</mi><mo>⋅</mo><mi>b</mi><mo>)</mo></mrow></mrow><mi>c</mi></mfrac>";
	mu_assert("FAILED: nested_brack", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_nested_root() {
	char *expr = "sqrt sqrt root3x";
	char *against = "<msqrt><msqrt><mroot><mi>x</mi><mn>3</mn></mroot></msqrt></msqrt>";
	mu_assert("FAILED: nested_root", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_vector() {
	char *expr = "<< a,b >> and {:(x,y),(u,v):}";
	char *against = "<mrow><mo>〈</mo><mi>a</mi><mo>,</mo><mi>b</mi><mo>〉</mo></mrow><mrow><mspace width=\"1ex\"></mspace><mtext>and</mtext><mspace width=\"1ex\"></mspace></mrow><mrow><mtable columnalign=\"left\"><mtr><mtd><mi>x</mi></mtd><mtd><mi>y</mi></mtd></mtr><mtr><mtd><mi>u</mi></mtd><mtd><mi>v</mi></mtd></mtr></mtable></mrow>";
	mu_assert("FAILED: vector", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_mismatch_bracket() {
	char *expr = "(a,b]={x in RR | a < x <= b}";
	char *against = "<mrow><mo>(</mo><mi>a</mi><mo>,</mo><mi>b</mi><mo>]</mo></mrow><mo>=</mo><mrow><mo>{</mo><mi>x</mi><mo>∈</mo><mo>ℝ</mo><mrow><mo>∣</mo></mrow><mi>a</mi><mo>&lt;</mo><mi>x</mi><mo>≤</mo><mi>b</mi><mo>}</mo></mrow>";
	mu_assert("FAILED: mismatch_bracket", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_decimal() {
	char *expr = "abc-123.45^-1.1";
	char *against = "<mi>a</mi><mi>b</mi><mi>c</mi><mo>-</mo><msup><mn>123.45</mn><mrow><mo>-</mo><mn>1.1</mn></mrow></msup>";
	mu_assert("FAILED: decimal", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_accent() {
	char *expr = "hat(ab) bar(xy) ulA vec v dotx ddot y";
	char *against = "<mover><mrow><mi>a</mi><mi>b</mi></mrow><mo>^</mo></mover><mover><mrow><mi>x</mi><mi>y</mi></mrow><mo>¯</mo></mover><munder><mi>A</mi><mo>̲</mo></munder><mover><mi>v</mi><mo>→</mo></mover><mover><mi>x</mi><mo>.</mo></mover><mover><mi>y</mi><mo>..</mo></mover>";
	mu_assert("FAILED: accent", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_font() {
	char *expr = "bb{AB3}.bbb(AB].cc(AB).fr{AB}.tt[AB].sf(AB)";
	char *against = "<mrow><mi>A</mi><mi>B</mi><mn>3</mn></mrow><mo>.</mo><mrow>𝔸𝔹</mrow><mo>.</mo><mrow>𝒜ℬ</mrow><mo>.</mo><mrow>𝔄𝔅</mrow><mo>.</mo><mrow><mi>A</mi><mi>B</mi></mrow><mo>.</mo><mrow><mi>A</mi><mi>B</mi></mrow>";
	mu_assert("FAILED: font", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_stack() {
	char *expr = "stackrel\"def\"= or stackrel Delta =\" \"(\"or \":=)";
	char *against = "<mover><mo>=</mo><mrow><mtext>def</mtext></mrow></mover><mrow><mspace width=\"1ex\"></mspace><mtext>or</mtext><mspace width=\"1ex\"></mspace></mrow><mover><mrow><mo>=</mo></mrow><mrow><mo>Δ</mo></mrow></mover><mrow><mspace width=\"1ex\"></mspace><mtext> </mtext><mspace width=\"1ex\"></mspace></mrow><mrow><mo>(</mo><mrow><mtext>or </mtext><mspace width=\"1ex\"></mspace></mrow><mo>:=</mo><mo>)</mo></mrow>";
	mu_assert("FAILED: stack", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_prescript() {
	char *expr = "{::}_(\\ 92)^238U";
	char *against = "<mrow><msubsup><mrow></mrow><mrow><mo>&nbsp;</mo><mn>92</mn></mrow><mn>238</mn></msubsup></mrow><mi>U</mi>";
	mu_assert("FAILED: prescript", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_cancel() {
	char *expr = "(cancel((x+1))(x-2))/(cancel((x+1))(x+3))";
	char *against = "<mfrac><mrow><menclose notation=\"updiagonalstrike\"><mrow><mrow><mo>(</mo><mi>x</mi><mo>+</mo><mn>1</mn><mo>)</mo></mrow></mrow></menclose><mrow><mo>(</mo><mi>x</mi><mo>-</mo><mn>2</mn><mo>)</mo></mrow></mrow><mrow><menclose notation=\"updiagonalstrike\"><mrow><mrow><mo>(</mo><mi>x</mi><mo>+</mo><mn>1</mn><mo>)</mo></mrow></mrow></menclose><mrow><mo>(</mo><mi>x</mi><mo>+</mo><mn>3</mn><mo>)</mo></mrow></mrow></mfrac>";
	mu_assert("FAILED: cancel", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_color() {
	char *expr = "color(red)(x^2)+3x+color(green)(4)";
	char *against = "<mrow><msup><mi>x</mi><mn>2</mn></msup></mrow><mo>+</mo><mn>3</mn><mi>x</mi><mo>+</mo><mrow><mn>4</mn></mrow>";
	mu_assert("FAILED: color", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * test_braces() {
	char *expr = "underbrace(1+2+3+4)_(\"4 terms\") - obrace(2+3)^(n)";
	char *against = "<munder><munder><mrow><mn>1</mn><mo>+</mo><mn>2</mn><mo>+</mo><mn>3</mn><mo>+</mo><mn>4</mn></mrow><mo>⏟</mo></munder><mrow><mrow><mtext>4 terms</mtext></mrow></mrow></munder><mo>-</mo><mover><mover><mrow><mn>2</mn><mo>+</mo><mn>3</mn></mrow><mo>⏞</mo></mover><mrow><mi>n</mi></mrow></mover>";
	mu_assert("FAILED: braces", strcmp(against, amath_asciimath_to_mathml(expr, strlen(expr))) == 0);
	return 0;
}

static char * all_tests() {
    mu_run_test(test_subscripts);
    mu_run_test(test_function);
    mu_run_test(test_deriv);
    mu_run_test(test_taylor);
    mu_run_test(test_integral);
    mu_run_test(test_matrix);
    mu_run_test(test_piecewise);
    mu_run_test(test_frac);
    mu_run_test(test_nested_frac);
    mu_run_test(test_slash_frac);
    mu_run_test(test_nested_brack);
    mu_run_test(test_nested_root);
    mu_run_test(test_vector);
    mu_run_test(test_mismatch_bracket);
    mu_run_test(test_decimal);
    mu_run_test(test_accent);
    mu_run_test(test_font);
    mu_run_test(test_stack);
    mu_run_test(test_prescript);
    mu_run_test(test_cancel);
    mu_run_test(test_color);
    mu_run_test(test_braces);
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
