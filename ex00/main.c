/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 08:09:54 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/24 21:12:34 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "libc.h"
#include "lexer.h"

static int		rdp(const char * const rest_immut, char prev_op,
		unsigned paren_lvl) {
	ft_printf("%s: rest='%s', prevop='%c', parenlvl=%u\n", __func__, rest_immut, prev_op, paren_lvl);
}

static int	eval(const char *tidy)
{
	t_tokctx *ctx;

	if ((ctx = lex(tidy)) == NULL) {
		ft_printf("%s: error: failed to parse expression\n", __func__);
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
