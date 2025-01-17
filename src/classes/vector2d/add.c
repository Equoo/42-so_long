/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:49:37 by dderny            #+#    #+#             */
/*   Updated: 2025/01/17 15:59:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/vector2d.h"

void	float2d_add(t_float2d *self, t_float2d *other)
{
	self->x += other->x;
	self->y += other->y;
}

void	int2d_add(t_int2d *self, t_int2d *other)
{
	self->x += other->x;
	self->y += other->y;
}
