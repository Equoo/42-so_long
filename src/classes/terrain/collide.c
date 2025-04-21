/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 05:17:32 by dderny            #+#    #+#             */
/*   Updated: 2025/04/21 15:29:54 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "vector2d.h"
#include "collisions.h"
#include <X11/X.h>
#include <X11/Xutil.h>
#include <libft.h>

#define MAX_SWEEP_ITERATIONS 4

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
		trace.ignore = ent->base->id;

		res = world_sweep_aabb(self->base->scene, trace);
		__builtin_printf("Collision TES: %d\n", i);

		if (!res.hit.touch || res.time >= 1.0f)
			break;
		__builtin_printf("Collision detected at time: %f\n", res.time);

		// Move to contact point
		ent->base->pos = float2d_lerp(ent->base->pos, trace.to, res.time);

		// Slide velocity along the hit normal
		t_float2d normal = res.hit.normal;
		t_float2d remaining = float2d_sub(remaining_vel, float2d_multiply(remaining_vel, float2d_abs(normal)));

		ent->velocity = float2d_scaled(remaining, 1.0f - res.time);

		// Add a tiny nudge along the normal to prevent sticking
		#define NUDGE_EPSILON 0.001f
		ent->base->pos = float2d_add(ent->base->pos, float2d_scaled(normal, NUDGE_EPSILON));

		// Update for next iteration
		remaining_vel = remaining;
	}

	// Final move
	ent->base->pos = float2d_add(ent->base->pos, remaining_vel);
	return (0);
}
