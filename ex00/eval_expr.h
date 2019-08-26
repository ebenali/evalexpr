/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_expr.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:11:53 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/25 18:22:47 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_EXPR_H
# define EVAL_EXPR_H

typedef struct	s_rdp {
	int			result;
	_Bool		err;
	char		*errmsg;
}				t_rdp;

static t_rdp	rdp_paren(t_tokctx *ctx, signed prec_lvl);
static t_rdp	rdp_unparen(t_tokctx *ctx, signed prec_lvl);

#endif

/*
** vim: ts=4 sw=4
*/
