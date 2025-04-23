/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:55:01 by dderny            #+#    #+#             */
/*   Updated: 2025/04/23 18:00:17 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entity.h"
#include "classes/entities/actor.h"

void	actor_update(t_element *self)
{
	t_actor	*actor;

	entity_physic(self);
	actor = cast_actor(self->parent);
	//__builtin_printf("actor_update: %p, health %d\n", actor, actor->health);
	if (actor && actor->health <= 0)
	{
		self->del(&self);
	}
}