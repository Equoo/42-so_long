/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:01:07 by dderny            #+#    #+#             */
/*   Updated: 2025/04/21 15:01:35 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector2d.h"
#include <libft.h>

t_float2d	float2d_lerp(t_float2d a, t_float2d b, float t)
{
	t_float2d	result;

	if (t < 0)
		t = 0;
	else if (t > 1)
		t = 1;
	result.x = ft_lerp(a.x, b.x, t);
	result.y = ft_lerp(a.y, b.y, t);
	return (result);
}
