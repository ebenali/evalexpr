/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 17:14:18 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/25 18:08:27 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "libc.h"
#include "lexer.h"

t_token		*tokctx_reduce(t_tokctx *ctx, t_token *from, t_token *to,
		t_token *replacement)
{
	t_toklist *tlist;
	t_toklist *tlnxt;

	if (!ctx)
		return (NULL);
	tlist = ctx->tlist_head;
	while (tlist->next && tlist->next->tok != from)
		tlist = tlist->next;
	while (tlist->next && tlist->next->tok != to)
	{
		token_free(tlist->next->tok);
		tlnxt = tlist->next->next;
		free(tlist->next);
		tlist->next = tlnxt;
	}
	if (tlist->next == NULL)
		tlist->next = toklist_init(ctx, replacement);
	else
	{
		tlnxt = tlist->next->next;
		token_free(tlist->next->tok);
		tlist->next->tok = token_clone(replacement);
	}
	return (tlist->next->tok);
}

/*
** vim: ts=4 sw=4
*/
