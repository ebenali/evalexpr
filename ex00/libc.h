/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 21:22:54 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/24 18:29:50 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBC_H

# define LIBC_H

# include <stdint.h>
# include <stddef.h>

/*
** +---------------------------------------------------------------------------
** |                            libc_stdio.c
*/

struct			s_printf_lenbase {
	signed		len_mod;
	unsigned	num_base;
};

extern int		ft_putchar(char c);

extern void		ft_puts(register const char *s);

extern void		ft_vsnprintf(char *buf, size_t sz, const char *fmt,
		__builtin_va_list ap);

extern void		ft_printf(const char *fmt, ...);

extern void		ft_snprintf(char *buf, size_t n, const char *fmt, ...);

/*
** +---------------------------------------------------------------------------
** |
** |                         libc_string{,2}.c
*/

extern size_t	ft_strlen(register const char *str);

extern void		ft_memcpy(register void *dest, register void const *src,
		register size_t len);

const char		*ft_strchr(const char *s, int c);

extern int		ft_strncmp(const char *s1, const char *s2, unsigned int n);

const char		*ft_strerror(int eno);

extern char*	ft_strcpy(char *dest, const char *src);

extern char		*ft_strdup(const char *s);

extern char		*ft_strtok(char *s, const char *dlm);

extern size_t	ft_strlcat(char *dest, const char *src, size_t size);

/*
** +---------------------------------------------------------------------------
** |                          libc_numeric.c
*/

/*
** ft_uintmax_to_str():
**  - negative @base indicates alternate case charset (upper for negative)
** get_mag_stdarg() returns if magnitude is in the negative
*/

_Bool			get_sgn_mag_stdarg(__builtin_va_list ap, unsigned nbits,
		signed nbase, uintmax_t *dest);

const char		*ft_uintmax_to_str(uintmax_t n, signed base);

intmax_t		ft_strtoimax(const char *str, char **endp, int base);

/*
** +---------------------------------------------------------------------------
** |                            libc_ctype.c
*/

extern int		ft_isalpha(int c);

extern int		ft_isdigit(int c);

extern int		ft_isxdigit(int c);

extern int		ft_tolower(int c);

extern int		ft_toupper(int c);

#endif

/*
** vim: ts=4 sw=4
*/
