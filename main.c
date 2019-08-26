/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 08:09:54 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/25 20:55:26 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "libc.h"
#include "lexer.h"
#include "eval_expr.h"

#define ARITH_PARSE
#include "arithmetic.h"

/*
**  Recursive descent evaluator part #2
**  evaluates de-parenthesized expression through ctx's token stream routines
**  calls rdp_paren() for recursive application
*/
t_rdp			rdp_unparen(t_tokctx *ctx, signed prec_lvl)
{
	struct s_uns	us;

	if (rdp_uns_init(ctx, &us) == false)
		return (us.ev_op2);
	while (true)
	{
		if ((us.op = tokctx_dequeue(ctx)) == NULL || us.op->type != TOK_OP)
		{
			if (us.op != NULL && us.op->type != TOK_RPAR)
				return (t_rdp){ .err=true };
			if (us.op && us.op->type == TOK_RPAR)
				tokctx_undequeue(ctx, us.op);
			break ;
		}
		if (OPREC(us.op->val.op) <= prec_lvl)
		{
			tokctx_undequeue(ctx, us.op);
			return (us.retv);
		}
		if ((us.ev_op2 = rdp_paren(ctx, OPREC(us.op->val.op))).err == true)
			return (us.ev_op2);
		us.retv.result = eval_op(us.retv.result,
				us.op->val.op, us.ev_op2.result);
	}
	return (us.retv);
}

/*
** Recursive descent evaluator part #1
*/
t_rdp			rdp_paren(t_tokctx *ctx, signed prec_lvl)
{
	t_token	*tok_start;
	t_token	*tok_end;
	t_token	*tok_reduction;
	t_rdp	retv;

	if ((tok_start = tokctx_dequeue(ctx)) == NULL)
		return (t_rdp){.result=0, .err=true};
	if (tok_start->type == TOK_LPAR)
	{
		if ((retv = rdp_paren(ctx, -1)).err)
			return (retv);
		if (!(tok_end = tokctx_dequeue(ctx)) || tok_end->type != TOK_RPAR)
			return ((t_rdp){.err = true});
		tok_reduction = token_init(TOK_NUM, &retv.result);
		tok_start = tokctx_reduce(ctx, tok_start, tok_end, tok_reduction);
		token_free(tok_reduction);
		tokctx_undequeue(ctx, tok_start);
		return (rdp_unparen(ctx, prec_lvl));
	}
	tokctx_undequeue(ctx, tok_start);
	return (rdp_unparen(ctx, prec_lvl));
}

/*
**  Tokenize and initiate recursive descent evaluation
*/
static int		eval(const char *tidy)
{
	t_tokctx	*ctx;
	t_rdp		rdp;

	if ((ctx = lex(tidy)) == NULL)
		return (0);
	if (ctx->tlist_head->next != NULL)
	{
		rdp = rdp_paren(ctx, -1);
		if (rdp.err)
		{
			tokctx_free(ctx);
			return (0);
		}
	}
	tokctx_free(ctx);
	return (rdp.result);
}

/*
**  tidy up input and pass to eval()
*/
int				eval_expr(char *str)
{
	char	*tok;
	char	*dup;
	char	*tidy;
	int		retv;

	if (str && ft_strlen(str) != 0)
	{
		dup = ft_strdup(str);
		tidy = (char*)malloc(ft_strlen(str) + 1);
		*tidy = '\0';
		tok = NULL;
		while ((tok = ft_strtok(tok == NULL ? dup : NULL, " \t\n")))
			ft_strlcat(tidy, tok, ft_strlen(str) + 1);
		free(dup);
		retv = eval(tidy);
		free(tidy);
	}
	else
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
