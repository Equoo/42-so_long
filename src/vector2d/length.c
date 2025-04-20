/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:43:36 by dderny            #+#    #+#             */
/*   Updated: 2025/04/18 16:33:23 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector2d.h"
#include <math.h>

/*
** Length of a 2D float vector
** @param self: the vector
** @return the length
*/
float	float2d_length(t_float2d self)
{
	return (sqrt(self.x * self.x + self.y * self.y));
}

/*
** Length of a 2D int vector
** @param self: the vector
** @return the length
*/
int	int2d_length(t_int2d self)
{
	return (sqrt(self.x * self.x + self.y * self.y));
}
