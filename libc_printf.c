/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 10:43:13 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/25 17:52:18 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libc.h"

void	ft_snprintf(char *buf, size_t n, const char *fmt, ...)
{
	__builtin_va_list	ap;

	__builtin_va_start(ap, fmt);
	ft_vsnprintf(buf, n, fmt, ap);
	__builtin_va_end(ap);
}

void	ft_printf(const char *fmt, ...)
{
	char				buf[0x800];
	__builtin_va_list	ap;

	__builtin_va_start(ap, fmt);
	ft_vsnprintf(buf, sizeof(buf), fmt, ap);
	ft_puts(buf);
	__builtin_va_end(ap);
}

#ifdef ALLOW_MALLOC

void	ft_asprintf(char **str, const char *fmt, ...)
{
	__builtin_va_list	ap;

	if (!str || (*str = (char*)malloc(0x1000 - 128)) == NULL)
		return ;
	__builtin_va_start(ap, fmt);
	ft_vsnprintf(*str, 0x1000 - 128, fmt, ap);
	__builtin_va_end(ap);
}

#endif

/*
** vim: ts=4 sw=4
*/
