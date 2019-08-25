/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_numeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 11:58:22 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/24 12:39:35 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <limits.h>
#include "libc.h"

static const char	g_printf_lowerbase[] = "0123456789abcdef";

static const char	g_printf_upperbase[] = "0123456789ABCDEF";

static unsigned		g_printf_longlens[] = {
	[0]= sizeof(int) * CHAR_BIT,
	[1]= sizeof(long) * CHAR_BIT,
	[2]= sizeof(long long) * CHAR_BIT,
};

_Bool				get_sgn_mag_stdarg(__builtin_va_list ap, unsigned nbits,
		signed nbase, uintmax_t *dest)
{
	uintmax_t			uu;
	_Bool				neg;
	__builtin_va_list	aap;

	__builtin_va_copy(aap, ap);
	if (nbits <= g_printf_longlens[0])
	{
		uu = __builtin_va_arg(ap, unsigned);
		neg = (int)uu < 0;
		(void)((nbase == +10 && neg) && (uu = -__builtin_va_arg(aap, int)));
	}
	else if (nbits == g_printf_longlens[1])
	{
		uu = __builtin_va_arg(ap, unsigned long);
		neg = (long)uu < 0;
		(void)((nbase == +10 && neg) && (uu = -__builtin_va_arg(aap, long)));
	}
	else
	{
		uu = __builtin_va_arg(ap, unsigned long long);
		neg = (long long)uu < 0;
		(void)(nbase == 10 && neg && (uu = -__builtin_va_arg(aap, long long)));
	}
	*dest = uu;
	return (neg);
}

static char			*put_ull(char *buf, uintmax_t n, signed sbase)
{
	const char	*cset;
	unsigned	base;

	cset = sbase > 0 ? g_printf_lowerbase : g_printf_upperbase;
	base = sbase > 0 ? sbase : -sbase;
	if (n / base != 0)
		buf = put_ull(buf, n / base, sbase);
	*buf = cset[(n % base)];
	return (buf + 1);
}

const char			*ft_uintmax_to_str(uintmax_t n, signed base)
{
	static char	buf[64 + 8];

	*buf = 0;
	*put_ull(buf, n, base) = '\0';
	return (buf);
}

/*
**   ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~~
**   detect_base(): helper routine for ft_strtoimax() below
*/

static int			detect_base(const char **buf)
{
	while (ft_strchr("\t\n ", **buf))
		(*buf)++;
	if (**buf == '0' && (*buf)++)
	{
		if ((**buf == 'x' || **buf == 'X') && (*buf)++)
			return (16);
		else if (**buf == 'b' && (*buf)++)
			return (2);
		return (8);
	}
	return (10);
}

intmax_t			ft_strtoimax(const char *str, char **endp, int base)
{
	int			sign;
	uintmax_t	absv;

	if (!(str && (base == 0 || (base >= 2 && base <= 16))))
	{
		errno = EINVAL;
		return (0);
	}
	else if (base == 0)
		base = detect_base(&str);
	else
		while (ft_strchr("\t\n ", *str))
			++str;
	sign = +1;
	if (*str == '-' || *str == '+')
		sign = (int[2]){-1, +1}[*str++ == '+'];
	absv = 0;
	while (*str && *str >= '0' && ft_strchr(g_printf_lowerbase,
				ft_tolower(*str)) && (ft_strchr(g_printf_lowerbase,
					ft_tolower(*str)) - g_printf_lowerbase) < base)
		absv = absv * base + (ft_strchr(g_printf_lowerbase,
					ft_tolower(*str++)) - g_printf_lowerbase);
	if (endp != NULL)
		*endp = (char*)str;
	return (intmax_t)(absv * sign);
}

/*
** vim: ts=4 sw=4
*/
