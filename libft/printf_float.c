/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:59:44 by dderny            #+#    #+#             */
/*   Updated: 2025/01/26 02:10:51 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdint.h>
#include <stdlib.h>

char	*convertfloat(double nbr, t_pflag ptype, int *len)
{
	char		*str;
	t_ltoainfo	info;

	info = (t_ltoainfo){{BASE10, 10}, 0, 0, 0, NULL};
	info.zeros = 6;
	if (ptype.atributs[F_PLUS])
		info.sign = '+';
	if (ptype.atributs[F_SPACE])
		info.sign = ' ';
	if (ptype.atributs[F_POINT])
		info.zeronbr = 1;
	if (ptype.atributs[F_ZERO])
		info.zeros = ptype.min;
	if (ptype.atributs[F_POINT])
		info.zeros = ptype.atributs[F_POINT] - 1;
	str = ft_ftoa(nbr, info, len);
	return (str);
}

char	*free_join(char *a, char *b)
{
	char	*res;

	res = ft_strjoin(a, b);
	free(a);
	free(b);
	return (res);
}

char	*ft_ftoa(double nbr, t_ltoainfo info, int *strlen)
{
	char	*str;
	char	*strfract;
	int		sign;
	double	fractionnal;
	int		i;

	sign = 1;
	if (*(long *)&nbr >> 63)
		sign = -1;
	str = ft_lltoa_base((long)nbr * sign, (t_ltoainfo){{BASE10, 10}, info.sign,
			0, 0, NULL}, strlen);
	strfract = ft_calloc(1, info.zeros + 2);
	strfract[0] = '.';
	fractionnal = nbr - (long)nbr;
	i = 0;
	while (i <= info.zeros && ++i)
	{
		fractionnal *= 10;
		strfract[i] = '0' + (int)fractionnal;
		fractionnal -= (int)fractionnal;
	}
	*strlen += i;
	str = free_join(str, strfract);
	return (str);
}
