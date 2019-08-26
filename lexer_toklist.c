/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_toklist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:41:54 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/25 18:10:36 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_toklist	*toklist_init(t_tokctx *ctx, t_token const *tok)
{
	t_toklist *retv;

	retv = (t_toklist*)malloc(sizeof(t_toklist));
	retv->ctx = ctx;
	retv->tok = token_clone(tok);
	retv->next = NULL;
	return (retv);
}

void		toklist_free(t_toklist *tlist)
{
	if (tlist && tlist->next)
		toklist_free(tlist->next);
	if (tlist && tlist->tok)
		token_free(tlist->tok);
	if (tlist)
		free(tlist);
}

/*
** -------
** Returns ptr to cloned token
*/

t_token		*toklist_enqueue(t_toklist *tlst, t_token const *tok)
{
	if (!(tlst && tok))
		return (NULL);
	while (tlst->next != NULL)
		tlst = tlst->next;
	tlst->next = toklist_init(tlst->ctx, tok);
	return (tlst->next->tok);
}

t_token		*toklist_dequeue(t_toklist *tlist)
{
	if (tlist && tlist->ctx->tlist_cursor)
	{
		tlist->ctx->tlist_cursor = tlist->ctx->tlist_cursor->next;
		return (tlist->ctx->tlist_cursor ? tlist->ctx->tlist_cursor->tok
				: NULL);
	}
	return (NULL);
}

/*
**  ------
**  Return pointer to tok un-dequeued
*/

t_token		*toklist_undequeue(t_toklist *tlist, t_token *tok)
{
	t_toklist	*tlp;

	if (tlist == NULL)
		return (NULL);
	tlp = tlist->ctx->tlist_head;
	while (tlp->next != NULL && tlp->next->tok != tok)
		tlp = tlp->next;
	if (tlp->next == NULL)
		return (NULL);
	tlp->ctx->tlist_cursor = tlp;
	return (tok);
}

/*
** vim: ts=4 sw=4
*/
