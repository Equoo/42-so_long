/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 04:36:34 by dderny            #+#    #+#             */
/*   Updated: 2025/04/21 15:32:52 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/element.h"
#include "classes/entity.h"
#include "classes/terrain.h"
#include "vector2d.h"
#include "collisions.h"
#include "so_long.h"

#define GRAVITY -9.1

void			entity_physic(t_element *self)
{
	t_entity	*ent;
	t_terrain	*terrain;
	t_gameenv	*env;
	double		frametime;

	env = self->scene->env;
	frametime = env->frametime;
	if (frametime > 0.5)
		frametime = 0.5;
	ent = cast_entity(self->parent);
	if (!ent->nogravity)
		ent->velocity.y -= GRAVITY * env->frametime;

	terrain = self->scene->terrain;
	if (terrain)
		terrain->collide(terrain, ent, ent->velocity);
	else
		ent->base->pos = float2d_add(ent->base->pos, ent->velocity);

	ent->velocity = float2d_scaled(ent->velocity, 1 - (3 * frametime));

	t_float2d from = (t_float2d){ent->base->pos.x + ent->hull.min.x, ent->base->pos.y + 1};
	t_sweep	res = world_sweep_aabb(self->scene, (t_trace){from, from, {{0}, {aabb_w(ent->hull), 16}, {0}, {0}}, 0, self->id});
	__builtin_printf("res.time: %f, res.hit.touch: %d, res.hit.normal: %f %f, res.hit.pos: %f %f\n",
		res.time, res.hit.touch, res.hit.normal.x, res.hit.normal.y, res.hit.pos.x, res.hit.pos.y);
	ent->b_isground = res.hit.touch;
}
