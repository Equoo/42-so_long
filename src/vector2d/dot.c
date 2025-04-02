/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:43:36 by dderny            #+#    #+#             */
/*   Updated: 2025/04/02 19:17:12 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector2d.h"

/*
** Dot product of two 2D float vectors
** @param self: the first vector
** @param other: the second vector
** @return the dot product
*/
float	float2d_dot(t_float2d *self, t_float2d *other)
{
	return (self->x * other->x + self->y * other->y);
}

/*
** Dot product of two 2D int vectors
** @param self: the first vector
** @param other: the second vector
** @return the dot product
*/
int	int2d_dot(t_int2d *self, t_int2d *other)
{
	return (self->x * other->x + self->y * other->y);
}
