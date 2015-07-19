#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "syms.h"

#define YYCTYPE         char
#define YYCURSOR        cursor
#define YYMARKER	marker
#define YYLIMIT         (cursor+len)
#define YYFILL(n)
#define SYM(t)		*cursor_ptr = cursor;\
			return &amath_syms[t];
#define NEW_SYM(t)	*cursor_ptr = cursor;\
			struct amath_node *a = malloc(sizeof(struct amath_node));\
			a->type=t;\
			a->str=strndup(old, YYCURSOR - old);\
			a->extra=AMATH_none;\
			return a;

struct amath_node *scan(char **cursor_ptr, size_t len)
{
	char *marker = 0;
	char *cursor = *cursor_ptr;
	char *old = cursor;

/*!re2c
        re2c:indent:top = 2;

	"alpha"		{ SYM(AMATH_alpha) }
	"beta"		{ SYM(AMATH_beta) }
	"chi"		{ SYM(AMATH_chi) }
	"delta"		{ SYM(AMATH_delta) }
	"Delta"		{ SYM(AMATH_Delta) }
	"epsi"		{ SYM(AMATH_epsi) }
	"varepsilon"	{ SYM(AMATH_varepsilon) }
	"eta"		{ SYM(AMATH_eta) }
	"gamma"		{ SYM(AMATH_gamma) }
	"Gamma"		{ SYM(AMATH_Gamma) }
	"iota"		{ SYM(AMATH_iota) }
	"kappa"		{ SYM(AMATH_kappa) }
	"lambda"	{ SYM(AMATH_lambda) }
	"Lambda"	{ SYM(AMATH_Lambda) }
	"lamda"		{ SYM(AMATH_lamda) }
	"Lamda"		{ SYM(AMATH_Lamda) }
	"mu"		{ SYM(AMATH_mu) }
	"nu"		{ SYM(AMATH_nu) }
	"omega"		{ SYM(AMATH_omega) }
	"Omega"		{ SYM(AMATH_Omega) }
	"phi"		{ SYM(AMATH_phi) }
	"varphi"	{ SYM(AMATH_varphi) }
	"Phi"		{ SYM(AMATH_Phi) }
	"pi"		{ SYM(AMATH_pi) }
	"Pi"		{ SYM(AMATH_Pi) }
	"psi"		{ SYM(AMATH_psi) }
	"Psi"		{ SYM(AMATH_Psi) }
	"rho"		{ SYM(AMATH_rho) }
	"sigma"		{ SYM(AMATH_sigma) }
	"Sigma"		{ SYM(AMATH_Sigma) }
	"tau"		{ SYM(AMATH_tau) }
	"theta"		{ SYM(AMATH_theta) }
	"varthetaut"	{ SYM(AMATH_varthetaut) }
	"Theta"		{ SYM(AMATH_Theta) }
	"upsilon"	{ SYM(AMATH_upsilon) }
	"xi"		{ SYM(AMATH_xi) }
	"Xi"		{ SYM(AMATH_Xi) }
	"zeta"		{ SYM(AMATH_zeta) }
	"+"		{ SYM(AMATH_plus) }
	"-"		{ SYM(AMATH_minus) }
	"*"		{ SYM(AMATH_cdot) }
	"**"		{ SYM(AMATH_ast) }
	"***"		{ SYM(AMATH_star) }
	"//"		{ SYM(AMATH_slash) }
	"\\\\"		{ SYM(AMATH_backslash) }
	"setminus"	{ SYM(AMATH_setminus) }
	"xx"		{ SYM(AMATH_times) }
	"-:"		{ SYM(AMATH_div) }
	"divide"	{ SYM(AMATH_divide) }
	"@"		{ SYM(AMATH_circ) }
	"o+"		{ SYM(AMATH_oplus) }
	"ox"		{ SYM(AMATH_otimes) }
	"o."		{ SYM(AMATH_odot) }
	"sum"		{ SYM(AMATH_sum) }
	"prod"		{ SYM(AMATH_prod) }
	"^^"		{ SYM(AMATH_wedge) }
	"^^^"		{ SYM(AMATH_bigwedge) }
	"vv"		{ SYM(AMATH_vee) }
	"vvv"		{ SYM(AMATH_bigvee) }
	"nn"		{ SYM(AMATH_cap) }
	"nnn"		{ SYM(AMATH_bigcap) }
	"uu"		{ SYM(AMATH_cup) }
	"uuu"		{ SYM(AMATH_bigcup) }
	"="		{ SYM(AMATH_eq) }
	"!="		{ SYM(AMATH_ne) }
	":="		{ SYM(AMATH_def) }
	"lt"		{ SYM(AMATH_lt) }
	"<="		{ SYM(AMATH_le) }
	"lt="		{ SYM(AMATH_leq) }
	"gt"		{ SYM(AMATH_gt) }
	">="		{ SYM(AMATH_ge) }
	"gt="		{ SYM(AMATH_geq) }
	"-<"		{ SYM(AMATH_prec) }
	"-lt"		{ SYM(AMATH_lt2) }
	">-"		{ SYM(AMATH_succ) }
	"-<="		{ SYM(AMATH_preceq) }
	">-="		{ SYM(AMATH_succeq) }
	"in"		{ SYM(AMATH_in) }
	"!in"		{ SYM(AMATH_notin) }
	"sub"		{ SYM(AMATH_subset) }
	"sup"		{ SYM(AMATH_supset) }
	"sube"		{ SYM(AMATH_subseteq) }
	"supe"		{ SYM(AMATH_supseteq) }
	"-="		{ SYM(AMATH_equiv) }
	"~="		{ SYM(AMATH_cong) }
	"~~"		{ SYM(AMATH_approx) }
	"prop"		{ SYM(AMATH_propto) }
	"and"		{ SYM(AMATH_and) }
	"or"		{ SYM(AMATH_or) }
	"not"		{ SYM(AMATH_neg) }
	"=>"		{ SYM(AMATH_implies) }
	"if"		{ SYM(AMATH_if) }
	"<=>"		{ SYM(AMATH_iff) }
	"AA"		{ SYM(AMATH_forall) }
	"EE"		{ SYM(AMATH_exists) }
	"_|_"		{ SYM(AMATH_bot) }
	"TT"		{ SYM(AMATH_top) }
	"|--"		{ SYM(AMATH_vdash) }
	"|=="		{ SYM(AMATH_models) }
	"(" 		{ SYM(AMATH_lparen) }
	")" 		{ SYM(AMATH_rparen) }
	"[" 		{ SYM(AMATH_lbracket) }
	"]" 		{ SYM(AMATH_rbracket) }
	"{" 		{ SYM(AMATH_lcurly) }
	"}" 		{ SYM(AMATH_rcurly) }
	"|" 		{ SYM(AMATH_pipe) }
	"||"		{ SYM(AMATH_doublepipe) }
	"(:" 		{ SYM(AMATH_lparencolon) }
	":)" 		{ SYM(AMATH_rparencolon) }
	"<<" 		{ SYM(AMATH_langle) }
	">>" 		{ SYM(AMATH_rangle) }
	"{:" 		{ SYM(AMATH_linvis) }
	":}" 		{ SYM(AMATH_rinvis) }
	"int"		{ SYM(AMATH_int) }
	"dx"		{ SYM(AMATH_dx) }
	"dy"		{ SYM(AMATH_dy) }
	"dz"		{ SYM(AMATH_dz) }
	"dt"		{ SYM(AMATH_dt) }
	"oint"		{ SYM(AMATH_oint) }
	"del"		{ SYM(AMATH_partial) }
	"grad"		{ SYM(AMATH_nabla) }
	"+-"		{ SYM(AMATH_pm) }
	"..."		{ SYM(AMATH_emptyset) }
	":."		{ SYM(AMATH_infty) }
	"/_"		{ SYM(AMATH_aleph) }
	"/_\\"		{ SYM(AMATH_ldots) }
	"'"		{ SYM(AMATH_therefore) }
	"tilde"		{ SYM(AMATH_angle) }
	"\\ "		{ SYM(AMATH_triangle) }
	"quad"		{ SYM(AMATH_prime) }
	"qquad"		{ SYM(AMATH_tilde) }
	"cdots"		{ SYM(AMATH_double_backslash) }
	"vdots"		{ SYM(AMATH_quad) }
	"ddots"		{ SYM(AMATH_qquad) }
	"diamond"	{ SYM(AMATH_cdots) }
	"square"	{ SYM(AMATH_vdots) }
	"|__"		{ SYM(AMATH_ddots) }
	"__|"		{ SYM(AMATH_diamond) }
	"|~"		{ SYM(AMATH_squar) }
	"~|"		{ SYM(AMATH_lfloor) }
	"O/"		{ SYM(AMATH_rfloor) }
	"oo"		{ SYM(AMATH_lceiling) }
	"aleph"		{ SYM(AMATH_rceiling) }
	"CC"		{ SYM(AMATH_complex) }
	"NN"		{ SYM(AMATH_natural) }
	"QQ"		{ SYM(AMATH_rational) }
	"RR"		{ SYM(AMATH_real) }
	"ZZ"		{ SYM(AMATH_integer) }
	"f"		{ SYM(AMATH_f) }
	"g"		{ SYM(AMATH_g) }
	"lim"		{ SYM(AMATH_lim) }
	"Lim"		{ SYM(AMATH_Lim) }
	"sin" 		{ SYM(AMATH_sin) }
	"cos" 		{ SYM(AMATH_cos) }
	"tan" 		{ SYM(AMATH_tan) }
	"sinh" 		{ SYM(AMATH_sinh) }
	"cosh" 		{ SYM(AMATH_cosh) }
	"tanh" 		{ SYM(AMATH_tanh) }
	"cot"		{ SYM(AMATH_cot) }
	"sec"		{ SYM(AMATH_sec) }
	"csc"		{ SYM(AMATH_csc) }
	"log"		{ SYM(AMATH_log) }
	"ln"		{ SYM(AMATH_ln) }
	"det"		{ SYM(AMATH_det) }
	"dim"		{ SYM(AMATH_dim) }
	"mod"		{ SYM(AMATH_mod) }
	"gcd"		{ SYM(AMATH_gcd) }
	"lcm"		{ SYM(AMATH_lcm) }
	"lub"		{ SYM(AMATH_lub) }
	"glb"		{ SYM(AMATH_glb) }
	"min"		{ SYM(AMATH_min) }
	"max"		{ SYM(AMATH_max) }
	"hat"		{ SYM(AMATH_hat) }
	"bar"		{ SYM(AMATH_bar) }
	"ul"		{ SYM(AMATH_ul) }
	"vec"		{ SYM(AMATH_vec) }
	"dot"		{ SYM(AMATH_dot) }
	"ddot"		{ SYM(AMATH_ddot) }
	"uarr" 		{ SYM(AMATH_uarr) }
	"darr" 		{ SYM(AMATH_darr) }
	"rarr" 		{ SYM(AMATH_rarr) }
	"->" 		{ SYM(AMATH_to) }
	">->" 		{ SYM(AMATH_inject) }
	"->>" 		{ SYM(AMATH_surject) }
	">->>" 		{ SYM(AMATH_biject) }
	"|->" 		{ SYM(AMATH_maps) }
	"larr" 		{ SYM(AMATH_larr) }
	"harr" 		{ SYM(AMATH_harr) }
	"rArr" 		{ SYM(AMATH_rArr) }
	"lArr" 		{ SYM(AMATH_lArr) }
	"hArr" 		{ SYM(AMATH_hArr) }
	"sqrt"		{ SYM(AMATH_sqrt) }
	"text"		{ SYM(AMATH_text) }
	"frac"		{ SYM(AMATH_frac) }
	"root"		{ SYM(AMATH_root) }
	"stackrel"	{ SYM(AMATH_stackrel) }
	"/"		{ SYM(AMATH_fracdiv) }
	"_"		{ SYM(AMATH_sub) }
	"^"		{ SYM(AMATH_sup) }
	","		{ SYM(AMATH_comma) }
	'"'.+'"'	{ NEW_SYM(TEXT) }
	[ \t]+		{ SYM(AMATH_whitespace) }
	[A-Za-z]+	{ NEW_SYM(IDENTIFIER) }
	[0-9]+'.'?[0-9]*{ NEW_SYM(NUMBER) }
	"\000"		{ SYM(AMATH_EOL) }
	[^]		{ SYM(AMATH_EOL) }

*/
}
