/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:43:36 by dderny            #+#    #+#             */
/*   Updated: 2025/02/07 00:14:06 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/vector2d.h"

/*
** Substract two 2D float vectors
** @param self: the first vector
** @param other: the second vector
*/
void	float2d_sub(t_float2d *self, t_float2d *other)
{
	self->x -= other->x;
	self->y -= other->y;
}

/*
** Substract two 2D int vectors
** @param self: the first vector
** @param other: the second vector
*/
void	int2d_sub(t_int2d *self, t_int2d *other)
{
	self->x -= other->x;
	self->y -= other->y;
}
