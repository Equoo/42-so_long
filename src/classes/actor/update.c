/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:55:01 by dderny            #+#    #+#             */
/*   Updated: 2025/04/24 16:09:36 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entity.h"
#include "classes/entities/actor.h"
#include "texture.h"

void	actor_update(t_element *self)
{
	t_actor	*actor;

	entity_physic(self);
	actor = cast_actor(self->parent);
	if (actor && actor->health <= 0)
	{

		if (!actor->die_end_time)
		{
			actor->die_end_time = self->scene->env->time
				+ texture_slice_time(self->texture, actor->death_anim);
			actor->entity->nocollision = 1;
			self->play_anim(self, actor->death_anim);
		}
		else if (actor->die_end_time <= self->scene->env->time)
			self->del(&self);
	}
}
