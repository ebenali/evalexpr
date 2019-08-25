/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_ctype.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 15:31:21 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/22 15:37:04 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libc.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isxdigit(int c)
{
	return (ft_isdigit(c) || (ft_tolower(c) >= 'a'
				&& ft_tolower(c) <= 'f'));
}

int	ft_tolower(int c)
{
	return (ft_isalpha(c) ? (c | (1 << 5)) : c);
}

int	ft_toupper(int c)
{
	return (ft_isalpha(c) ? (c & !(1 << 5)) : c);
}
