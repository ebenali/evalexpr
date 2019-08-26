/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_expr.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:11:53 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/25 20:51:42 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_EXPR_H
# define EVAL_EXPR_H

typedef struct	s_rdp {
	int			result;
	_Bool		err;
}				t_rdp;

/*
**   Ugly state wrapper to get around 25 line limitation. terrible.
*/

struct			s_uns {
	t_rdp		retv;
	t_token		*op1;
	t_token		*op;
	t_rdp		ev_op2;
};

/*
** --------------------
**  main.c
*/
extern	t_rdp	rdp_paren(t_tokctx *ctx, signed prec_lvl);
extern	t_rdp	rdp_unparen(t_tokctx *ctx, signed prec_lvl);

/*
** -----------------
** main2.c
*/

extern _Bool	rdp_uns_init(t_tokctx *ctx, struct s_uns *us);
extern int		eval_op(int op1, char op, int op2);

#endif

/*
** vim: ts=4 sw=4
*/
