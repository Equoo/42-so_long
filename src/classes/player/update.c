/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:19:09 by dderny            #+#    #+#             */
/*   Updated: 2025/04/24 23:38:50 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/element.h"
#include "classes/entities/actor.h"
#include "classes/entities/player.h"
#include "classes/entity.h"
#include "collisions.h"
#include "ft_printf.h"
#include "render.h"
#include "scene.h"
#include "vector2d.h"

void	player_update(t_element *self)
{
	t_player	*ply;

	actor_update(self);
	ply = (t_player *)self->parent;
	if (ply->is_jumping && ply->entity->b_isground)
	{
		ply->is_jumping = FALSE;
		self->play_anim(self, "J_3");
	}
	if (ply->entity->b_isground && ply->last_pos.x > 0 && ply->last_pos.y > 0
		&& (self->pos.x != ply->last_pos.x || self->pos.y != ply->last_pos.y))
	{
		ply->walk_count += float2d_length(float2d_sub(self->pos,
					ply->last_pos)) / TR_GRID_SIZE;
		ft_printf("Moves: %d\n", (int)ply->walk_count);
	}
	ply->last_pos = self->pos;
	self->scene->cam_pos = float2d_sub(self->pos,
			(t_float2d){(double)self->scene->env->render.r_width / 2,
			(double)self->scene->env->render.r_height / 2});
	self->scene->cam_pos.y -= self->scene->env->render.r_height / 6;
}
