/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaled.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:43:36 by dderny            #+#    #+#             */
/*   Updated: 2025/04/18 16:33:23 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector2d.h"

/*
** Scale a 2D float vector
** @param self: the vector
** @param factor: the factor
*/
t_float2d	float2d_scaled(t_float2d self, float factor)
{
	t_float2d	new;

	if (factor == 0)
		return (self);
	new.x = self.x * factor;
	new.y = self.y * factor;
	return (new);
}

/*
** Scale a 2D int vector
** @param self: the vector
** @param factor: the factor
*/
t_int2d	int2d_scaled(t_int2d self, int factor)
{
	t_int2d	new;

	if (factor == 0)
		return (self);
	new.x = self.x * factor;
	new.y = self.y * factor;
	return (new);
}
