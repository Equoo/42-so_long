/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:43:36 by dderny            #+#    #+#             */
/*   Updated: 2025/01/17 15:59:19 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/vector2d.h"

float	float2d_dot(t_float2d *self, t_float2d *other)
{
	return (self->x * other->x + self->y * other->y);
}

int	int2d_dot(t_int2d *self, t_int2d *other)
{
	return (self->x * other->x + self->y * other->y);
}
