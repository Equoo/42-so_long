/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:29:58 by dderny            #+#    #+#             */
/*   Updated: 2024/11/20 11:59:51 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1char;
	unsigned char	*s2char;
	size_t			i;

	s1char = (unsigned char *)s1;
	s2char = (unsigned char *)s2;
	i = 0;
	while (i < n && s1char[i] == s2char[i])
		i++;
	if (!n || i == n)
		return (0);
	else
		return ((int)(s1char[i] - s2char[i]));
}
