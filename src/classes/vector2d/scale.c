/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:43:36 by dderny            #+#    #+#             */
/*   Updated: 2025/01/17 15:57:42 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/vector2d.h"

void	float2d_scale(t_float2d *self, float factor)
{
	self->x *= factor;
	self->y *= factor;
}

void	int2d_scale(t_int2d *self, int factor)
{
	self->x *= factor;
	self->y *= factor;
}
