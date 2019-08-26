/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:58:52 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/25 18:21:17 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libc.h"
#include "lexer.h"

#undef ARITH_PARSE

#include "arithmetic.h"

static _Bool	lex_nbr(const char **str, char prevc, intmax_t *num_val)
{
	char		*eptr;

	eptr = NULL;
	if (ft_strchr(g_digset, **str) || (ft_strchr("+-", **str) &&
			(prevc == '\0' || prevc == '(' || ft_strchr(g_opset, prevc))))
	{
		*num_val = ft_strtoimax(*str, &eptr, 10);
		if (eptr == *str)
			return (false);
		else
			*str = eptr - 1;
		return (true);
	}
	return (false);
}

/*
**  To build a general purpose lexer, parametrize token types and recognition
**  rules instead of the hardcoded integer arithmetic here.
*/

t_tokctx		*lex(const char *str)
{
	t_tokctx	*ctx;
	char		prevc;
	intmax_t	num_val;
	t_token		*tmptok;

	if (!(str && (ctx = tokctx_init())))
		return (NULL);
	prevc = '\0';
	while (*str != '\0')
	{
		if (lex_nbr(&str, prevc, &num_val))
			tmptok = token_init(TOK_NUM, &num_val);
		else if (ft_strchr(g_opset, *str))
			tmptok = token_init(TOK_OP, (void*)str);
		else if (ft_strchr("()", *str))
			tmptok = token_init(*str == '(' ? TOK_LPAR : TOK_RPAR, NULL);
		else
			break ;
		tokctx_enqueue(ctx, tmptok);
		token_free(tmptok);
		prevc = *str++;
	}
	return (*str != '\0' ? tokctx_free(ctx) : ctx);
}

/*
** vim: ts=4 sw=4
*/
