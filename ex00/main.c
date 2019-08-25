/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 08:09:54 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/25 13:49:03 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "libc.h"
#include "lexer.h"
#include "arithmetic.h"

const char	*token_tostring(t_token *tok)
{
	static char	buf[64];
	char buf2[32];

	if (tok == NULL)
		ft_strcpy(buf, "<NONE>");
	else {
		if (tok->type == TOK_NUM)
			ft_snprintf(buf2, sizeof(buf2), "%lli", tok->val.num);
		else if (tok->type == TOK_OP)
			ft_snprintf(buf2, sizeof(buf2), "\'%c\'", tok->val.op);
		else
			ft_strcpy(buf2, "NONE");
		ft_snprintf(buf, sizeof(buf), "<type=%s,val=%s>",
				tok->type == TOK_NUM ? "NUM"
				: tok->type == TOK_OP ? "OP"
				: tok->type == TOK_LPAR ? "LPAR"
				: "RPAR",
				buf2);
	}
	return (buf);
}

typedef struct	s_rdp {
	int			result;
	_Bool		err;
	char		*errmsg;
}				t_rdp;

static t_rdp rdp_paren(t_tokctx *ctx, signed prec_lvl);
static t_rdp	rdp_unparen(t_tokctx *ctx, signed prec_lvl);

int				eval_op(int op1, char op, int op2)
{
	if (op == ADD)
		return (op1 + op2);
	else if (op == SUB)
		return (op1 - op2);
	else if (op == MUL)
		return (op1 * op2);
	else if (op == DIV)
		return (op1 / op2);
	else if (op == MOD)
		return (op1 % op2);
	return (0);
}

/*
 *  Upon encountering left parens, start a sub-parse with rdp()
 *  Upon enountering right parens, bail out and back up for rdp() to make sure
 *  parens are balanced.
 */
static t_rdp	rdp_unparen(t_tokctx *ctx, signed prec_lvl)
{
	t_rdp		retv;
	t_token		*op1;
	t_token		*op;
	t_token		*op2;
	t_rdp		ev_op2;

	if ((op1 = tokctx_dequeue(ctx)) == NULL || !(op1->type == TOK_NUM || op1->type == TOK_LPAR)) {
		retv.err = true;
		ft_asprintf(&retv.errmsg, "expected numeric or parenthesized operand #1, heave instead token '%s'",
				token_tostring(op1));
		return (retv);
	} else if (op1->type == TOK_LPAR) {
		if ((ev_op2 = rdp_paren(ctx, -1)).err == true)
			return (ev_op2);
		retv.result = ev_op2.result;
	} else
		retv.result = op1->val.num;
	retv.err = false;
	while (true) { // keep going as long as on same or higher precedence or error occurs
		if ((op = tokctx_dequeue(ctx)) == NULL || op->type != TOK_OP) {
			if (op == NULL) // either single numeric operand or computation collapsed into one
				break ;
			if (op->type == TOK_RPAR) {
				tokctx_undequeue(ctx, op); // for rdp_paren()
				break ;
			}
			retv.err = true;
			ft_asprintf(&retv.errmsg, "expected operator, instead got token '%s'",
					token_tostring(op));
			return (retv);
		}
		if (OPREC(op->val.op) < prec_lvl) { // lower precedence encountered, go back to caller
			tokctx_undequeue(ctx, op);
			return (retv);
		} else if (OPREC(op->val.op) > prec_lvl) { // higher precedence, recurse and get result for ourself
			if ((ev_op2 = rdp_paren(ctx, OPREC(op->val.op))).err == true)
				return (ev_op2);
		} else { // same precedence
			if ((op2 = tokctx_dequeue(ctx)) == NULL ||
					!(op2->type == TOK_LPAR || op2->type == TOK_NUM)) {
				retv.err = true;
				ft_asprintf(&retv.errmsg, "expected numeric or parenthesized operand #2"
						", instead got token '%s'", token_tostring(op2));
				return (retv);
			} // op2 != LPAR && op2 != NUM
			// XXX: right-associate or left associate?
			if (op2->type == TOK_LPAR) {
				if ((ev_op2 = rdp_paren(ctx, -1)).err == true) // notice -1: paren level reset
					return (ev_op2);
			} else { // if (op2->type == TOK_NUM)
				ev_op2.result = op2->val.num;
			}
		} // same prec
		retv.result = eval_op(retv.result, op->val.op, ev_op2.result);
	} // while (true)
	return (retv);
}

static t_rdp rdp_paren(t_tokctx *ctx, signed prec_lvl)
{
	t_token	*tok_start;
	t_token	*tok_end;
	t_token	*tok_reduction;
	t_rdp	retv;

	if ((tok_start = tokctx_dequeue(ctx)) == NULL)
		return (t_rdp){.result=0, .err=true, .errmsg=ft_strdup("premature end of expression")};
	if (tok_start->type == TOK_LPAR) { // left parens handled here while right parens by rdp_unparen()
		if ((retv = rdp_paren(ctx, prec_lvl)).err)
			return (retv);
		if ((tok_end = tokctx_dequeue(ctx)) == NULL || tok_end->type != TOK_RPAR) {
			ft_asprintf(&retv.errmsg, "no matching right paren: instead got '%s'", token_tostring(tok_end));
			retv.err = true;
			return (retv);
		}
		tok_reduction = token_init(TOK_NUM, &retv.result);
		tok_start = tokctx_reduce(ctx, tok_start, tok_end, tok_reduction);
		token_free(tok_reduction); // duplicated by reduce()
		tokctx_undequeue(ctx, tok_start); // rewind
		return rdp_unparen(ctx, prec_lvl);
	}
	// else
	tokctx_undequeue(ctx, tok_start);
	return (rdp_unparen(ctx, prec_lvl));
}

/**
 *  Tokenize and initiate recursive descent parse
 */
static int	eval(const char *tidy)
{
	t_tokctx	*ctx;
	t_rdp		rdp;

	if ((ctx = lex(tidy)) == NULL) {
		ft_printf("%s: error: failed to tokenize expression\n", __func__);
		return (0);
	}

	if (ctx->tlist_head->next != NULL) {
		rdp = rdp_paren(ctx, -1);
		if (rdp.err) {
			if (rdp.errmsg != NULL)
			{
				ft_printf("error: malformed arithmetic expression: %s\n", rdp.errmsg);
				free(rdp.errmsg);
			}
			tokctx_free(ctx);
			return (0);
		}
	}

	tokctx_free(ctx);
	return (rdp.result);
}

/**
 *  tidy up input and pass to eval()
 */
int				eval_expr(char *str)
{
	char	*tok;
	char	*dup;
	char	*tidy;
	int		retv;

	if (str && ft_strlen(str) != 0) {
		dup = ft_strdup(str);
		tidy = (char*)malloc(ft_strlen(str) + 1);
		*tidy = '\0';
		tok = NULL;
		while ((tok = ft_strtok(tok == NULL ? dup : NULL, " \t\n"))) {
			ft_strlcat(tidy, tok, ft_strlen(str) + 1);
		}
		free(dup);
		retv = eval(tidy);
		free(tidy);
	} else
		retv = 0;
	return (retv);
}

int				main(int argc, char *argv[])
{
	if (argc > 1)
		ft_printf("%i\n", eval_expr(argv[1]));
	return (0);
}

/*
 ** vim: ts=4 sw=4
 */
