/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:22:03 by dderny            #+#    #+#             */
/*   Updated: 2024/11/17 12:41:30 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*schar;
	size_t	i;

	if (!n)
		return (NULL);
	schar = (char *)s;
	i = 0;
	while (i < n && schar[i] != (char)c)
		i++;
	if (i == n)
		return (NULL);
	return ((void *)s + i);
}
