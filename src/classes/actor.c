/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 01:32:11 by dderny            #+#    #+#             */
/*   Updated: 2025/04/23 17:58:41 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entities/actor.h"
#include "classes/entity.h"
#include "scene.h"
#include <stdlib.h>
#include <stdint.h>

void	actor_del(t_element **self)
{
	t_actor	*actor;

	actor = cast_actor((*self)->parent);
	entity_del(self);
	if (actor)
		free(actor);
}

t_actor	*ft_actor(t_scene *scene)
{
	t_entity *entity;
	t_actor *actor;

	entity = ft_entity(scene);
	if (!entity)
		return (NULL);
	actor = ft_calloc(1, sizeof(t_actor));
	if (!actor)
	{
		entity->base->del(&entity->base);
		return (NULL);
	}
	actor->entity = entity;
	actor->actor = actor;
	actor->move = &actor_move;
	actor->direction = 1;
	actor->health = 100;
	actor->base = entity->base;
	actor->base->zindex = 10;
	actor->base->parent = actor;
	actor->base->update = &actor_update;
	actor->base->draw = &actor_draw;
	actor->base->class = CLASS_ACTOR;
	actor->base->del = &actor_del;
	actor->entity->base = actor->base;
	return (actor);
}

t_actor	*cast_actor(void *actor)
{
	if (!actor)
		return (NULL);
	return ((t_actor *)(((uintptr_t *)actor))[2]);
}
