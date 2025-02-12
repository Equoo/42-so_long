/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:27:18 by dderny            #+#    #+#             */
/*   Updated: 2025/02/12 14:27:35 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	long long	nbr;
	long long	precision;
	long long	precc;
	int			len;

	nbr = ft_atoll(str);
	while (*str != '.')
		str++;
	str++;
	precision = ft_atoll(str);
	precc = precision;
	len = 1;
	while (precc != 0)
	{
		precc /= 10;
		len *= 10;
	}
	return ((double)nbr + ((double)precision / len));
}