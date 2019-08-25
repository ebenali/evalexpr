
#include <stdbool.h>
#include "libc.h"
#include "lexer.h"
#include "arithmetic.h"

static _Bool	lex_nbr(t_tokctx *ctx, const char **str, char prevc, intmax_t *num_val)
{
	char		*eptr;

	if (ft_strchr(g_digset, **str) || (ft_strchr("+-", **str) &&
				(prevc == '\0' || ft_strchr("+-", prevc) != NULL))) {
		*num_val = ft_strtoimax(*str, &eptr, 10);
		if (eptr == *str)
			return (false);
		else
			*str = eptr - 1;
	}
	return (true);
}

/**
 *  To build a general purpose lexer, parametrize token types and recognition
 *  rules instead of the hardcoded integer arithmetic here.
 */
t_tokctx	*lex(const char *str)
{
	t_tokctx	*ctx;
	char		prevc;
	intmax_t	num_val;
	t_token		*tmptok;

	if (!(str && (ctx = tokctx_init())))
		return (NULL);

	prevc = '\0';
	while (*str != '\0') {
		if (lex_nbr(ctx, &str, prevc, &num_val))
			tmptok = token_init(TOK_NUM, &num_val);
		else if (ft_strchr(g_opset, *str))
			tmptok = token_init(TOK_OP, (void*)str);
		else if (ft_strchr("()", *str))
			tmptok = token_init(*str == '(' ? TOK_LPAR : TOK_RPAR, NULL);
		else
			break ;
		tokctx_enqueue(ctx, tmptok);
		free(tmptok);
		prevc = *str++;
	}
	if (*str != '\0') {
		tokctx_free(ctx);
		return NULL;
	}
	return (ctx);
}
