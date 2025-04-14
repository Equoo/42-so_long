/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_coroutine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 23:01:54 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entities/player.h"
#include "vector2d.h"

void player_anim_coroutine(t_actor *self)
{
	t_player	*player;
	float		speed;

	player = (t_player *)self->base->parent;
	speed = float2d_length(player->entity->velocity);
	if (player->entity->b_isground && speed <= 1.5 && speed >= 0.05)
	{
		if (ft_strcmp(player->base->anim, "W_1") && player->base->cycle <= 0.1)
			player->base->anim = "W_2";
		else
			player->base->anim = "W_1";
	}
	else if (player->entity->b_isground && speed > 1.5 && speed <= 4)
		player->base->anim = "W_3";
	else if (player->entity->b_isground && speed > 4)
	{
		if (ft_strcmp(player->base->anim, "Run_1") && player->base->cycle <= 0.1)
			player->base->anim = "Run_2";
		else
			player->base->anim = "Run_1";
	}
	else if (!player->entity->b_isground)
	{
		if (player->entity->velocity.y < 0)
			player->base->anim = "Stop";
		else
			player->base->anim = "Stop";
	}
	else
		player->base->anim = "Idle_1";
}
