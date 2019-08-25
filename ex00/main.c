/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 08:09:54 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/25 00:10:54 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "libc.h"
#include "lexer.h"

static int	eval(const char *tidy)
{
	t_tokctx *ctx;
	t_token *tok;

	if ((ctx = lex(tidy)) == NULL) {
		ft_printf("%s: error: failed to parse expression\n", __func__);
	}

	while ((tok = tokctx_dequeue(ctx))) {
		ft_printf("%s: arith token: type=%s", __func__, tok->type == TOK_NUM ? "NUM"
				: tok->type == TOK_OP ? "OP" : tok->type == TOK_LPAR ? "LPAR"  :  "RPAR");
		if (tok->type == TOK_NUM)
			ft_printf(", val=%lli\n", tok->val.num);
		else if (tok->type == TOK_OP)
			ft_printf(", val='%c'\n", tok->val.op);
		else
			ft_putchar('\n');
	}

	tokctx_free(ctx);
	return (0);
}

int				eval_expr(char *str)
{
	char	*tok;
	char	*dup;
	char	*tidy;
	int		retv;

	if (str && ft_strlen(str) != 0) {
		dup = ft_strdup(str);
		tidy = (char*)malloc(ft_strlen(str) + 1);
		*tidy = '\0';
		tok = NULL;
		while ((tok = ft_strtok(tok == NULL ? dup : NULL, " \t\n"))) {
			ft_strlcat(tidy, tok, ft_strlen(str) + 1);
		}
		free(dup);
		retv = eval(tidy);
		free(tidy);
	} else
		retv = 0;
	return (retv);
}

int				main(int argc, char *argv[])
{
	if (argc > 1)
		ft_printf("%i\n", eval_expr(argv[1]));
	return (0);
}

/*
 ** vim: ts=4 sw=4
 */
