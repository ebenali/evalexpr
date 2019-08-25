/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 10:43:13 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/24 13:10:30 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char				buf[2048];
	__builtin_va_list	ap;

	__builtin_va_start(ap, fmt);
	ft_vsnprintf(buf, sizeof(buf), fmt, ap);
	ft_puts(buf);
	__builtin_va_end(ap);
}
