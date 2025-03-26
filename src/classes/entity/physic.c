/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 04:36:34 by dderny            #+#    #+#             */
/*   Updated: 2025/03/26 06:04:41 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/element.h"
#include "classes/entity.h"
#include "classes/terrain.h"
#include "classes/vector2d.h"
#include "so_long.h"

#define GRAVITY -9.1

void			entity_physic(t_element *self)
{
	t_entity	*ent;
	t_terrain	*terrain;
	t_gameenv	*env;

	element_update(self);
	env = self->scene->env;
	ent = cast_entity(self->parent);
	if (!ent->nogravity)
		ent->velocity.y -= GRAVITY;

	terrain = self->scene->terrain;
	if (terrain)
		self->pos = terrain->collide(terrain, ent,
				float2d_scaled(ent->velocity, env->frametime),
				float2d_add(self->pos, float2d_scaled(ent->velocity, env->frametime)));
	else
		self->pos = float2d_add(self->pos,
		float2d_scaled(ent->velocity, env->frametime));

	float2d_sub(&ent->velocity, float2d_scaled((t_float2d){0.1, 0.1}, env->frametime));
}
