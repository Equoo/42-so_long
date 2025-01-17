/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:43:36 by dderny            #+#    #+#             */
/*   Updated: 2025/01/17 15:58:27 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/vector2d.h"
#include <math.h>

float	float2d_length(t_float2d *self)
{
	return (sqrt(self->x * self->x + self->y * self->y));
}

int	int2d_length(t_int2d *self)
{
	return (sqrt(self->x * self->x + self->y * self->y));
}