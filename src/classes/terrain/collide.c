/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 05:17:32 by dderny            #+#    #+#             */
/*   Updated: 2025/04/17 22:24:12 by dderny           ###   ########.fr       */
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
	t_trace	trace;
	(void)vel;
	(void)ent;
	(void)self;

	trace = (t_trace){0};
	trace.from = ent->base->pos;
	trace.to = newpos;
	trace.hull = ent->hull;
	trace.ignore = ent->base->id;
	trace = swept_aabb(self->base->scene, trace);
	if (trace.hit)
	{
		ent->velocity = float2d_sub(ent->velocity, float2d_multiply(ent->velocity, float2d_abs(trace.normal)));
		newpos = float2d_add(ent->base->pos, ent->velocity);
		__builtin_printf("ENTITY collide %d %f %f\n", ent->base->class, trace.normal.x, trace.normal.y);
	}
	return (newpos);
}
