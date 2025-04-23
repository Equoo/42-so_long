/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:12:45 by dderny            #+#    #+#             */
/*   Updated: 2025/04/23 18:01:02 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entities/player.h"
#include "classes/entity.h"
#include "scene.h"
#include "vector2d.h"
#include "collisions.h"

void	player_attack(t_player *self)
{
	t_trace	trace;
	t_sweep	sweep;
	t_actor	*actor;

	trace = (t_trace){0};
	trace.from = float2d_add(self->base->pos,
		(t_float2d){self->entity->hull.min.x * 2, 0});
	trace.to = trace.from;
	trace.hull = self->entity->hull;
	trace.mask = CGROUP_ACTOR;
	trace.ignore = self->base->id;
	sweep = world_sweep_aabb(self->base->scene, trace);
	__builtin_printf("player_attack: %d, %p\n", sweep.hit.touch, sweep.hit.element);
	actor = NULL;
	if (sweep.hit.touch && sweep.hit.element
		&& sweep.hit.element->class & CGROUP_ACTOR)
		actor = cast_actor(sweep.hit.element->parent);
	if (actor)
		actor->health -= 50;
	self->base->play_anim(self->base, "Attack_1");
}
