/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_stdio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 21:23:58 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/22 10:01:33 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdint.h>
#include "libc.h"

#if defined(WIN32) || defined(_WIN32)
# include <io.h>
# define STDOUT_FILENO	1
#else
# include <unistd.h>
#endif

int		ft_putchar(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

void	ft_puts(register const char *s)
{
	while (*s)
		ft_putchar(*s++);
}

/*
** vim: ts=4 sw=4
*/
