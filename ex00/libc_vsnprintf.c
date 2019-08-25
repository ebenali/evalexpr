/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_vsnprintf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 10:01:43 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/24 13:08:03 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include "libc.h"

/*
** Using builtin compiler primitives for current CPU architecture.
** No system standard library code is referenced at compile or link time.
*/

static	const signed g_printf_basemap[] = {
	['X']= -16,
	['x']= +16,
	['o']= -8,
	['b']= -2,
	['d']= +10,
	['i']= +10,
	['u']= -10,
};

static const unsigned g_printf_longlens[] = {
	[0]= sizeof(int) * CHAR_BIT,
	[1]= sizeof(long) * CHAR_BIT,
	[2]= sizeof(long long) * CHAR_BIT,
};

static const unsigned g_printf_halflens[] = {
	[0]= sizeof(int) * CHAR_BIT,
	[1]= sizeof(short) * CHAR_BIT,
	[2]= sizeof(char) * CHAR_BIT,
};

static int	ft_snputs(char *buf, size_t sz, const char *str)
{
	int chars_out;

	chars_out = 0;
	while (buf && sz && (sz - 1) && *buf)
	{
		++buf;
		--sz;
	}
	while (buf && str && *str && sz && (sz - 1))
	{
		*buf++ = *str++;
		--sz;
		++chars_out;
	}
	if (buf && sz != 0)
		*buf = '\0';
	return (chars_out);
}

static int	ft_snputc(char *buf, size_t sz, int c)
{
	char tmp[2];

	tmp[0] = (char)c;
	tmp[1] = '\0';
	return (ft_snputs(buf, sz, tmp));
}

static void	ft_snprintf_numeric(char *buf, size_t sz, __builtin_va_list ap,
		struct s_printf_lenbase lenbase)
{
	unsigned	nbits;
	uintmax_t	n;
	_Bool		neg;

	nbits = (lenbase.len_mod >= 0 ? g_printf_longlens[lenbase.len_mod]
			: g_printf_halflens[-lenbase.len_mod]);
	neg = get_sgn_mag_stdarg(ap, nbits, lenbase.num_base, &n);
	if (lenbase.num_base == +10 && neg == true)
		ft_snputc(buf, sz, '-');
	ft_snputs(buf, sz, ft_uintmax_to_str(n, lenbase.num_base));
}

static void	ft_vsnprintf2(char *const buf, size_t const sz, const char **fmt,
		__builtin_va_list ap)
{
	struct s_printf_lenbase lenbase;

	if (**fmt == '%' && (*fmt)[1] != '%' && ++*fmt)
	{
		lenbase.len_mod = 0;
		if (**fmt == 's' && ++*fmt)
			ft_snputs(buf, sz, __builtin_va_arg(ap, const char *));
		else if (**fmt == 'c' && ++*fmt)
			ft_snputc(buf, sz, __builtin_va_arg(ap, int));
		while ((**fmt == 'l' || **fmt == 'h') && ++*fmt)
			lenbase.len_mod += (signed[2]){+1, -1}[*(*fmt - 1) == 'h'];
		if (ft_strchr("Xxobdiu", **fmt) != NULL)
		{
			lenbase.num_base = g_printf_basemap[(unsigned)*(*fmt)++];
			ft_snprintf_numeric(buf, sz, ap, lenbase);
		}
	}
	(void)(**fmt && ft_snputc(buf, sz, *(*fmt)++));
}

void		ft_vsnprintf(char *buf, size_t sz, const char *fmt,
		__builtin_va_list ap)
{
	if (!(buf && sz && sz <= INT_MAX))
		return ;
	*buf = '\0';
	while (buf && sz && fmt && *fmt)
		ft_vsnprintf2(buf, sz, &fmt, ap);
}

/*
** vim: sw=4 ts=4
*/
