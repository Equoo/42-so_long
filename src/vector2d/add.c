/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:49:37 by dderny            #+#    #+#             */
/*   Updated: 2025/04/22 14:40:00 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector2d.h"

t_float2d	float2d_add(t_float2d self, t_float2d other)
{
	self.x += other.x;
	self.y += other.y;
	return (self);
}

t_int2d	int2d_add(t_int2d self, t_int2d other)
{
	self.x += other.x;
	self.y += other.y;
	return (self);
}
