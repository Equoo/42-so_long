/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 04:36:34 by dderny            #+#    #+#             */
/*   Updated: 2025/04/16 00:56:57 by dderny           ###   ########.fr       */
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
	t_float2d	res;
	double		frametime;

	env = self->scene->env;
	frametime = env->frametime;
	if (frametime > 0.5)
		frametime = 0.5;
	ent = cast_entity(self->parent);
	if (!ent->nogravity)
		ent->velocity.y -= GRAVITY * env->frametime;

	t_float2d	new_pos = float2d_add(self->pos,
		ent->velocity);

	terrain = self->scene->terrain;
	if (terrain)
		new_pos = terrain->collide(terrain, ent,
				float2d_scaled(ent->velocity, env->frametime),
				new_pos);
	self->pos = new_pos;

	ent->velocity = float2d_scaled(ent->velocity, 1 - (3 * frametime));

	ent->b_isground = trace_grid((t_float2d){ent->base->pos.x + ent->hull.a.x, ent->base->pos.y + 1}, (t_float2d){ent->base->pos.x + ent->hull.b.x, ent->base->pos.y + 1}, self->scene->terrain, &res);
}
