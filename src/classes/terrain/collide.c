/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 05:17:32 by dderny            #+#    #+#             */
/*   Updated: 2025/04/24 16:03:53 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "vector2d.h"
#include "collisions.h"
#include <X11/X.h>
#include <X11/Xutil.h>
#include <libft.h>

int terrain_collide(t_terrain *self, t_entity *ent, t_float2d vel)
{
	t_trace	trace;
	t_sweep	res;
	t_float2d remaining_vel = vel;
	int i;

	for (i = 0; i < MAX_SWEEP_ITERATIONS; i++)
	{
		trace = (t_trace){0};
		trace.from = ent->base->pos;
		trace.to = float2d_add(ent->base->pos, remaining_vel);
		trace.hull = ent->hull;
		trace.mask = CGROUP_ALL;
		trace.ignore = ent->base->id;
		res = world_sweep_aabb(self->base->scene, trace);
		if (!res.hit.touch || res.time >= 1.0f)
			break;
		ent->base->pos = float2d_lerp(ent->base->pos, trace.to, res.time);

		t_float2d normal = res.hit.normal;
		t_float2d remaining = float2d_sub(remaining_vel, float2d_multiply(remaining_vel, float2d_abs(normal)));

		ent->velocity = float2d_scaled(remaining, 1.0f - res.time);
		ent->base->pos = float2d_add(ent->base->pos, float2d_scaled(normal, EPSILON));
		remaining_vel = remaining;
	}

	// Final move
	ent->base->pos = float2d_add(ent->base->pos, remaining_vel);
	return (0);
}
