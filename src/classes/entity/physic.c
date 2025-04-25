/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 04:36:34 by dderny            #+#    #+#             */
/*   Updated: 2025/04/25 02:21:52 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/element.h"
#include "classes/entity.h"
#include "classes/terrain.h"
#include "libft.h"
#include "vector2d.h"
#include "collisions.h"
#include "so_long.h"
#include <math.h>

#define GRAVITY 9.1

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
		ent->velocity = float2d_sub(ent->velocity,
			float2d_scaled(ent->gravity_dir, GRAVITY * frametime));
	ent->velocity.x = ft_fclamp(ent->velocity.x, -16, 16);
	ent->velocity.y = ft_fclamp(ent->velocity.y, -16, 16);
	terrain = self->scene->terrain;
	if (terrain)
		terrain->collide(terrain, ent, ent->velocity);
	else
		ent->base->pos = float2d_add(ent->base->pos, ent->velocity);

	t_float2d from = (t_float2d){ent->base->pos.x + ent->hull.min.x, ent->base->pos.y + 1};
	t_sweep	res = world_sweep_aabb(self->scene, (t_trace){from, from, {{0}, {aabb_w(ent->hull), 1}, {0}, {0}}, CGROUP_ALL, self->id});
	ent->b_isground = res.hit.touch;

	if (ent->b_isground)
		ent->velocity = float2d_scaled(ent->velocity, 1 - (frametime * 5));
	else
		ent->velocity = float2d_scaled(ent->velocity, 1 - (frametime * 3));
}
