/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:45:18 by dderny            #+#    #+#             */
/*   Updated: 2024/11/17 12:41:30 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*c_dest;
	const char	*c_src;
	size_t		i;

	if (!dest && !src)
		return (dest);
	c_dest = (char *)dest;
	c_src = (char *)src;
	i = -1;
	if (c_src < c_dest)
		while (++i < n)
			c_dest[n - i - 1] = c_src[n - i - 1];
	else
		while (++i < n)
			c_dest[i] = c_src[i];
	return (dest);
}
