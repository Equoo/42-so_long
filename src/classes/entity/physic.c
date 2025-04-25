/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 04:36:34 by dderny            #+#    #+#             */
/*   Updated: 2025/04/25 20:18:22 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/element.h"
#include "classes/entity.h"
#include "collisions.h"
#include "libft.h"
#include "scene.h"
#include "so_long.h"
#include "vector2d.h"

static void	on_collides(t_entity *ent, t_sweep res)
{
	t_entity	*other;

	if (ent->on_collide)
		ent->on_collide(ent, res.hit.element, res);
	if (res.hit.element && res.hit.element->class & CGROUP_ENTITY)
	{
		other = cast_entity(res.hit.element->parent);
		if (other && other->on_collide)
			other->on_collide(other, ent->base, res);
	}
}

static t_float2d	collide(t_entity *ent, t_float2d vel)
{
	t_trace		trace;
	t_sweep		res;
	int			i;
	t_float2d	remaining;

	i = -1;
	while (++i < MAX_SWEEP_ITERATIONS)
	{
		trace = (t_trace){ent->base->pos, ent->base->pos, ent->hull, CGROUP_ALL,
			ent->base->id};
		trace.to = float2d_add(trace.to, vel);
		res = world_sweep_aabb(ent->base->scene, trace);
		if (!res.hit.touch || res.time >= 1.0f)
			break ;
		on_collides(ent, res);
		ent->base->pos = float2d_lerp(ent->base->pos, trace.to, res.time);
		remaining = float2d_sub(vel, float2d_multiply(vel,
					float2d_abs(res.hit.normal)));
		ent->velocity = float2d_scaled(remaining, 1.0f - res.time);
		ent->base->pos = float2d_add(ent->base->pos, float2d_scaled(
					res.hit.normal, EPSILON));
		vel = remaining;
	}
	return (float2d_add(ent->base->pos, vel));
}

static void	isgrounded(t_entity *ent)
{
	t_float2d	from;
	t_sweep		res;

	from = (t_float2d){ent->base->pos.x + ent->hull.min.x, ent->base->pos.y
		+ 1};
	if (ent->gravity_dir.y > 0)
		from.y -= aabb_h(ent->hull) + 2;
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
	ent->base->pos = collide(ent, ent->velocity);
	isgrounded(ent);
	if (ent->b_isground)
		ent->velocity = float2d_scaled(ent->velocity, 1 - (frametime * 5));
	else
		ent->velocity = float2d_scaled(ent->velocity, 1 - (frametime * 3));
}
