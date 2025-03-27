/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaled.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:43:36 by dderny            #+#    #+#             */
/*   Updated: 2025/03/26 20:43:29 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/vector2d.h"

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
