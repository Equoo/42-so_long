/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_collide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 00:58:03 by dderny            #+#    #+#             */
/*   Updated: 2025/04/27 01:22:52 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entities/player.h"
#include "vector2d.h"

void	frog_on_collide(t_entity *self, t_element *other, t_sweep data)
{
	t_player	*ply;

	(void)self;
	if (other->class == CLASS_PLAYER)
	{
		ply = other->parent;
		if (ply->hit_cooldown > self->base->scene->env->time)
			return ;
		ply->actor->health -= 25;
		ply->entity->velocity = float2d_add(ply->entity->velocity,
				float2d_scaled(data.hit.normal, 100
					* self->base->scene->env->frametime));
		ply->base->play_anim(ply->base, "Dmg");
		ply->hit_cooldown = self->base->scene->env->time + 1;
	}
}
