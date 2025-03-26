/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:37:29 by dderny            #+#    #+#             */
/*   Updated: 2025/03/26 02:39:08 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/vector2d.h"

t_int2d	to_int2d(t_float2d vec)
{
	return ((t_int2d){vec.x, vec.y});
}

t_float2d	to_float2d(t_int2d vec)
{
	return ((t_float2d){vec.x, vec.y});
}
