/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:00:07 by dderny            #+#    #+#             */
/*   Updated: 2024/12/05 12:02:01 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *str)
{
	const char	*const_str;

	if (!str)
		return (0);
	const_str = str;
	while (*const_str != '\0')
		++const_str;
	return (const_str - str);
}
