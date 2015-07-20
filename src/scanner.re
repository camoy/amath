#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "syms.h"

#define YYCTYPE         char
#define YYCURSOR        c
#define YYMARKER	marker
#define YYLIMIT         (c+len)
#define YYFILL(n)

static inline struct amath_node *get_sym(char *c, char **c_ptr, enum amath_symt sym)
{
	*c_ptr = c;
	return &amath_syms[sym];
}

static inline struct amath_node *new_sym(char *c, char **c_ptr, char *old, int token)
{
	struct amath_node *a = malloc(sizeof(struct amath_node));
	*c_ptr = c;
	a->token = token;
	a->str = strndup(old, c - old);
	a->extra = AMATH_none;
	return a;
}

struct amath_node *scan(char **c_ptr, size_t len)
{
	char *marker = 0;
	char *c = *c_ptr;
	char *old = c;

/*!re2c
        re2c:indent:top = 2;

	"alpha"		{ return get_sym(c, c_ptr, AMATH_alpha); }
	"beta"		{ return get_sym(c, c_ptr, AMATH_beta); }
	"chi"		{ return get_sym(c, c_ptr, AMATH_chi); }
	"delta"		{ return get_sym(c, c_ptr, AMATH_delta); }
	"Delta"		{ return get_sym(c, c_ptr, AMATH_Delta); }
	"epsi"		{ return get_sym(c, c_ptr, AMATH_epsi); }
	"varepsilon"	{ return get_sym(c, c_ptr, AMATH_varepsilon); }
	"eta"		{ return get_sym(c, c_ptr, AMATH_eta); }
	"gamma"		{ return get_sym(c, c_ptr, AMATH_gamma); }
	"Gamma"		{ return get_sym(c, c_ptr, AMATH_Gamma); }
	"iota"		{ return get_sym(c, c_ptr, AMATH_iota); }
	"kappa"		{ return get_sym(c, c_ptr, AMATH_kappa); }
	"lambda"	{ return get_sym(c, c_ptr, AMATH_lambda); }
	"Lambda"	{ return get_sym(c, c_ptr, AMATH_Lambda); }
	"lamda"		{ return get_sym(c, c_ptr, AMATH_lamda); }
	"Lamda"		{ return get_sym(c, c_ptr, AMATH_Lamda); }
	"mu"		{ return get_sym(c, c_ptr, AMATH_mu); }
	"nu"		{ return get_sym(c, c_ptr, AMATH_nu); }
	"omega"		{ return get_sym(c, c_ptr, AMATH_omega); }
	"Omega"		{ return get_sym(c, c_ptr, AMATH_Omega); }
	"phi"		{ return get_sym(c, c_ptr, AMATH_phi); }
	"varphi"	{ return get_sym(c, c_ptr, AMATH_varphi); }
	"Phi"		{ return get_sym(c, c_ptr, AMATH_Phi); }
	"pi"		{ return get_sym(c, c_ptr, AMATH_pi); }
	"Pi"		{ return get_sym(c, c_ptr, AMATH_Pi); }
	"psi"		{ return get_sym(c, c_ptr, AMATH_psi); }
	"Psi"		{ return get_sym(c, c_ptr, AMATH_Psi); }
	"rho"		{ return get_sym(c, c_ptr, AMATH_rho); }
	"sigma"		{ return get_sym(c, c_ptr, AMATH_sigma); }
	"Sigma"		{ return get_sym(c, c_ptr, AMATH_Sigma); }
	"tau"		{ return get_sym(c, c_ptr, AMATH_tau); }
	"theta"		{ return get_sym(c, c_ptr, AMATH_theta); }
	"varthetaut"	{ return get_sym(c, c_ptr, AMATH_varthetaut); }
	"Theta"		{ return get_sym(c, c_ptr, AMATH_Theta); }
	"upsilon"	{ return get_sym(c, c_ptr, AMATH_upsilon); }
	"xi"		{ return get_sym(c, c_ptr, AMATH_xi); }
	"Xi"		{ return get_sym(c, c_ptr, AMATH_Xi); }
	"zeta"		{ return get_sym(c, c_ptr, AMATH_zeta); }
	"+"		{ return get_sym(c, c_ptr, AMATH_plus); }
	" - "		{ return get_sym(c, c_ptr, AMATH_minus); }
	"*"		{ return get_sym(c, c_ptr, AMATH_cdot); }
	"**"		{ return get_sym(c, c_ptr, AMATH_ast); }
	"***"		{ return get_sym(c, c_ptr, AMATH_star); }
	"//"		{ return get_sym(c, c_ptr, AMATH_slash); }
	"\\\\"		{ return get_sym(c, c_ptr, AMATH_backslash); }
	"setminus"	{ return get_sym(c, c_ptr, AMATH_setminus); }
	"xx"		{ return get_sym(c, c_ptr, AMATH_times); }
	"-:"		{ return get_sym(c, c_ptr, AMATH_div); }
	"divide"	{ return get_sym(c, c_ptr, AMATH_divide); }
	"@"		{ return get_sym(c, c_ptr, AMATH_circ); }
	"o+"		{ return get_sym(c, c_ptr, AMATH_oplus); }
	"ox"		{ return get_sym(c, c_ptr, AMATH_otimes); }
	"o."		{ return get_sym(c, c_ptr, AMATH_odot); }
	"sum"		{ return get_sym(c, c_ptr, AMATH_sum); }
	"prod"		{ return get_sym(c, c_ptr, AMATH_prod); }
	"^^"		{ return get_sym(c, c_ptr, AMATH_wedge); }
	"^^^"		{ return get_sym(c, c_ptr, AMATH_bigwedge); }
	"vv"		{ return get_sym(c, c_ptr, AMATH_vee); }
	"vvv"		{ return get_sym(c, c_ptr, AMATH_bigvee); }
	"nn"		{ return get_sym(c, c_ptr, AMATH_cap); }
	"nnn"		{ return get_sym(c, c_ptr, AMATH_bigcap); }
	"uu"		{ return get_sym(c, c_ptr, AMATH_cup); }
	"uuu"		{ return get_sym(c, c_ptr, AMATH_bigcup); }
	"="		{ return get_sym(c, c_ptr, AMATH_eq); }
	"!="		{ return get_sym(c, c_ptr, AMATH_ne); }
	":="		{ return get_sym(c, c_ptr, AMATH_def); }
	"lt"		{ return get_sym(c, c_ptr, AMATH_lt); }
	"<="		{ return get_sym(c, c_ptr, AMATH_le); }
	"lt="		{ return get_sym(c, c_ptr, AMATH_leq); }
	"gt"		{ return get_sym(c, c_ptr, AMATH_gt); }
	">="		{ return get_sym(c, c_ptr, AMATH_ge); }
	"gt="		{ return get_sym(c, c_ptr, AMATH_geq); }
	"-<"		{ return get_sym(c, c_ptr, AMATH_prec); }
	"-lt"		{ return get_sym(c, c_ptr, AMATH_lt2); }
	">-"		{ return get_sym(c, c_ptr, AMATH_succ); }
	"-<="		{ return get_sym(c, c_ptr, AMATH_preceq); }
	">-="		{ return get_sym(c, c_ptr, AMATH_succeq); }
	"in"		{ return get_sym(c, c_ptr, AMATH_in); }
	"!in"		{ return get_sym(c, c_ptr, AMATH_notin); }
	"sub"		{ return get_sym(c, c_ptr, AMATH_subset); }
	"sup"		{ return get_sym(c, c_ptr, AMATH_supset); }
	"sube"		{ return get_sym(c, c_ptr, AMATH_subseteq); }
	"supe"		{ return get_sym(c, c_ptr, AMATH_supseteq); }
	"-="		{ return get_sym(c, c_ptr, AMATH_equiv); }
	"~="		{ return get_sym(c, c_ptr, AMATH_cong); }
	"~~"		{ return get_sym(c, c_ptr, AMATH_approx); }
	"prop"		{ return get_sym(c, c_ptr, AMATH_propto); }
	"and"		{ return get_sym(c, c_ptr, AMATH_and); }
	"or"		{ return get_sym(c, c_ptr, AMATH_or); }
	"not"		{ return get_sym(c, c_ptr, AMATH_neg); }
	"=>"		{ return get_sym(c, c_ptr, AMATH_implies); }
	"if"		{ return get_sym(c, c_ptr, AMATH_if); }
	"<=>"		{ return get_sym(c, c_ptr, AMATH_iff); }
	"AA"		{ return get_sym(c, c_ptr, AMATH_forall); }
	"EE"		{ return get_sym(c, c_ptr, AMATH_exists); }
	"_|_"		{ return get_sym(c, c_ptr, AMATH_bot); }
	"TT"		{ return get_sym(c, c_ptr, AMATH_top); }
	"|--"		{ return get_sym(c, c_ptr, AMATH_vdash); }
	"|=="		{ return get_sym(c, c_ptr, AMATH_models); }
	"(" 		{ return get_sym(c, c_ptr, AMATH_lparen); }
	")" 		{ return get_sym(c, c_ptr, AMATH_rparen); }
	"[" 		{ return get_sym(c, c_ptr, AMATH_lbracket); }
	"]" 		{ return get_sym(c, c_ptr, AMATH_rbracket); }
	"{" 		{ return get_sym(c, c_ptr, AMATH_lcurly); }
	"}" 		{ return get_sym(c, c_ptr, AMATH_rcurly); }
	"|" 		{ return get_sym(c, c_ptr, AMATH_pipe); }
	"||"		{ return get_sym(c, c_ptr, AMATH_doublepipe); }
	"(:" 		{ return get_sym(c, c_ptr, AMATH_lparencolon); }
	":)" 		{ return get_sym(c, c_ptr, AMATH_rparencolon); }
	"<<" 		{ return get_sym(c, c_ptr, AMATH_langle); }
	">>" 		{ return get_sym(c, c_ptr, AMATH_rangle); }
	"{:" 		{ return get_sym(c, c_ptr, AMATH_linvis); }
	":}" 		{ return get_sym(c, c_ptr, AMATH_rinvis); }
	"int"		{ return get_sym(c, c_ptr, AMATH_int); }
	"dx"		{ return get_sym(c, c_ptr, AMATH_dx); }
	"dy"		{ return get_sym(c, c_ptr, AMATH_dy); }
	"dz"		{ return get_sym(c, c_ptr, AMATH_dz); }
	"dt"		{ return get_sym(c, c_ptr, AMATH_dt); }
	"oint"		{ return get_sym(c, c_ptr, AMATH_oint); }
	"del"		{ return get_sym(c, c_ptr, AMATH_partial); }
	"grad"		{ return get_sym(c, c_ptr, AMATH_nabla); }
	"+-"		{ return get_sym(c, c_ptr, AMATH_pm); }
	"..."		{ return get_sym(c, c_ptr, AMATH_emptyset); }
	":."		{ return get_sym(c, c_ptr, AMATH_infty); }
	"/_"		{ return get_sym(c, c_ptr, AMATH_aleph); }
	"/_\\"		{ return get_sym(c, c_ptr, AMATH_ldots); }
	"'"		{ return get_sym(c, c_ptr, AMATH_therefore); }
	"tilde"		{ return get_sym(c, c_ptr, AMATH_angle); }
	"\\ "		{ return get_sym(c, c_ptr, AMATH_triangle); }
	"quad"		{ return get_sym(c, c_ptr, AMATH_prime); }
	"qquad"		{ return get_sym(c, c_ptr, AMATH_tilde); }
	"cdots"		{ return get_sym(c, c_ptr, AMATH_double_backslash); }
	"vdots"		{ return get_sym(c, c_ptr, AMATH_quad); }
	"ddots"		{ return get_sym(c, c_ptr, AMATH_qquad); }
	"diamond"	{ return get_sym(c, c_ptr, AMATH_cdots); }
	"square"	{ return get_sym(c, c_ptr, AMATH_vdots); }
	"|__"		{ return get_sym(c, c_ptr, AMATH_ddots); }
	"__|"		{ return get_sym(c, c_ptr, AMATH_diamond); }
	"|~"		{ return get_sym(c, c_ptr, AMATH_squar); }
	"~|"		{ return get_sym(c, c_ptr, AMATH_lfloor); }
	"O/"		{ return get_sym(c, c_ptr, AMATH_rfloor); }
	"oo"		{ return get_sym(c, c_ptr, AMATH_lceiling); }
	"aleph"		{ return get_sym(c, c_ptr, AMATH_rceiling); }
	"CC"		{ return get_sym(c, c_ptr, AMATH_complex); }
	"NN"		{ return get_sym(c, c_ptr, AMATH_natural); }
	"QQ"		{ return get_sym(c, c_ptr, AMATH_rational); }
	"RR"		{ return get_sym(c, c_ptr, AMATH_real); }
	"ZZ"		{ return get_sym(c, c_ptr, AMATH_integer); }
	"f"		{ return get_sym(c, c_ptr, AMATH_f); }
	"g"		{ return get_sym(c, c_ptr, AMATH_g); }
	"lim"		{ return get_sym(c, c_ptr, AMATH_lim); }
	"Lim"		{ return get_sym(c, c_ptr, AMATH_Lim); }
	"sin" 		{ return get_sym(c, c_ptr, AMATH_sin); }
	"cos" 		{ return get_sym(c, c_ptr, AMATH_cos); }
	"tan" 		{ return get_sym(c, c_ptr, AMATH_tan); }
	"sinh" 		{ return get_sym(c, c_ptr, AMATH_sinh); }
	"cosh" 		{ return get_sym(c, c_ptr, AMATH_cosh); }
	"tanh" 		{ return get_sym(c, c_ptr, AMATH_tanh); }
	"cot"		{ return get_sym(c, c_ptr, AMATH_cot); }
	"sec"		{ return get_sym(c, c_ptr, AMATH_sec); }
	"csc"		{ return get_sym(c, c_ptr, AMATH_csc); }
	"log"		{ return get_sym(c, c_ptr, AMATH_log); }
	"ln"		{ return get_sym(c, c_ptr, AMATH_ln); }
	"det"		{ return get_sym(c, c_ptr, AMATH_det); }
	"dim"		{ return get_sym(c, c_ptr, AMATH_dim); }
	"mod"		{ return get_sym(c, c_ptr, AMATH_mod); }
	"gcd"		{ return get_sym(c, c_ptr, AMATH_gcd); }
	"lcm"		{ return get_sym(c, c_ptr, AMATH_lcm); }
	"lub"		{ return get_sym(c, c_ptr, AMATH_lub); }
	"glb"		{ return get_sym(c, c_ptr, AMATH_glb); }
	"min"		{ return get_sym(c, c_ptr, AMATH_min); }
	"max"		{ return get_sym(c, c_ptr, AMATH_max); }
	"hat"		{ return get_sym(c, c_ptr, AMATH_hat); }
	"bar"		{ return get_sym(c, c_ptr, AMATH_bar); }
	"ul"		{ return get_sym(c, c_ptr, AMATH_ul); }
	"vec"		{ return get_sym(c, c_ptr, AMATH_vec); }
	"dot"		{ return get_sym(c, c_ptr, AMATH_dot); }
	"ddot"		{ return get_sym(c, c_ptr, AMATH_ddot); }
	"uarr" 		{ return get_sym(c, c_ptr, AMATH_uarr); }
	"darr" 		{ return get_sym(c, c_ptr, AMATH_darr); }
	"rarr" 		{ return get_sym(c, c_ptr, AMATH_rarr); }
	"->" 		{ return get_sym(c, c_ptr, AMATH_to); }
	">->" 		{ return get_sym(c, c_ptr, AMATH_inject); }
	"->>" 		{ return get_sym(c, c_ptr, AMATH_surject); }
	">->>" 		{ return get_sym(c, c_ptr, AMATH_biject); }
	"|->" 		{ return get_sym(c, c_ptr, AMATH_maps); }
	"larr" 		{ return get_sym(c, c_ptr, AMATH_larr); }
	"harr" 		{ return get_sym(c, c_ptr, AMATH_harr); }
	"rArr" 		{ return get_sym(c, c_ptr, AMATH_rArr); }
	"lArr" 		{ return get_sym(c, c_ptr, AMATH_lArr); }
	"hArr" 		{ return get_sym(c, c_ptr, AMATH_hArr); }
	"sqrt"		{ return get_sym(c, c_ptr, AMATH_sqrt); }
	"text"		{ return get_sym(c, c_ptr, AMATH_text); }
	"frac"		{ return get_sym(c, c_ptr, AMATH_frac); }
	"root"		{ return get_sym(c, c_ptr, AMATH_root); }
	"stackrel"	{ return get_sym(c, c_ptr, AMATH_stackrel); }
	"/"		{ return get_sym(c, c_ptr, AMATH_fracdiv); }
	"_"		{ return get_sym(c, c_ptr, AMATH_sub); }
	"^"		{ return get_sym(c, c_ptr, AMATH_sup); }
	","		{ return get_sym(c, c_ptr, AMATH_comma); }
	'"'.+'"'	{ return new_sym(c, c_ptr, old, TEXT); }
	[ \t]+		{ return get_sym(c, c_ptr, AMATH_whitespace); }
	[A-Za-z]+	{ return new_sym(c, c_ptr, old, IDENTIFIER); }
	"-"?[0-9]+'.'?[0-9]*{ return new_sym(c, c_ptr, old, NUMBER); }
	"\000"		{ return get_sym(c, c_ptr, AMATH_EOL); }
	[^]		{ return get_sym(c, c_ptr, AMATH_EOL); }

*/
}
