/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:37:29 by dderny            #+#    #+#             */
/*   Updated: 2025/04/18 16:33:23 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector2d.h"

t_int2d	to_int2d(t_float2d vec)
{
	return ((t_int2d){vec.x, vec.y});
}

t_float2d	to_float2d(t_int2d vec)
{
	return ((t_float2d){vec.x, vec.y});
}
