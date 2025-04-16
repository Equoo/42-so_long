/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabbtoaabb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:42:49 by dderny            #+#    #+#             */
/*   Updated: 2025/04/16 21:44:00 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector2d.h"

float	aabb_w(t_faabb hull)
{
	return (ft_fabs(hull.b.x - hull.a.x));
}

float	aabb_h(t_faabb hull)
{
	return (ft_fabs(hull.b.y - hull.a.y));
}