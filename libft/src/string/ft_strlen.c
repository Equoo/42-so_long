/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:00:07 by dderny            #+#    #+#             */
/*   Updated: 2025/02/04 08:29:41 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *str)
{
	const char	*const_str;

	const_str = str;
	while (str)
	{
		if (!str[0])
			return (str - const_str);
		if (!str[1])
			return (str - const_str + 1);
		if (!str[2])
			return (str - const_str + 2);
		if (!str[3])
			return (str - const_str + 3);
		if (!str[4])
			return (str - const_str + 4);
		if (!str[5])
			return (str - const_str + 5);
		if (!str[6])
			return (str - const_str + 6);
		if (!str[7])
			return (str - const_str + 7);
		str += 8;
	}
	return (const_str - str);
}
