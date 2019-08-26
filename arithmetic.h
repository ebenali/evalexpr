/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 20:44:32 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/25 17:58:29 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARITHMETIC_H
# define ARITHMETIC_H

# ifdef ARITH_PARSE

enum {
	ADD = '+', SUB = '-', MUL = '*', DIV = '/', MOD = '%'
};

#  define OPREC(op) (g_prc_tbl[(int)(op)])

static signed	g_prc_tbl[] = {
	[ADD]= 0,
	[SUB]= 0,
	[MUL]= 1,
	[DIV]= 1,
	[MOD]= 1,
};

# else

static char		g_digset[] = "0123456789";

static char		g_opset[] = "+-*/%";

# endif

#endif
