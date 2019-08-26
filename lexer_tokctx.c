/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokctx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:43:48 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/25 18:21:37 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_tokctx			*tokctx_init(void)
{
	t_tokctx	*ctx;

	ctx = (t_tokctx *)malloc(sizeof(*ctx));
	ctx->tlist_head = toklist_init(ctx, NULL);
	ctx->tlist_cursor = ctx->tlist_head;
	return (ctx);
}

void				*tokctx_free(t_tokctx *ctx)
{
	if (ctx)
	{
		if (ctx->tlist_head)
		{
			toklist_free(ctx->tlist_head->next);
			free(ctx->tlist_head);
		}
		free(ctx);
	}
	return (NULL);
}

t_token				*tokctx_enqueue(t_tokctx *ctx, t_token *tok)
{
	if (!(ctx && tok))
		return (NULL);
	return (toklist_enqueue(ctx->tlist_head, tok));
}

t_token				*tokctx_dequeue(t_tokctx *ctx)
{
	if (!ctx)
		return (NULL);
	return (toklist_dequeue(ctx->tlist_head));
}

t_token				*tokctx_undequeue(t_tokctx *ctx, t_token *tok)
{
	if (!(ctx && tok))
		return (NULL);
	return (toklist_undequeue(ctx->tlist_head, tok));
}

/*
** vim: ts=4 sw=4
*/
