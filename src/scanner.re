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
			return &syms[t];
#define NEW_SYM(t)	*cursor_ptr = cursor;\
			struct sym *a = malloc(sizeof(struct sym));\
			a->type=t;\
			a->str=strndup(old, YYCURSOR - old);\
			return a;

const struct sym *scan(char **cursor_ptr, size_t len)
{
	char *marker = 0;
	char *cursor = *cursor_ptr;
	char *old = cursor;

/*!re2c
        re2c:indent:top = 2;

	"alpha"		{ SYM(SYM_alpha) }
	"beta"		{ SYM(SYM_beta) }
	"chi"		{ SYM(SYM_chi) }
	"delta"		{ SYM(SYM_delta) }
	"Delta"		{ SYM(SYM_Delta) }
	"epsi"		{ SYM(SYM_epsi) }
	"varepsilon"	{ SYM(SYM_varepsilon) }
	"eta"		{ SYM(SYM_eta) }
	"gamma"		{ SYM(SYM_gamma) }
	"Gamma"		{ SYM(SYM_Gamma) }
	"iota"		{ SYM(SYM_iota) }
	"kappa"		{ SYM(SYM_kappa) }
	"lambda"	{ SYM(SYM_lambda) }
	"Lambda"	{ SYM(SYM_Lambda) }
	"lamda"		{ SYM(SYM_lamda) }
	"Lamda"		{ SYM(SYM_Lamda) }
	"mu"		{ SYM(SYM_mu) }
	"nu"		{ SYM(SYM_nu) }
	"omega"		{ SYM(SYM_omega) }
	"Omega"		{ SYM(SYM_Omega) }
	"phi"		{ SYM(SYM_phi) }
	"varphi"	{ SYM(SYM_varphi) }
	"Phi"		{ SYM(SYM_Phi) }
	"pi"		{ SYM(SYM_pi) }
	"Pi"		{ SYM(SYM_Pi) }
	"psi"		{ SYM(SYM_psi) }
	"Psi"		{ SYM(SYM_Psi) }
	"rho"		{ SYM(SYM_rho) }
	"sigma"		{ SYM(SYM_sigma) }
	"Sigma"		{ SYM(SYM_Sigma) }
	"tau"		{ SYM(SYM_tau) }
	"theta"		{ SYM(SYM_theta) }
	"varthetaut"	{ SYM(SYM_varthetaut) }
	"Theta"		{ SYM(SYM_Theta) }
	"upsilon"	{ SYM(SYM_upsilon) }
	"xi"		{ SYM(SYM_xi) }
	"Xi"		{ SYM(SYM_Xi) }
	"zeta"		{ SYM(SYM_zeta) }
	"+"		{ SYM(SYM_plus) }
	"-"		{ SYM(SYM_minus) }
	"*"		{ SYM(SYM_cdot) }
	"**"		{ SYM(SYM_ast) }
	"***"		{ SYM(SYM_star) }
	"//"		{ SYM(SYM_slash) }
	"\\\\"		{ SYM(SYM_backslash) }
	"setminus"	{ SYM(SYM_setminus) }
	"xx"		{ SYM(SYM_times) }
	"-:"		{ SYM(SYM_div) }
	"divide"	{ SYM(SYM_divide) }
	"@"		{ SYM(SYM_circ) }
	"o+"		{ SYM(SYM_oplus) }
	"ox"		{ SYM(SYM_otimes) }
	"o."		{ SYM(SYM_odot) }
	"sum"		{ SYM(SYM_sum) }
	"prod"		{ SYM(SYM_prod) }
	"^^"		{ SYM(SYM_wedge) }
	"^^^"		{ SYM(SYM_bigwedge) }
	"vv"		{ SYM(SYM_vee) }
	"vvv"		{ SYM(SYM_bigvee) }
	"nn"		{ SYM(SYM_cap) }
	"nnn"		{ SYM(SYM_bigcap) }
	"uu"		{ SYM(SYM_cup) }
	"uuu"		{ SYM(SYM_bigcup) }
	"="		{ SYM(SYM_eq) }
	"!="		{ SYM(SYM_ne) }
	":="		{ SYM(SYM_def) }
	"lt"		{ SYM(SYM_lt) }
	"<="		{ SYM(SYM_le) }
	"lt="		{ SYM(SYM_leq) }
	"gt"		{ SYM(SYM_gt) }
	">="		{ SYM(SYM_ge) }
	"gt="		{ SYM(SYM_geq) }
	"-<"		{ SYM(SYM_prec) }
	"-lt"		{ SYM(SYM_lt2) }
	">-"		{ SYM(SYM_succ) }
	"-<="		{ SYM(SYM_preceq) }
	">-="		{ SYM(SYM_succeq) }
	"in"		{ SYM(SYM_in) }
	"!in"		{ SYM(SYM_notin) }
	"sub"		{ SYM(SYM_subset) }
	"sup"		{ SYM(SYM_supset) }
	"sube"		{ SYM(SYM_subseteq) }
	"supe"		{ SYM(SYM_supseteq) }
	"-="		{ SYM(SYM_equiv) }
	"~="		{ SYM(SYM_cong) }
	"~~"		{ SYM(SYM_approx) }
	"prop"		{ SYM(SYM_propto) }
	"and"		{ SYM(SYM_and) }
	"or"		{ SYM(SYM_or) }
	"not"		{ SYM(SYM_neg) }
	"=>"		{ SYM(SYM_implies) }
	"if"		{ SYM(SYM_if) }
	"<=>"		{ SYM(SYM_iff) }
	"AA"		{ SYM(SYM_forall) }
	"EE"		{ SYM(SYM_exists) }
	"_|_"		{ SYM(SYM_bot) }
	"TT"		{ SYM(SYM_top) }
	"|--"		{ SYM(SYM_vdash) }
	"|=="		{ SYM(SYM_models) }
	"(" 		{ SYM(SYM_lparen) }
	")" 		{ SYM(SYM_rparen) }
	"[" 		{ SYM(SYM_lbracket) }
	"]" 		{ SYM(SYM_rbracket) }
	"{" 		{ SYM(SYM_lcurly) }
	"}" 		{ SYM(SYM_rcurly) }
	"|" 		{ SYM(SYM_pipe) }
	"||"		{ SYM(SYM_doublepipe) }
	"(:" 		{ SYM(SYM_lparencolon) }
	":)" 		{ SYM(SYM_rparencolon) }
	"<<" 		{ SYM(SYM_langle) }
	">>" 		{ SYM(SYM_rangle) }
	"{:" 		{ SYM(SYM_linvis) }
	":}" 		{ SYM(SYM_rinvis) }
	"int"		{ SYM(SYM_int) }
	"dx"		{ SYM(SYM_dx) }
	"dy"		{ SYM(SYM_dy) }
	"dz"		{ SYM(SYM_dz) }
	"dt"		{ SYM(SYM_dt) }
	"oint"		{ SYM(SYM_oint) }
	"del"		{ SYM(SYM_partial) }
	"grad"		{ SYM(SYM_nabla) }
	"+-"		{ SYM(SYM_pm) }
	"..."		{ SYM(SYM_emptyset) }
	":."		{ SYM(SYM_infty) }
	"/_"		{ SYM(SYM_aleph) }
	"/_\\"		{ SYM(SYM_ldots) }
	"'"		{ SYM(SYM_therefore) }
	"tilde"		{ SYM(SYM_angle) }
	"\\ "		{ SYM(SYM_triangle) }
	"quad"		{ SYM(SYM_prime) }
	"qquad"		{ SYM(SYM_tilde) }
	"cdots"		{ SYM(SYM_double_backslash) }
	"vdots"		{ SYM(SYM_quad) }
	"ddots"		{ SYM(SYM_qquad) }
	"diamond"	{ SYM(SYM_cdots) }
	"square"	{ SYM(SYM_vdots) }
	"|__"		{ SYM(SYM_ddots) }
	"__|"		{ SYM(SYM_diamond) }
	"|~"		{ SYM(SYM_squar) }
	"~|"		{ SYM(SYM_lfloor) }
	"O/"		{ SYM(SYM_rfloor) }
	"oo"		{ SYM(SYM_lceiling) }
	"aleph"		{ SYM(SYM_rceiling) }
	"CC"		{ SYM(SYM_complex) }
	"NN"		{ SYM(SYM_natural) }
	"QQ"		{ SYM(SYM_rational) }
	"RR"		{ SYM(SYM_real) }
	"ZZ"		{ SYM(SYM_integer) }
	"f"		{ SYM(SYM_f) }
	"g"		{ SYM(SYM_g) }
	"lim"		{ SYM(SYM_lim) }
	"Lim"		{ SYM(SYM_Lim) }
	"sin" 		{ SYM(SYM_sin) }
	"cos" 		{ SYM(SYM_cos) }
	"tan" 		{ SYM(SYM_tan) }
	"sinh" 		{ SYM(SYM_sinh) }
	"cosh" 		{ SYM(SYM_cosh) }
	"tanh" 		{ SYM(SYM_tanh) }
	"cot"		{ SYM(SYM_cot) }
	"sec"		{ SYM(SYM_sec) }
	"csc"		{ SYM(SYM_csc) }
	"log"		{ SYM(SYM_log) }
	"ln"		{ SYM(SYM_ln) }
	"det"		{ SYM(SYM_det) }
	"dim"		{ SYM(SYM_dim) }
	"mod"		{ SYM(SYM_mod) }
	"gcd"		{ SYM(SYM_gcd) }
	"lcm"		{ SYM(SYM_lcm) }
	"lub"		{ SYM(SYM_lub) }
	"glb"		{ SYM(SYM_glb) }
	"min"		{ SYM(SYM_min) }
	"max"		{ SYM(SYM_max) }
	"hat"		{ SYM(SYM_hat) }
	"bar"		{ SYM(SYM_bar) }
	"ul"		{ SYM(SYM_ul) }
	"vec"		{ SYM(SYM_vec) }
	"dot"		{ SYM(SYM_dot) }
	"ddot"		{ SYM(SYM_ddot) }
	"uarr" 		{ SYM(SYM_uarr) }
	"darr" 		{ SYM(SYM_darr) }
	"rarr" 		{ SYM(SYM_rarr) }
	"->" 		{ SYM(SYM_to) }
	">->" 		{ SYM(SYM_inject) }
	"->>" 		{ SYM(SYM_surject) }
	">->>" 		{ SYM(SYM_biject) }
	"|->" 		{ SYM(SYM_maps) }
	"larr" 		{ SYM(SYM_larr) }
	"harr" 		{ SYM(SYM_harr) }
	"rArr" 		{ SYM(SYM_rArr) }
	"lArr" 		{ SYM(SYM_lArr) }
	"hArr" 		{ SYM(SYM_hArr) }
	"sqrt"		{ SYM(SYM_sqrt) }
	"text"		{ SYM(SYM_text) }
	"frac"		{ SYM(SYM_frac) }
	"root"		{ SYM(SYM_root) }
	"stackrel"	{ SYM(SYM_stackrel) }
	"/"		{ SYM(SYM_fracdiv) }
	"_"		{ SYM(SYM_sub) }
	"^"		{ SYM(SYM_sup) }
	[ \t]+		{ SYM(SYM_ignore) }
	[A-Za-z]+	{ NEW_SYM(IDENTIFIER) }
	[0-9]+'.'?[0-9]*{ NEW_SYM(NUMBER) }
	"\000"		{ SYM(SYM_EOL) }
	[^]		{ SYM(SYM_EOL) }

*/
}
