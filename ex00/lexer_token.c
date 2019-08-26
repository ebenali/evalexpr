/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:41:12 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/25 17:51:40 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token			*token_init(t_toktype type, void *val)
{
	t_token *retv;

	retv = (t_token*)malloc(sizeof(t_token));
	retv->type = type;
	if (type == TOK_NUM)
		retv->val.num = *(intmax_t*)val;
	if (type == TOK_OP)
		retv->val.op = *(char*)val;
	return (retv);
}

void			token_free(t_token *tok)
{
	if (tok)
		free(tok);
}

t_token			*token_clone(t_token const *tok)
{
	t_token *retv;

	if (tok == NULL)
		return (NULL);
	retv = (t_token*)malloc(sizeof(t_token));
	ft_memcpy(retv, tok, sizeof(t_token));
	return (retv);
}

/*
** vim: ts=4 sw=4
*/
