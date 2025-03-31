/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:43:36 by dderny            #+#    #+#             */
/*   Updated: 2025/03/31 19:22:13 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/vector2d.h"
#include <math.h>

/*
** Normalize a 2D float vector
** @param self: the vector
*/
t_float2d	float2d_normalize(t_float2d self)
{
	float	len;

	len = sqrt(self.x * self.x + self.y * self.y);
	if (len > 0.0f)
	{
		self.x /= len;
		self.y /= len;
	}
	return (self);
}

/*
** Normalize a 2D int vector
** @param self: the vector
*/
t_int2d	int2d_normalize(t_int2d self)
{
	int	len;

	len = sqrt(self.x * self.x + self.y * self.y);
	if (len > 0.0f)
	{
		self.x /= len;
		self.y /= len;
	}
	return (self);
}
