/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:43:36 by dderny            #+#    #+#             */
/*   Updated: 2025/02/07 00:13:28 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/vector2d.h"
#include <math.h>

/*
** Normalize a 2D float vector
** @param self: the vector
*/
void	float2d_normalize(t_float2d *self)
{
	float	len;

	len = sqrt(self->x * self->x + self->y * self->y);
	if (len > 0.0f)
	{
		self->x /= len;
		self->y /= len;
	}
}

/*
** Normalize a 2D int vector
** @param self: the vector
*/
void	int2d_normalize(t_int2d *self)
{
	int	len;

	len = sqrt(self->x * self->x + self->y * self->y);
	if (len > 0.0f)
	{
		self->x /= len;
		self->y /= len;
	}
}
