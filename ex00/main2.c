/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 20:44:04 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/25 20:52:59 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Ugly workaround for norminette. Returns true if processing should continue
** normally or whether the value at ev_op2 should be returned instead.
*/

#include <stdbool.h>

#include "lexer.h"
#define ARITH_PARSE
#include "arithmetic.h"
#include "eval_expr.h"

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

_Bool			rdp_uns_init(t_tokctx *ctx, struct s_uns *us)
{
	if (!(us->op1 = tokctx_dequeue(ctx)) || !(us->op1->type == TOK_NUM
				|| us->op1->type == TOK_LPAR))
	{
		us->ev_op2.err = true;
		return (false);
	}
	if (us->op1->type == TOK_LPAR)
	{
		us->ev_op2 = rdp_paren(ctx, -1);
		return (false);
	}
	us->retv.result = us->op1->val.num;
	us->retv.err = false;
	return (true);
}
