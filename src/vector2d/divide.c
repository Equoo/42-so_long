/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:13:19 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector2d.h"

t_float2d	float2d_divide(t_float2d self, t_float2d other)
{
	t_float2d	result;

	result.x = self.x / other.x;
	result.y = self.y / other.y;
	return (result);
}

t_int2d	int2d_divide(t_int2d self, t_int2d other)
{
	t_int2d	result;

	result.x = self.x / other.x;
	result.y = self.y / other.y;
	return (result);
}
