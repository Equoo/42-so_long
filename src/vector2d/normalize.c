/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:43:36 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector2d.h"
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
