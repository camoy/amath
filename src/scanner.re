#include "syms.h"
#include "parser.h"
#include <stdlib.h>
#include <string.h>

#define YYCTYPE         char
#define YYCURSOR        cursor
#define YYMARKER	marker
#define YYLIMIT         (cursor+l)
#define YYFILL(n)
#define NEXTCURSOR	*cursor_ptr = cursor

const struct sym *scan(char **cursor_ptr, int l)
{
	char *marker = 0;
	char *cursor = *cursor_ptr;
	char *t = cursor;

/*!re2c
        re2c:indent:top = 2;

	"alpha"		{ NEXTCURSOR; return &syms[SYM_alpha]; }
	"beta"		{ NEXTCURSOR; return &syms[SYM_beta]; }
	"chi"		{ NEXTCURSOR; return &syms[SYM_chi]; }
	"delta"		{ NEXTCURSOR; return &syms[SYM_delta]; }
	"Delta"		{ NEXTCURSOR; return &syms[SYM_Delta]; }
	"epsi"		{ NEXTCURSOR; return &syms[SYM_epsi]; }
	"varepsilon"	{ NEXTCURSOR; return &syms[SYM_varepsilon]; }
	"eta"		{ NEXTCURSOR; return &syms[SYM_eta]; }
	"gamma"		{ NEXTCURSOR; return &syms[SYM_gamma]; }
	"Gamma"		{ NEXTCURSOR; return &syms[SYM_Gamma]; }
	"iota"		{ NEXTCURSOR; return &syms[SYM_iota]; }
	"kappa"		{ NEXTCURSOR; return &syms[SYM_kappa]; }
	"lambda"	{ NEXTCURSOR; return &syms[SYM_lambda]; }
	"Lambda"	{ NEXTCURSOR; return &syms[SYM_Lambda]; }
	"lamda"		{ NEXTCURSOR; return &syms[SYM_lamda]; }
	"Lamda"		{ NEXTCURSOR; return &syms[SYM_Lamda]; }
	"mu"		{ NEXTCURSOR; return &syms[SYM_mu]; }
	"nu"		{ NEXTCURSOR; return &syms[SYM_nu]; }
	"omega"		{ NEXTCURSOR; return &syms[SYM_omega]; }
	"Omega"		{ NEXTCURSOR; return &syms[SYM_Omega]; }
	"phi"		{ NEXTCURSOR; return &syms[SYM_phi]; }
	"varphi"	{ NEXTCURSOR; return &syms[SYM_varphi]; }
	"Phi"		{ NEXTCURSOR; return &syms[SYM_Phi]; }
	"pi"		{ NEXTCURSOR; return &syms[SYM_pi]; }
	"Pi"		{ NEXTCURSOR; return &syms[SYM_Pi]; }
	"psi"		{ NEXTCURSOR; return &syms[SYM_psi]; }
	"Psi"		{ NEXTCURSOR; return &syms[SYM_Psi]; }
	"rho"		{ NEXTCURSOR; return &syms[SYM_rho]; }
	"sigma"		{ NEXTCURSOR; return &syms[SYM_sigma]; }
	"Sigma"		{ NEXTCURSOR; return &syms[SYM_Sigma]; }
	"tau"		{ NEXTCURSOR; return &syms[SYM_tau]; }
	"theta"		{ NEXTCURSOR; return &syms[SYM_theta]; }
	"varthetaut"	{ NEXTCURSOR; return &syms[SYM_varthetaut]; }
	"Theta"		{ NEXTCURSOR; return &syms[SYM_Theta]; }
	"upsilon"	{ NEXTCURSOR; return &syms[SYM_upsilon]; }
	"xi"		{ NEXTCURSOR; return &syms[SYM_xi]; }
	"Xi"		{ NEXTCURSOR; return &syms[SYM_Xi]; }
	"zeta"		{ NEXTCURSOR; return &syms[SYM_zeta]; }
	"+"		{ NEXTCURSOR; return &syms[SYM_plus]; }
	"-"		{ NEXTCURSOR; return &syms[SYM_minus]; }
	"*"		{ NEXTCURSOR; return &syms[SYM_cdot]; }
	"**"		{ NEXTCURSOR; return &syms[SYM_ast]; }
	"***"		{ NEXTCURSOR; return &syms[SYM_star]; }
	"//"		{ NEXTCURSOR; return &syms[SYM_slash]; }
	"\\\\"		{ NEXTCURSOR; return &syms[SYM_backslash]; }
	"setminus"	{ NEXTCURSOR; return &syms[SYM_setminus]; }
	"xx"		{ NEXTCURSOR; return &syms[SYM_times]; }
	"-:"		{ NEXTCURSOR; return &syms[SYM_div]; }
	"divide"	{ NEXTCURSOR; return &syms[SYM_divide]; }
	"@"		{ NEXTCURSOR; return &syms[SYM_circ]; }
	"o+"		{ NEXTCURSOR; return &syms[SYM_oplus]; }
	"ox"		{ NEXTCURSOR; return &syms[SYM_otimes]; }
	"o."		{ NEXTCURSOR; return &syms[SYM_odot]; }
	"sum"		{ NEXTCURSOR; return &syms[SYM_sum]; }
	"prod"		{ NEXTCURSOR; return &syms[SYM_prod]; }
	"^^"		{ NEXTCURSOR; return &syms[SYM_wedge]; }
	"^^^"		{ NEXTCURSOR; return &syms[SYM_bigwedge]; }
	"vv"		{ NEXTCURSOR; return &syms[SYM_vee]; }
	"vvv"		{ NEXTCURSOR; return &syms[SYM_bigvee]; }
	"nn"		{ NEXTCURSOR; return &syms[SYM_cap]; }
	"nnn"		{ NEXTCURSOR; return &syms[SYM_bigcap]; }
	"uu"		{ NEXTCURSOR; return &syms[SYM_cup]; }
	"uuu"		{ NEXTCURSOR; return &syms[SYM_bigcup]; }
	"="		{ NEXTCURSOR; return &syms[SYM_eq]; }
	"!="		{ NEXTCURSOR; return &syms[SYM_ne]; }
	":="		{ NEXTCURSOR; return &syms[SYM_def]; }
	"lt"		{ NEXTCURSOR; return &syms[SYM_lt]; }
	"<="		{ NEXTCURSOR; return &syms[SYM_le]; }
	"lt="		{ NEXTCURSOR; return &syms[SYM_leq]; }
	"gt"		{ NEXTCURSOR; return &syms[SYM_gt]; }
	">="		{ NEXTCURSOR; return &syms[SYM_ge]; }
	"gt="		{ NEXTCURSOR; return &syms[SYM_geq]; }
	"-<"		{ NEXTCURSOR; return &syms[SYM_prec]; }
	"-lt"		{ NEXTCURSOR; return &syms[SYM_lt2]; }
	">-"		{ NEXTCURSOR; return &syms[SYM_succ]; }
	"-<="		{ NEXTCURSOR; return &syms[SYM_preceq]; }
	">-="		{ NEXTCURSOR; return &syms[SYM_succeq]; }
	"in"		{ NEXTCURSOR; return &syms[SYM_in]; }
	"!in"		{ NEXTCURSOR; return &syms[SYM_notin]; }
	"sub"		{ NEXTCURSOR; return &syms[SYM_subset]; }
	"sup"		{ NEXTCURSOR; return &syms[SYM_supset]; }
	"sube"		{ NEXTCURSOR; return &syms[SYM_subseteq]; }
	"supe"		{ NEXTCURSOR; return &syms[SYM_supseteq]; }
	"-="		{ NEXTCURSOR; return &syms[SYM_equiv]; }
	"~="		{ NEXTCURSOR; return &syms[SYM_cong]; }
	"~~"		{ NEXTCURSOR; return &syms[SYM_approx]; }
	"prop"		{ NEXTCURSOR; return &syms[SYM_propto]; }
	"and"		{ NEXTCURSOR; return &syms[SYM_and]; }
	"or"		{ NEXTCURSOR; return &syms[SYM_or]; }
	"not"		{ NEXTCURSOR; return &syms[SYM_neg]; }
	"=>"		{ NEXTCURSOR; return &syms[SYM_implies]; }
	"if"		{ NEXTCURSOR; return &syms[SYM_if]; }
	"<=>"		{ NEXTCURSOR; return &syms[SYM_iff]; }
	"AA"		{ NEXTCURSOR; return &syms[SYM_forall]; }
	"EE"		{ NEXTCURSOR; return &syms[SYM_exists]; }
	"_|_"		{ NEXTCURSOR; return &syms[SYM_bot]; }
	"TT"		{ NEXTCURSOR; return &syms[SYM_top]; }
	"|--"		{ NEXTCURSOR; return &syms[SYM_vdash]; }
	"|=="		{ NEXTCURSOR; return &syms[SYM_models]; }
	"(" 		{ NEXTCURSOR; return &syms[SYM_lparen]; }
	")" 		{ NEXTCURSOR; return &syms[SYM_rparen]; }
	"[" 		{ NEXTCURSOR; return &syms[SYM_lbracket]; }
	"]" 		{ NEXTCURSOR; return &syms[SYM_rbracket]; }
	"{" 		{ NEXTCURSOR; return &syms[SYM_lcurly]; }
	"}" 		{ NEXTCURSOR; return &syms[SYM_rcurly]; }
	"|" 		{ NEXTCURSOR; return &syms[SYM_pipe]; }
	"||"		{ NEXTCURSOR; return &syms[SYM_doublepipe]; }
	"(:" 		{ NEXTCURSOR; return &syms[SYM_lparencolon]; }
	":)" 		{ NEXTCURSOR; return &syms[SYM_rparencolon]; }
	"<<" 		{ NEXTCURSOR; return &syms[SYM_langle]; }
	">>" 		{ NEXTCURSOR; return &syms[SYM_rangle]; }
	"{:" 		{ NEXTCURSOR; return &syms[SYM_linvis]; }
	":}" 		{ NEXTCURSOR; return &syms[SYM_rinvis]; }
	"int"		{ NEXTCURSOR; return &syms[SYM_int]; }
	"dx"		{ NEXTCURSOR; return &syms[SYM_dx]; }
	"dy"		{ NEXTCURSOR; return &syms[SYM_dy]; }
	"dz"		{ NEXTCURSOR; return &syms[SYM_dz]; }
	"dt"		{ NEXTCURSOR; return &syms[SYM_dt]; }
	"oint"		{ NEXTCURSOR; return &syms[SYM_oint]; }
	"del"		{ NEXTCURSOR; return &syms[SYM_partial]; }
	"grad"		{ NEXTCURSOR; return &syms[SYM_nabla]; }
	"+-"		{ NEXTCURSOR; return &syms[SYM_pm]; }
	"..."		{ NEXTCURSOR; return &syms[SYM_emptyset]; }
	":."		{ NEXTCURSOR; return &syms[SYM_infty]; }
	"/_"		{ NEXTCURSOR; return &syms[SYM_aleph]; }
	"/_\\"		{ NEXTCURSOR; return &syms[SYM_ldots]; }
	"'"		{ NEXTCURSOR; return &syms[SYM_therefore]; }
	"tilde"		{ NEXTCURSOR; return &syms[SYM_angle]; }
	"\\ "		{ NEXTCURSOR; return &syms[SYM_triangle]; }
	"quad"		{ NEXTCURSOR; return &syms[SYM_prime]; }
	"qquad"		{ NEXTCURSOR; return &syms[SYM_tilde]; }
	"cdots"		{ NEXTCURSOR; return &syms[SYM_double_backslash]; }
	"vdots"		{ NEXTCURSOR; return &syms[SYM_quad]; }
	"ddots"		{ NEXTCURSOR; return &syms[SYM_qquad]; }
	"diamond"	{ NEXTCURSOR; return &syms[SYM_cdots]; }
	"square"	{ NEXTCURSOR; return &syms[SYM_vdots]; }
	"|__"		{ NEXTCURSOR; return &syms[SYM_ddots]; }
	"__|"		{ NEXTCURSOR; return &syms[SYM_diamond]; }
	"|~"		{ NEXTCURSOR; return &syms[SYM_squar]; }
	"~|"		{ NEXTCURSOR; return &syms[SYM_lfloor]; }
	"O/"		{ NEXTCURSOR; return &syms[SYM_rfloor]; }
	"oo"		{ NEXTCURSOR; return &syms[SYM_lceiling]; }
	"aleph"		{ NEXTCURSOR; return &syms[SYM_rceiling]; }
	"CC"		{ NEXTCURSOR; return &syms[SYM_complex]; }
	"NN"		{ NEXTCURSOR; return &syms[SYM_natural]; }
	"QQ"		{ NEXTCURSOR; return &syms[SYM_rational]; }
	"RR"		{ NEXTCURSOR; return &syms[SYM_real]; }
	"ZZ"		{ NEXTCURSOR; return &syms[SYM_integer]; }
	"f"		{ NEXTCURSOR; return &syms[SYM_f]; }
	"g"		{ NEXTCURSOR; return &syms[SYM_g]; }
	"lim"		{ NEXTCURSOR; return &syms[SYM_lim]; }
	"Lim"		{ NEXTCURSOR; return &syms[SYM_Lim]; }
	"sin" 		{ NEXTCURSOR; return &syms[SYM_sin]; }
	"cos" 		{ NEXTCURSOR; return &syms[SYM_cos]; }
	"tan" 		{ NEXTCURSOR; return &syms[SYM_tan]; }
	"sinh" 		{ NEXTCURSOR; return &syms[SYM_sinh]; }
	"cosh" 		{ NEXTCURSOR; return &syms[SYM_cosh]; }
	"tanh" 		{ NEXTCURSOR; return &syms[SYM_tanh]; }
	"cot"		{ NEXTCURSOR; return &syms[SYM_cot]; }
	"sec"		{ NEXTCURSOR; return &syms[SYM_sec]; }
	"csc"		{ NEXTCURSOR; return &syms[SYM_csc]; }
	"log"		{ NEXTCURSOR; return &syms[SYM_log]; }
	"ln"		{ NEXTCURSOR; return &syms[SYM_ln]; }
	"det"		{ NEXTCURSOR; return &syms[SYM_det]; }
	"dim"		{ NEXTCURSOR; return &syms[SYM_dim]; }
	"mod"		{ NEXTCURSOR; return &syms[SYM_mod]; }
	"gcd"		{ NEXTCURSOR; return &syms[SYM_gcd]; }
	"lcm"		{ NEXTCURSOR; return &syms[SYM_lcm]; }
	"lub"		{ NEXTCURSOR; return &syms[SYM_lub]; }
	"glb"		{ NEXTCURSOR; return &syms[SYM_glb]; }
	"min"		{ NEXTCURSOR; return &syms[SYM_min]; }
	"max"		{ NEXTCURSOR; return &syms[SYM_max]; }
	"hat"		{ NEXTCURSOR; return &syms[SYM_hat]; }
	"bar"		{ NEXTCURSOR; return &syms[SYM_bar]; }
	"ul"		{ NEXTCURSOR; return &syms[SYM_ul]; }
	"vec"		{ NEXTCURSOR; return &syms[SYM_vec]; }
	"dot"		{ NEXTCURSOR; return &syms[SYM_dot]; }
	"ddot"		{ NEXTCURSOR; return &syms[SYM_ddot]; }
	"uarr" 		{ NEXTCURSOR; return &syms[SYM_uarr]; }
	"darr" 		{ NEXTCURSOR; return &syms[SYM_darr]; }
	"rarr" 		{ NEXTCURSOR; return &syms[SYM_rarr]; }
	"->" 		{ NEXTCURSOR; return &syms[SYM_to]; }
	">->" 		{ NEXTCURSOR; return &syms[SYM_inject]; }
	"->>" 		{ NEXTCURSOR; return &syms[SYM_surject]; }
	">->>" 		{ NEXTCURSOR; return &syms[SYM_biject]; }
	"|->" 		{ NEXTCURSOR; return &syms[SYM_maps]; }
	"larr" 		{ NEXTCURSOR; return &syms[SYM_larr]; }
	"harr" 		{ NEXTCURSOR; return &syms[SYM_harr]; }
	"rArr" 		{ NEXTCURSOR; return &syms[SYM_rArr]; }
	"lArr" 		{ NEXTCURSOR; return &syms[SYM_lArr]; }
	"hArr" 		{ NEXTCURSOR; return &syms[SYM_hArr]; }
	"sqrt"		{ NEXTCURSOR; return &syms[SYM_sqrt]; }
	"text"		{ NEXTCURSOR; return &syms[SYM_text]; }
	"frac"		{ NEXTCURSOR; return &syms[SYM_frac]; }
	"root"		{ NEXTCURSOR; return &syms[SYM_root]; }
	"stackrel"	{ NEXTCURSOR; return &syms[SYM_stackrel]; }
	"/"		{ NEXTCURSOR; return &syms[SYM_fracdiv]; }
	"_"		{ NEXTCURSOR; return &syms[SYM_sub]; }
	"^"		{ NEXTCURSOR; return &syms[SYM_sup]; }
	[ \t]+		{ NEXTCURSOR; return &syms[SYM_ignore]; }
	[A-Za-z]+	{ NEXTCURSOR; struct sym *a = malloc(sizeof(struct sym)); a->type=IDENTIFIER; a->str=strndup(t, YYCURSOR - t); return a; }
	[0-9]+'.'?[0-9]*{ NEXTCURSOR; struct sym *a = malloc(sizeof(struct sym)); a->type=NUMBER; a->str=strndup(t, YYCURSOR - t); return a; }
	"\000"		{ NEXTCURSOR; return &syms[SYM_EOL]; }
	[^]		{ NEXTCURSOR; return &syms[SYM_EOL]; }

*/
}
