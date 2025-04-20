/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:43:36 by dderny            #+#    #+#             */
/*   Updated: 2025/04/18 16:33:23 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector2d.h"

/*
** Substract two 2D float vectors
** @param self: the first vector
** @param other: the second vector
*/
t_float2d	float2d_sub(t_float2d self, t_float2d other)
{
	t_float2d	result;

	result.x = self.x - other.x;
	result.y = self.y - other.y;
	return (result);
}

/*
** Substract two 2D int vectors
** @param self: the first vector
** @param other: the second vector
*/
t_int2d	int2d_sub(t_int2d self, t_int2d other)
{
	t_int2d	result;

	result.x = self.x - other.x;
	result.y = self.y - other.y;
	return (result);
}
