#include "symtypes.h"

static const struct sym syms[SYM__MAX] = {
	{ IDENTIFIER, "\u03B1" }, /* SYM_alpha */
	{ IDENTIFIER, "\u03B2" }, /* SYM_beta */
	{ IDENTIFIER, "\u03C7" }, /* SYM_chi */
	{ IDENTIFIER, "\u03B4" }, /* SYM_delta */
	{ IDENTIFIER, "\u0394" }, /* SYM_Delta */
	{ IDENTIFIER, "\u03B5" }, /* SYM_epsi */
	{ IDENTIFIER, "\u025B" }, /* SYM_varepsilon */
	{ IDENTIFIER, "\u03B7" }, /* SYM_eta */
	{ IDENTIFIER, "\u03B3" }, /* SYM_gamma */
	{ IDENTIFIER, "\u0393" }, /* SYM_Gamma */
	{ IDENTIFIER, "\u03B9" }, /* SYM_iota */
	{ IDENTIFIER, "\u03BA" }, /* SYM_kappa */
	{ IDENTIFIER, "\u03BB" }, /* SYM_lambda */
	{ IDENTIFIER, "\u039B" }, /* SYM_Lambda */
	{ IDENTIFIER, "\u03BB" }, /* SYM_lamda */
	{ IDENTIFIER, "\u039B" }, /* SYM_Lamda */
	{ IDENTIFIER, "\u03BC" }, /* SYM_mu */
	{ IDENTIFIER, "\u03BD" }, /* SYM_nu */
	{ IDENTIFIER, "\u03C9" }, /* SYM_omega */
	{ IDENTIFIER, "\u03A9" }, /* SYM_Omega */
	{ IDENTIFIER, "\u03D5" }, /* SYM_phi */
	{ IDENTIFIER, "\u03C6" }, /* SYM_varphi */
	{ IDENTIFIER, "\u03A6" }, /* SYM_Phi */
	{ IDENTIFIER, "\u03C0" }, /* SYM_pi */
	{ IDENTIFIER, "\u03A0" }, /* SYM_Pi */
	{ IDENTIFIER, "\u03C8" }, /* SYM_psi */
	{ IDENTIFIER, "\u03A8" }, /* SYM_Psi */
	{ IDENTIFIER, "\u03C1" }, /* SYM_rho */
	{ IDENTIFIER, "\u03C3" }, /* SYM_sigma */
	{ IDENTIFIER, "\u03A3" }, /* SYM_Sigma */
	{ IDENTIFIER, "\u03C4" }, /* SYM_tau */
	{ IDENTIFIER, "\u03B8" }, /* SYM_theta */
	{ IDENTIFIER, "\u03D1" }, /* SYM_varthetaut */
	{ IDENTIFIER, "\u0398" }, /* SYM_Theta */
	{ IDENTIFIER, "\u03C5" }, /* SYM_upsilon */
	{ IDENTIFIER, "\u03BE" }, /* SYM_xi */
	{ IDENTIFIER, "\u039E" }, /* SYM_Xi */
	{ IDENTIFIER, "\u03B6" },  /* SYM_zeta */
	{ OPERATOR, "+" },   /* SYM_plus */
	{ OPERATOR, "\u2212" },  /* SYM_minus */
	{ OPERATOR, "\u22C5" },   /* SYM_cdot */
	{ OPERATOR, "\u2217" },  /* SYM_ast */
	{ OPERATOR, "\u22C6" },  /* SYM_star */
	{ OPERATOR, "/" },  /* SYM_slash */
	{ OPERATOR, "\\" },  /* SYM_backslash */
	{ OPERATOR, "\\" },  /* SYM_setminus */
	{ OPERATOR, "\u00D7" },  /* SYM_times */
	{ OPERATOR, "\u00F7" },  /* SYM_div */
	{ OPERATOR, "-:" },  /* SYM_divide */
	{ OPERATOR, "\u2218" },  /* SYM_circ */
	{ OPERATOR, "\u2295" },  /* SYM_oplus */
	{ OPERATOR, "\u2297" },  /* SYM_otimes */
	{ OPERATOR, "\u2299" },  /* SYM_odot */
	{ OPERATOR, "\u2211", TOK_underover },  /* SYM_sum */
	{ OPERATOR, "\u220F", TOK_underover },  /* SYM_prod */
	{ OPERATOR, "\u2227" },  /* SYM_wedge */
	{ OPERATOR, "\u22C0", TOK_underover },  /* SYM_bigwedge */
	{ OPERATOR, "\u2228" },  /* SYM_vee */
	{ OPERATOR, "\u22C1", TOK_underover },  /* SYM_bigvee */
	{ OPERATOR, "\u2229" },  /* SYM_cap */
	{ OPERATOR, "\u22C2", TOK_underover },  /* SYM_bigcap */
	{ OPERATOR, "\u222A" },  /* SYM_cup */
	{ OPERATOR, "\u22C3", TOK_underover },  /* SYM_bigcup */
	{ OPERATOR, "=" }, /* SYM_eq */
	{ OPERATOR, "\u2260" }, /* SYM_ne */
	{ OPERATOR, ":=" }, /* SYM_def */
	{ OPERATOR, "<" }, /* SYM_lt */
	{ OPERATOR, "\u2264" }, /* SYM_le */
	{ OPERATOR, "\u2264" }, /* SYM_leq */
	{ OPERATOR, ">" }, /* SYM_gt */
	{ OPERATOR, "\u2265" }, /* SYM_ge */
	{ OPERATOR, "\u2265" }, /* SYM_geq */
	{ OPERATOR, "\u227A" }, /* SYM_prec */
	{ OPERATOR, "\u227A" }, /* SYM_lt2 */
	{ OPERATOR, "\u227B" }, /* SYM_succ */
	{ OPERATOR, "\u2AAF" }, /* SYM_preceq */
	{ OPERATOR, "\u2AB0" }, /* SYM_succeq */
	{ OPERATOR, "\u2208" }, /* SYM_in */
	{ OPERATOR, "\u2209" }, /* SYM_notin */
	{ OPERATOR, "\u2282" }, /* SYM_subset */
	{ OPERATOR, "\u2283" }, /* SYM_supset */
	{ OPERATOR, "\u2286" }, /* SYM_subseteq */
	{ OPERATOR, "\u2287" }, /* SYM_supseteq */
	{ OPERATOR, "\u2261" }, /* SYM_equiv */
	{ OPERATOR, "\u2245" }, /* SYM_cong */
	{ OPERATOR, "\u2248" }, /* SYM_approx */
	{ OPERATOR, "\u221D" }, /* SYM_propto */
	{ TEXT, "and" }, /* SYM_and */
	{ TEXT, "or" }, /* SYM_or */
	{ OPERATOR, "\u00AC" }, /* SYM_neg */
	{ OPERATOR, "\u21D2" }, /* SYM_implies */
	{ OPERATOR, "if" }, /* SYM_if */
	{ OPERATOR, "\u21D4" }, /* SYM_iff */
	{ OPERATOR, "\u2200" }, /* SYM_forall */
	{ OPERATOR, "\u2203" }, /* SYM_exists */
	{ OPERATOR, "\u22A5" }, /* SYM_bot */
	{ OPERATOR, "\u22A4" }, /* SYM_top */
	{ OPERATOR, "\u22A2" }, /* SYM_vdash */
	{ OPERATOR, "\u22A8" }, /* SYM_models */
	{ LEFT, "(" }, /* SYM_lparen */
	{ RIGHT, ")" }, /* SYM_rparen */
	{ LEFT, "[" }, /* SYM_lbracket */
	{ RIGHT, "]" }, /* SYM_rbracket */
	{ LEFT, "{" }, /* SYM_lcurly */
	{ RIGHT, "}" }, /* SYM_rcurly */
	{ LEFT, "|" }, /* SYM_pipe */
	{ RIGHT, "||" }, /* SYM_doublepipe */
	{ LEFT, "\u2329" }, /* SYM_lparencolon */
	{ RIGHT, "\u232A" }, /* SYM_rparencolon */
	{ LEFT, "\u2329" }, /* SYM_langle */
	{ RIGHT, "\u232A" }, /* SYM_rangle */
	{ LEFT, "" }, /* SYM_linvis */
	{ RIGHT, "" }, /* SYM_rinvis */
	{ OPERATOR, "\u222B" }, /* SYM_int */
	{ IDENTIFIER, "dx" }, /* SYM_dx */
	{ IDENTIFIER, "dy" }, /* SYM_dy */
	{ IDENTIFIER, "dz" }, /* SYM_dz */
	{ IDENTIFIER, "dt" }, /* SYM_dt */
	{ OPERATOR, "\u222E" }, /* SYM_oint */
	{ OPERATOR, "\u2202" }, /* SYM_partial */
	{ OPERATOR, "\u2207" }, /* SYM_nabla */
	{ OPERATOR, "\u00B1" }, /* SYM_pm */
	{ OPERATOR, "\u2205" }, /* SYM_emptyset */
	{ OPERATOR, "\u221E" }, /* SYM_infty */
	{ OPERATOR, "\u2135" }, /* SYM_aleph */
	{ OPERATOR, "..." }, /* SYM_ldots */
	{ OPERATOR, "\u2234" }, /* SYM_therefore */
	{ OPERATOR, "\u2220" }, /* SYM_angle */
	{ OPERATOR, "\u25B3" }, /* SYM_triangle */
	{ OPERATOR, "\u2032" }, /* SYM_prime */
	{ OPERATOR, "~" }, /* SYM_tilde */
	{ OPERATOR, "\u00A0" }, /* SYM_double_backslash */
	{ OPERATOR, "\u00A0\u00A0" }, /* SYM_quad */
	{ OPERATOR, "\u00A0\u00A0\u00A0\u00A0" }, /* SYM_qquad */
	{ OPERATOR, "\u22EF" }, /* SYM_cdots */
	{ OPERATOR, "\u22EE" }, /* SYM_vdots */
	{ OPERATOR, "\u22F1" }, /* SYM_ddots */
	{ OPERATOR, "\u22C4" }, /* SYM_diamond */
	{ OPERATOR, "\u25A1" }, /* SYM_squar */
	{ OPERATOR, "\u230A" }, /* SYM_lfloor */
	{ OPERATOR, "\u230B" }, /* SYM_rfloor */
	{ OPERATOR, "\u2308" }, /* SYM_lceiling */
	{ OPERATOR, "\u2309" }, /* SYM_rceiling */
	{ OPERATOR, "\u2102" }, /* SYM_complex */
	{ OPERATOR, "\u2115" }, /* SYM_natural */
	{ OPERATOR, "\u211A" }, /* SYM_rational */
	{ OPERATOR, "\u211D" }, /* SYM_real */
	{ OPERATOR, "\u2124" }, /* SYM_integer */
	{ IDENTIFIER, "f" }, /* SYM_f */
	{ IDENTIFIER, "g" }, /* SYM_g */
	{ OPERATOR, "lim", TOK_underover }, /* SYM_lim */
	{ OPERATOR, "Lim", TOK_underover }, /* SYM_Lim */
	{ OPERATOR, "sin" }, /* SYM_sin */
	{ OPERATOR, "cos" }, /* SYM_cos */
	{ OPERATOR, "tan" }, /* SYM_tan */
	{ OPERATOR, "sinh" }, /* SYM_sinh */
	{ OPERATOR, "cosh" }, /* SYM_cosh */
	{ OPERATOR, "tanh" }, /* SYM_tanh */
	{ OPERATOR, "cot" }, /* SYM_cot */
	{ OPERATOR, "sec" }, /* SYM_sec */
	{ OPERATOR, "csc" }, /* SYM_csc */
	{ OPERATOR, "log" }, /* SYM_log */
	{ OPERATOR, "ln" }, /* SYM_ln */
	{ OPERATOR, "det" }, /* SYM_det */
	{ OPERATOR, "dim" }, /* SYM_dim */
	{ OPERATOR, "mod" }, /* SYM_mod */
	{ OPERATOR, "gcd" }, /* SYM_gcd */
	{ OPERATOR, "lcm" }, /* SYM_lcm */
	{ OPERATOR, "lub" }, /* SYM_lub */
	{ OPERATOR, "glb" }, /* SYM_glb */
	{ OPERATOR, "min", TOK_underover }, /* SYM_min */
	{ OPERATOR, "max", TOK_underover }, /* SYM_max */
	{ ACCENT, "&#x005E;", TOK_over }, /* SYM_hat */
	{ ACCENT, "&#x00AF;", TOK_over }, /* SYM_bar */
	{ ACCENT, "_", TOK_under }, /* SYM_ul */
	{ ACCENT, "&#x2192;", TOK_over }, /* SYM_vec */
	{ ACCENT, ".", TOK_over }, /* SYM_dot */
	{ ACCENT, "..", TOK_over }, /* SYM_ddot */
	/* arrows */
	{ UNARY, "sqrt" }, /* SYM_sqrt */
	{ UNARY, "text" }, /* SYM_text */
	{ BINARY, "frac" }, /* SYM_frac */
	{ BINARY, "root" }, /* SYM_root */
	{ BINARY, "over" }, /* SYM_stackrel */
	{ DIV, 0 }, /* SYM_fracdiv */
	{ SUB, 0 }, /* SYM_sub */
	{ SUP, 0 }, /* SYM_sup */
	{ 0, 0 }, /* SYM_EOL */
	{ 0, 0 } /* SYM_ignore */
};
