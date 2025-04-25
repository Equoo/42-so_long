/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 04:36:34 by dderny            #+#    #+#             */
/*   Updated: 2025/04/25 12:22:20 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/element.h"
#include "classes/entity.h"
#include "collisions.h"
#include "libft.h"
#include "so_long.h"
#include "vector2d.h"

static int	collide(t_entity *ent, t_float2d vel)
{
	t_trace		trace;
	t_sweep		res;
	t_float2d	remaining_vel;
	int			i;
	t_float2d	normal;
	t_float2d	remaining;

	remaining_vel = vel;
	for (i = 0; i < MAX_SWEEP_ITERATIONS; i++)
	{
		trace = (t_trace){0};
		trace.from = ent->base->pos;
		trace.to = float2d_add(ent->base->pos, remaining_vel);
		trace.hull = ent->hull;
		trace.mask = CGROUP_ALL;
		trace.ignore = ent->base->id;
		res = world_sweep_aabb(ent->base->scene, trace);
		if (!res.hit.touch || res.time >= 1.0f)
			break ;
		if (ent->on_collide)
			ent->on_collide(ent, res.hit.element, res);
		ent->base->pos = float2d_lerp(ent->base->pos, trace.to, res.time);
		normal = res.hit.normal;
		remaining = float2d_sub(remaining_vel, float2d_multiply(remaining_vel,
					float2d_abs(normal)));
		ent->velocity = float2d_scaled(remaining, 1.0f - res.time);
		ent->base->pos = float2d_add(ent->base->pos, float2d_scaled(normal,
					EPSILON));
		remaining_vel = remaining;
	}
	// Final move
	ent->base->pos = float2d_add(ent->base->pos, remaining_vel);
	return (0);
}

static void	isgrounded(t_entity *ent)
{
	t_float2d	from;
	t_sweep		res;

	from = (t_float2d){ent->base->pos.x + ent->hull.min.x, ent->base->pos.y
		+ 1};
	res = world_sweep_aabb(ent->base->scene, (t_trace){from, from, {{0},
			{aabb_w(ent->hull), 1}, {0}, {0}}, CGROUP_ALL, ent->base->id});
	ent->b_isground = res.hit.touch;
}

void	entity_physic(t_element *self)
{
	t_entity	*ent;
	t_gameenv	*env;
	double		frametime;

	env = self->scene->env;
	frametime = env->frametime;
	if (frametime > 0.1)
		frametime = 0.1;
	ent = cast_entity(self->parent);
	if (!ent->nogravity)
		ent->velocity = float2d_sub(ent->velocity,
				float2d_scaled(ent->gravity_dir, GRAVITY * frametime));
	ent->velocity.x = ft_fclamp(ent->velocity.x, -16, 16);
	ent->velocity.y = ft_fclamp(ent->velocity.y, -16, 16);
	collide(ent, ent->velocity);
	isgrounded(ent);
	if (ent->b_isground)
		ent->velocity = float2d_scaled(ent->velocity, 1 - (frametime * 5));
	else
		ent->velocity = float2d_scaled(ent->velocity, 1 - (frametime * 3));
}
