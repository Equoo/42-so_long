/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:43:36 by dderny            #+#    #+#             */
/*   Updated: 2025/01/17 15:58:01 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/vector2d.h"
#include <math.h>

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
