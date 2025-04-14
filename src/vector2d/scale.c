/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:43:36 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector2d.h"

/*
** Scale a 2D float vector
** @param self: the vector
** @param factor: the factor
*/
void	float2d_scale(t_float2d *self, float factor)
{
	self->x *= factor;
	self->y *= factor;
}

/*
** Scale a 2D int vector
** @param self: the vector
** @param factor: the factor
*/
void	int2d_scale(t_int2d *self, int factor)
{
	self->x *= factor;
	self->y *= factor;
}
