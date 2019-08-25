/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 17:14:18 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/25 14:05:05 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "libc.h"
#include "lexer.h"

/*
** Specialized lexer providing an interface to a token FIFO stream extracted
** from parenthesized arithmetic expressions of integer operands.
*/


// class Token
t_token		*token_init(t_toktype type, void *val)
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

t_token		*token_clone(t_token const *tok)
{
	t_token *retv;

	if (tok == NULL)
		return (NULL);
	retv = (t_token*)malloc(sizeof(t_token));
	ft_memcpy(retv, tok, sizeof(t_token));
	return (retv);
}



/////// Token list
t_toklist	*toklist_init(t_tokctx *ctx, t_token const *tok)
{
	t_toklist *retv;

	retv = (t_toklist*)malloc(sizeof(t_toklist));
	retv->ctx = ctx;
	retv->tok = token_clone(tok);
	retv->next = NULL;
	return (retv);
}

void				toklist_free(t_toklist *tlist)
{
	if (tlist && tlist->next)
		toklist_free(tlist->next);
	if (tlist && tlist->tok)
		token_free(tlist->tok);
	if (tlist)
		free(tlist);
}

/*
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
	if (tlist == NULL)
		return (NULL);
	if (tlist->ctx->tlist_cursor) {
		tlist->ctx->tlist_cursor = tlist->ctx->tlist_cursor->next;
		return (tlist->ctx->tlist_cursor ? tlist->ctx->tlist_cursor->tok : NULL);
	} else
		return (NULL);
}

/**
*  Return pointer to tok un-dequeued
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


//////////////// Context
t_tokctx			*tokctx_init(void)
{
	t_tokctx	*ctx;

	ctx =(t_tokctx *)malloc(sizeof(*ctx));
	ctx->tlist_head = toklist_init(ctx, NULL);
	ctx->tlist_cursor = ctx->tlist_head;
	return (ctx);
}

void				tokctx_free(t_tokctx *ctx)
{
	if (ctx) {
		if (ctx->tlist_head) {
			toklist_free(ctx->tlist_head->next);
			free(ctx->tlist_head);
		}
		free(ctx);
	}
}

t_token						*tokctx_enqueue(t_tokctx *ctx, t_token *tok)
{
	if (!(ctx && tok))
		return (NULL);
	return (toklist_enqueue(ctx->tlist_head, tok));
}

t_token						*tokctx_dequeue(t_tokctx *ctx)
{
	if (!ctx)
		return (NULL);
	return (toklist_dequeue(ctx->tlist_head));
}

t_token						*tokctx_undequeue(t_tokctx *ctx, t_token *tok)
{
	if (!(ctx && tok))
		return (NULL);
	return (toklist_undequeue(ctx->tlist_head, tok));
}

t_token		*tokctx_reduce(t_tokctx *ctx, t_token *from, t_token *to, t_token *replacement)
{
	t_toklist *tlist;
	if (!ctx)
		return (NULL);
	tlist = ctx->tlist_head;
	while (tlist->next && tlist->next->tok != from)
		tlist = tlist->next;
	while (tlist->next && tlist->next->tok != to)
	{
		t_token *rmtok = tlist->next->tok;
		tlist->next = tlist->next->next;
		token_free(rmtok);
	}
	if (tlist->next->tok != NULL)
		token_free(tlist->next->tok);
	tlist->next->tok = token_clone(replacement);
	return (tlist->next->tok);
}

/*
 ** vim: ts=4 sw=4
 */
