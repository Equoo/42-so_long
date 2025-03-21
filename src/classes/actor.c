/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 01:32:11 by dderny            #+#    #+#             */
/*   Updated: 2025/03/21 16:59:11 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entities/actor.h"
#include "classes/entity.h"
#include "classes/scene.h"
#include <stdlib.h>

void	actor_del(t_element **self)
{
	t_entity *entity;

	if ((*self)->parent)
	{
		entity = ((t_actor *)(*self))->entity;
		if (entity->parent)
			free((*self)->parent);
		free(entity);
	}
	free(*self);
	*self = NULL;
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
	*actor = (t_actor){0};
	actor->entity = entity;
	actor->base = entity->base;
	actor->base->class = CLASS_ACTOR;
	actor->base->del = actor_del;
	actor->entity->base = actor->base;
	return (actor);
}
