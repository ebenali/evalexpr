/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 07:53:15 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/24 21:50:28 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include "libc.h"

/*
** ft_memcpy: memcpy(3)-like except it doesn't return pointer to @dest.
** Copyies byte-wise until 8-byte memory alignment is achieved, then copies
** over remaining data efficiently with 64-bit granularity.
** Results are UNDEFINED if memory regions @dest and @src overlap.
*/

void		ft_memcpy(register void *dest, register void const *src,
		register size_t len)
{
	while (len / sizeof(uint64_t))
	{
		*((uint64_t*)dest) = *((uint64_t const*)src);
		(void)(dest = (char*)dest + sizeof(uint64_t));
		(void)(src = (const char*)src + sizeof(uint64_t));
		(void)(len -= sizeof(uint64_t));
	}
	while (len--)
	{
		(void)(*((char*)dest) = *((char const*)src));
		(void)(dest = (char*)dest + sizeof(char));
		(void)(src = (const char*)src + sizeof(char));
	}
}

size_t		ft_strlen(register const char *str)
{
	const char *p;

	p = str;
	while (*p)
		(void)++p;
	return ((size_t)(p - str));
}

const char	*ft_strchr(const char *s, int c)
{
	while (s && *s && *s != c)
		++s;
	if (s && *s && *s == c)
		return (s);
	return (NULL);
}

int			ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	while (n != 0)
	{
		--n;
		if (*s1 != *s2 || *s1 == '\0' || *s2 == '\0')
			break ;
		++s1;
		++s2;
	}
	if (n != 0)
		return (*s1 - *s2);
	return (0);
}

const char	*ft_strerror(int eno)
{
	if (eno == EDOM)
		return ("Domain error");
	if (eno == ERANGE)
		return ("Range error");
	if (eno == ENOENT)
		return ("No such file or directory");
	if (eno == EINVAL)
		return ("Invalid argument");
	if (eno == EISDIR)
		return ("Is a directory");
	if (eno == ENOTDIR)
		return ("Not a directory");
	if (eno == EIO)
		return ("I/O error");
	if (eno == ENOMEM)
		return ("Out of memory");
	if (eno == EPIPE)
		return ("Broken pipe");
	return ("no error information");
}

/*
** vim: ts=4 sw=4
*/
