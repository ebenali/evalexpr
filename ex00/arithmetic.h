/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 20:44:32 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/24 21:01:37 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define OPREC(op) (prc_tbl[(int)(op)])
#define	ISOP(str) (ft_strlen((str)) == 1 && ft_strchr(g_oset, *(str)) != NULL)

enum 			{ ADD='+', SUB='-', MUL='*', DIV='/', MOD='%' };

static signed	prc_tbl[] = {
	[ADD]= 0,
	[SUB]= 0,
	[MUL]= 1,
	[DIV]= 1,
	[MOD]= 1,
};

static char		g_digset[] = "0123456789";

static char		g_opset[] = "+-*/%";

