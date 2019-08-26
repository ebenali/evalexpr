/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_string2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 12:12:19 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/25 17:47:40 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libc.h"

char		*ft_strcpy(char *dest, const char *src)
{
	char *retv;

	retv = dest;
	while ((*dest++ = *src++))
		continue ;
	return (retv);
}

char		*ft_strdup(const char *s)
{
	return (ft_strcpy((char*)malloc(ft_strlen(s) + 1), s));
}

char		*ft_strtok(char *s, const char *dlm)
{
	static	char	*buf = NULL;
	char			*tok;

	if (buf == NULL || s != NULL)
		buf = s;
	while (buf && dlm && *buf && ft_strchr(dlm, *buf) != NULL)
		++buf;
	if (buf && *buf)
	{
		tok = buf;
		while (*buf && *(buf + 1) && ft_strchr(dlm, *(buf + 1)) == NULL)
			++buf;
		if (*buf != '\0')
		{
			if (*(buf + 1) != '\0')
			{
				*(buf + 1) = '\0';
				buf = buf + 2;
			}
			else
				buf = NULL;
		}
		return (tok);
	}
	return (NULL);
}

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	total_len;

	total_len = 0;
	while (*dest != '\0' && size)
	{
		++total_len;
		--size;
		++dest;
	}
	while (size != 0)
	{
		if (size == 1 || (*dest++ = *src) == '\0')
			break ;
		else
			src++;
		++total_len;
		--size;
	}
	if (size >= 1)
		*dest = '\0';
	while (*src++)
		++total_len;
	return (total_len);
}

/*
** vim: ts=4 sw=4
*/
