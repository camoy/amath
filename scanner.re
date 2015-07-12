#include "syms.h"
#include "parser.h"
#include <string.h>

#define YYCTYPE         char
#define YYCURSOR        cursor
#define YYMARKER	marker
#define YYLIMIT         (cursor+l)
#define YYFILL(n)
#define NEXTCURSOR	*cursor_ptr = cursor
#define CLONE_STRUCT(A) struct sym *a = malloc(sizeof(struct sym)); a->type=syms[A].type; a->str=strdup(syms[A].str); a->pos=syms[A].pos; return a

const struct sym *scan(char **cursor_ptr, int l)
{
	char *marker = 0;
	char *cursor = *cursor_ptr;
	char *t = cursor;

/*!re2c
        re2c:indent:top = 2;

	"alpha"		{ NEXTCURSOR; CLONE_STRUCT(SYM_alpha); }
	"beta"		{ NEXTCURSOR; CLONE_STRUCT(SYM_beta); }
	"chi"		{ NEXTCURSOR; CLONE_STRUCT(SYM_chi); }
	"delta"		{ NEXTCURSOR; CLONE_STRUCT(SYM_delta); }
	"Delta"		{ NEXTCURSOR; CLONE_STRUCT(SYM_Delta); }
	"epsi"		{ NEXTCURSOR; CLONE_STRUCT(SYM_epsi); }
	"varepsilon"	{ NEXTCURSOR; CLONE_STRUCT(SYM_varepsilon); }
	"eta"		{ NEXTCURSOR; CLONE_STRUCT(SYM_eta); }
	"gamma"		{ NEXTCURSOR; CLONE_STRUCT(SYM_gamma); }
	"Gamma"		{ NEXTCURSOR; CLONE_STRUCT(SYM_Gamma); }
	"iota"		{ NEXTCURSOR; CLONE_STRUCT(SYM_iota); }
	"kappa"		{ NEXTCURSOR; CLONE_STRUCT(SYM_kappa); }
	"lambda"	{ NEXTCURSOR; CLONE_STRUCT(SYM_lambda); }
	"Lambda"	{ NEXTCURSOR; CLONE_STRUCT(SYM_Lambda); }
	"lamda"		{ NEXTCURSOR; CLONE_STRUCT(SYM_lamda); }
	"Lamda"		{ NEXTCURSOR; CLONE_STRUCT(SYM_Lamda); }
	"mu"		{ NEXTCURSOR; CLONE_STRUCT(SYM_mu); }
	"nu"		{ NEXTCURSOR; CLONE_STRUCT(SYM_nu); }
	"omega"		{ NEXTCURSOR; CLONE_STRUCT(SYM_omega); }
	"Omega"		{ NEXTCURSOR; CLONE_STRUCT(SYM_Omega); }
	"phi"		{ NEXTCURSOR; CLONE_STRUCT(SYM_phi); }
	"varphi"	{ NEXTCURSOR; CLONE_STRUCT(SYM_varphi); }
	"Phi"		{ NEXTCURSOR; CLONE_STRUCT(SYM_Phi); }
	"pi"		{ NEXTCURSOR; CLONE_STRUCT(SYM_pi); }
	"Pi"		{ NEXTCURSOR; CLONE_STRUCT(SYM_Pi); }
	"psi"		{ NEXTCURSOR; CLONE_STRUCT(SYM_psi); }
	"Psi"		{ NEXTCURSOR; CLONE_STRUCT(SYM_Psi); }
	"rho"		{ NEXTCURSOR; CLONE_STRUCT(SYM_rho); }
	"sigma"		{ NEXTCURSOR; CLONE_STRUCT(SYM_sigma); }
	"Sigma"		{ NEXTCURSOR; CLONE_STRUCT(SYM_Sigma); }
	"tau"		{ NEXTCURSOR; CLONE_STRUCT(SYM_tau); }
	"theta"		{ NEXTCURSOR; CLONE_STRUCT(SYM_theta); }
	"varthetaut"	{ NEXTCURSOR; CLONE_STRUCT(SYM_varthetaut); }
	"Theta"		{ NEXTCURSOR; CLONE_STRUCT(SYM_Theta); }
	"upsilon"	{ NEXTCURSOR; CLONE_STRUCT(SYM_upsilon); }
	"xi"		{ NEXTCURSOR; CLONE_STRUCT(SYM_xi); }
	"Xi"		{ NEXTCURSOR; CLONE_STRUCT(SYM_Xi); }
	"zeta"		{ NEXTCURSOR; CLONE_STRUCT(SYM_zeta); }
	"+"		{ NEXTCURSOR; CLONE_STRUCT(SYM_plus); }
	"-"		{ NEXTCURSOR; CLONE_STRUCT(SYM_minus); }
	"*"		{ NEXTCURSOR; CLONE_STRUCT(SYM_cdot); }
	"**"		{ NEXTCURSOR; CLONE_STRUCT(SYM_ast); }
	"***"		{ NEXTCURSOR; CLONE_STRUCT(SYM_star); }
	"//"		{ NEXTCURSOR; CLONE_STRUCT(SYM_slash); }
	"\\\\"		{ NEXTCURSOR; CLONE_STRUCT(SYM_backslash); }
	"setminus"	{ NEXTCURSOR; CLONE_STRUCT(SYM_setminus); }
	"xx"		{ NEXTCURSOR; CLONE_STRUCT(SYM_times); }
	"-:"		{ NEXTCURSOR; CLONE_STRUCT(SYM_div); }
	"divide"	{ NEXTCURSOR; CLONE_STRUCT(SYM_divide); }
	"@"		{ NEXTCURSOR; CLONE_STRUCT(SYM_circ); }
	"o+"		{ NEXTCURSOR; CLONE_STRUCT(SYM_oplus); }
	"ox"		{ NEXTCURSOR; CLONE_STRUCT(SYM_otimes); }
	"o."		{ NEXTCURSOR; CLONE_STRUCT(SYM_odot); }
	"sum"		{ NEXTCURSOR; CLONE_STRUCT(SYM_sum); }
	"prod"		{ NEXTCURSOR; CLONE_STRUCT(SYM_prod); }
	"^^"		{ NEXTCURSOR; CLONE_STRUCT(SYM_wedge); }
	"^^^"		{ NEXTCURSOR; CLONE_STRUCT(SYM_bigwedge); }
	"vv"		{ NEXTCURSOR; CLONE_STRUCT(SYM_vee); }
	"vvv"		{ NEXTCURSOR; CLONE_STRUCT(SYM_bigvee); }
	"nn"		{ NEXTCURSOR; CLONE_STRUCT(SYM_cap); }
	"nnn"		{ NEXTCURSOR; CLONE_STRUCT(SYM_bigcap); }
	"uu"		{ NEXTCURSOR; CLONE_STRUCT(SYM_cup); }
	"uuu"		{ NEXTCURSOR; CLONE_STRUCT(SYM_bigcup); }
	"="		{ NEXTCURSOR; CLONE_STRUCT(SYM_eq); }
	"!="		{ NEXTCURSOR; CLONE_STRUCT(SYM_ne); }
	":="		{ NEXTCURSOR; CLONE_STRUCT(SYM_def); }
	"lt"		{ NEXTCURSOR; CLONE_STRUCT(SYM_lt); }
	"<="		{ NEXTCURSOR; CLONE_STRUCT(SYM_le); }
	"lt="		{ NEXTCURSOR; CLONE_STRUCT(SYM_leq); }
	"gt"		{ NEXTCURSOR; CLONE_STRUCT(SYM_gt); }
	">="		{ NEXTCURSOR; CLONE_STRUCT(SYM_ge); }
	"gt="		{ NEXTCURSOR; CLONE_STRUCT(SYM_geq); }
	"-<"		{ NEXTCURSOR; CLONE_STRUCT(SYM_prec); }
	"-lt"		{ NEXTCURSOR; CLONE_STRUCT(SYM_lt2); }
	">-"		{ NEXTCURSOR; CLONE_STRUCT(SYM_succ); }
	"-<="		{ NEXTCURSOR; CLONE_STRUCT(SYM_preceq); }
	">-="		{ NEXTCURSOR; CLONE_STRUCT(SYM_succeq); }
	"in"		{ NEXTCURSOR; CLONE_STRUCT(SYM_in); }
	"!in"		{ NEXTCURSOR; CLONE_STRUCT(SYM_notin); }
	"sub"		{ NEXTCURSOR; CLONE_STRUCT(SYM_subset); }
	"sup"		{ NEXTCURSOR; CLONE_STRUCT(SYM_supset); }
	"sube"		{ NEXTCURSOR; CLONE_STRUCT(SYM_subseteq); }
	"supe"		{ NEXTCURSOR; CLONE_STRUCT(SYM_supseteq); }
	"-="		{ NEXTCURSOR; CLONE_STRUCT(SYM_equiv); }
	"~="		{ NEXTCURSOR; CLONE_STRUCT(SYM_cong); }
	"~~"		{ NEXTCURSOR; CLONE_STRUCT(SYM_approx); }
	"prop"		{ NEXTCURSOR; CLONE_STRUCT(SYM_propto); }
	"and"		{ NEXTCURSOR; CLONE_STRUCT(SYM_and); }
	"or"		{ NEXTCURSOR; CLONE_STRUCT(SYM_or); }
	"not"		{ NEXTCURSOR; CLONE_STRUCT(SYM_neg); }
	"=>"		{ NEXTCURSOR; CLONE_STRUCT(SYM_implies); }
	"if"		{ NEXTCURSOR; CLONE_STRUCT(SYM_if); }
	"<=>"		{ NEXTCURSOR; CLONE_STRUCT(SYM_iff); }
	"AA"		{ NEXTCURSOR; CLONE_STRUCT(SYM_forall); }
	"EE"		{ NEXTCURSOR; CLONE_STRUCT(SYM_exists); }
	"_|_"		{ NEXTCURSOR; CLONE_STRUCT(SYM_bot); }
	"TT"		{ NEXTCURSOR; CLONE_STRUCT(SYM_top); }
	"|--"		{ NEXTCURSOR; CLONE_STRUCT(SYM_vdash); }
	"|=="		{ NEXTCURSOR; CLONE_STRUCT(SYM_models); }
	"(" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_lparen); }
	")" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_rparen); }
	"[" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_lbracket); }
	"]" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_rbracket); }
	"{" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_lcurly); }
	"}" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_rcurly); }
	"|" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_pipe); }
	"||"		{ NEXTCURSOR; CLONE_STRUCT(SYM_doublepipe); }
	"(:" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_lparencolon); }
	":)" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_rparencolon); }
	"<<" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_langle); }
	">>" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_rangle); }
	"{:" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_linvis); }
	":}" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_rinvis); }
	"int"		{ NEXTCURSOR; CLONE_STRUCT(SYM_int); }
	"dx"		{ NEXTCURSOR; CLONE_STRUCT(SYM_dx); }
	"dy"		{ NEXTCURSOR; CLONE_STRUCT(SYM_dy); }
	"dz"		{ NEXTCURSOR; CLONE_STRUCT(SYM_dz); }
	"dt"		{ NEXTCURSOR; CLONE_STRUCT(SYM_dt); }
	"oint"		{ NEXTCURSOR; CLONE_STRUCT(SYM_oint); }
	"del"		{ NEXTCURSOR; CLONE_STRUCT(SYM_partial); }
	"grad"		{ NEXTCURSOR; CLONE_STRUCT(SYM_nabla); }
	"+-"		{ NEXTCURSOR; CLONE_STRUCT(SYM_pm); }
	"..."		{ NEXTCURSOR; CLONE_STRUCT(SYM_emptyset); }
	":."		{ NEXTCURSOR; CLONE_STRUCT(SYM_infty); }
	"/_"		{ NEXTCURSOR; CLONE_STRUCT(SYM_aleph); }
	"/_\\"		{ NEXTCURSOR; CLONE_STRUCT(SYM_ldots); }
	"'"		{ NEXTCURSOR; CLONE_STRUCT(SYM_therefore); }
	"tilde"		{ NEXTCURSOR; CLONE_STRUCT(SYM_angle); }
	"\\ "		{ NEXTCURSOR; CLONE_STRUCT(SYM_triangle); }
	"quad"		{ NEXTCURSOR; CLONE_STRUCT(SYM_prime); }
	"qquad"		{ NEXTCURSOR; CLONE_STRUCT(SYM_tilde); }
	"cdots"		{ NEXTCURSOR; CLONE_STRUCT(SYM_double_backslash); }
	"vdots"		{ NEXTCURSOR; CLONE_STRUCT(SYM_quad); }
	"ddots"		{ NEXTCURSOR; CLONE_STRUCT(SYM_qquad); }
	"diamond"	{ NEXTCURSOR; CLONE_STRUCT(SYM_cdots); }
	"square"	{ NEXTCURSOR; CLONE_STRUCT(SYM_vdots); }
	"|__"		{ NEXTCURSOR; CLONE_STRUCT(SYM_ddots); }
	"__|"		{ NEXTCURSOR; CLONE_STRUCT(SYM_diamond); }
	"|~"		{ NEXTCURSOR; CLONE_STRUCT(SYM_squar); }
	"~|"		{ NEXTCURSOR; CLONE_STRUCT(SYM_lfloor); }
	"O/"		{ NEXTCURSOR; CLONE_STRUCT(SYM_rfloor); }
	"oo"		{ NEXTCURSOR; CLONE_STRUCT(SYM_lceiling); }
	"aleph"		{ NEXTCURSOR; CLONE_STRUCT(SYM_rceiling); }
	"CC"		{ NEXTCURSOR; CLONE_STRUCT(SYM_complex); }
	"NN"		{ NEXTCURSOR; CLONE_STRUCT(SYM_natural); }
	"QQ"		{ NEXTCURSOR; CLONE_STRUCT(SYM_rational); }
	"RR"		{ NEXTCURSOR; CLONE_STRUCT(SYM_real); }
	"ZZ"		{ NEXTCURSOR; CLONE_STRUCT(SYM_integer); }
	"f"		{ NEXTCURSOR; CLONE_STRUCT(SYM_f); }
	"g"		{ NEXTCURSOR; CLONE_STRUCT(SYM_g); }
	"lim"		{ NEXTCURSOR; CLONE_STRUCT(SYM_lim); }
	"Lim"		{ NEXTCURSOR; CLONE_STRUCT(SYM_Lim); }
	"sin" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_sin); }
	"cos" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_cos); }
	"tan" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_tan); }
	"sinh" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_sinh); }
	"cosh" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_cosh); }
	"tanh" 		{ NEXTCURSOR; CLONE_STRUCT(SYM_tanh); }
	"cot"		{ NEXTCURSOR; CLONE_STRUCT(SYM_cot); }
	"sec"		{ NEXTCURSOR; CLONE_STRUCT(SYM_sec); }
	"csc"		{ NEXTCURSOR; CLONE_STRUCT(SYM_csc); }
	"log"		{ NEXTCURSOR; CLONE_STRUCT(SYM_log); }
	"ln"		{ NEXTCURSOR; CLONE_STRUCT(SYM_ln); }
	"det"		{ NEXTCURSOR; CLONE_STRUCT(SYM_det); }
	"dim"		{ NEXTCURSOR; CLONE_STRUCT(SYM_dim); }
	"mod"		{ NEXTCURSOR; CLONE_STRUCT(SYM_mod); }
	"gcd"		{ NEXTCURSOR; CLONE_STRUCT(SYM_gcd); }
	"lcm"		{ NEXTCURSOR; CLONE_STRUCT(SYM_lcm); }
	"lub"		{ NEXTCURSOR; CLONE_STRUCT(SYM_lub); }
	"glb"		{ NEXTCURSOR; CLONE_STRUCT(SYM_glb); }
	"min"		{ NEXTCURSOR; CLONE_STRUCT(SYM_min); }
	"max"		{ NEXTCURSOR; CLONE_STRUCT(SYM_max); }
	"hat"		{ NEXTCURSOR; CLONE_STRUCT(SYM_hat); }
	"bar"		{ NEXTCURSOR; CLONE_STRUCT(SYM_bar); }
	"ul"		{ NEXTCURSOR; CLONE_STRUCT(SYM_ul); }
	"vec"		{ NEXTCURSOR; CLONE_STRUCT(SYM_vec); }
	"dot"		{ NEXTCURSOR; CLONE_STRUCT(SYM_dot); }
	"ddot"		{ NEXTCURSOR; CLONE_STRUCT(SYM_ddot); }
	"sqrt"		{ NEXTCURSOR; CLONE_STRUCT(SYM_sqrt); }
	"text"		{ NEXTCURSOR; CLONE_STRUCT(SYM_text); }
	"frac"		{ NEXTCURSOR; CLONE_STRUCT(SYM_frac); }
	"root"		{ NEXTCURSOR; CLONE_STRUCT(SYM_root); }
	"stackrel"	{ NEXTCURSOR; CLONE_STRUCT(SYM_stackrel); }
	"/"		{ NEXTCURSOR; CLONE_STRUCT(SYM_fracdiv); }
	"_"		{ NEXTCURSOR; CLONE_STRUCT(SYM_sub); }
	"^"		{ NEXTCURSOR; CLONE_STRUCT(SYM_sup); }
	[ \t]+		{ NEXTCURSOR; return &syms[SYM_whitespace]; }
	[A-Za-z]+	{ NEXTCURSOR; struct sym *a = malloc(sizeof(struct sym)); a->type=IDENTIFIER; a->str=strndup(t, YYCURSOR - t); return a; }
	"\000"		{ NEXTCURSOR; return &syms[SYM_EOL]; }
	[^]		{ NEXTCURSOR; return &syms[SYM_EOL]; }

*/
}
