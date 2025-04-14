/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 05:17:32 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "vector2d.h"
#include "collisions.h"
#include <X11/X.h>
#include <X11/Xutil.h>
#include <libft.h>

t_float2d	terrain_collide(t_terrain *self, t_entity *ent, t_float2d vel, t_float2d newpos)
{
	t_float2d	res;
	t_float2d	norm;
	(void)vel;
	(void)ent;
	(void)self;
	(void)res;

	res = (t_float2d){0, 0};
	if (swept_aabb_grid((t_faabb){ent->base->pos, newpos}, ent->hull, self, &res, &norm))
	{
		//newpos = res;
		ent->velocity = float2d_sub(ent->velocity, float2d_multiply(ent->velocity, float2d_abs(norm)));
		newpos = float2d_add(ent->base->pos, ent->velocity);
		__builtin_printf("collide %f %f\n", norm.x, norm.y);
	}
	return (newpos);
}
