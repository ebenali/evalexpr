/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:39:50 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/25 13:19:58 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdint.h>
# include "libc.h"

enum						e_toktype {
							TOK_NUM,
							TOK_OP,
							TOK_LPAR,
							TOK_RPAR,
};

union						u_tokval {
	uintmax_t				num;
	char					op;
};

struct						s_token {
	enum e_toktype			type;
	union u_tokval			val;
};

struct						s_tokctx;

struct						s_toklist {
	struct s_token			*tok;
	struct s_tokctx			*ctx;
	struct s_toklist		*next;
};

struct						s_tokctx {
	struct s_toklist		*tlist_head;
	struct s_toklist		*tlist_cursor;
};

typedef union u_tokval		t_tokval;
typedef enum e_toktype		t_toktype;
typedef struct s_tokctx		t_tokctx;
typedef struct s_toklist	t_toklist;
typedef struct s_token		t_token;

t_token				*token_init(t_toktype type, void *val);

void					token_free(t_token *tok);

t_tokval				token_set(t_token *tok, t_tokval val);

t_token				*token_clone(t_token const *tok);

t_toklist			*toklist_init(t_tokctx *ctx, t_token const *tok);

void					toklist_free(t_toklist *tlist);

t_token				*toklist_enqueue(t_toklist *tlst, t_token const *tok);

t_token				*toklist_dequeue(t_toklist *tlist);

t_token				*toklist_undequeue(t_toklist *tlist, t_token *tok);

t_tokctx					*tokctx_init(void);

void						tokctx_free(t_tokctx *ctx);

t_token						*tokctx_enqueue(t_tokctx *ctx, t_token *tok);

t_token						*tokctx_dequeue(t_tokctx *ctx);

t_token						*tokctx_undequeue(t_tokctx *ctx, t_token *tok);

t_token						*tokctx_reduce(t_tokctx *ctx, t_token *from,
		t_token *to, t_token *replacement);

t_tokctx					*lex(const char *str);

#endif

/*
** vim: ts=4 sw=4
*/
