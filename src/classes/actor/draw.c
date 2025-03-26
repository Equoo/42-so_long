/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:20:50 by dderny            #+#    #+#             */
/*   Updated: 2025/03/26 03:11:16 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entities/actor.h"
#include "classes/texture.h"
#include "classes/vector2d.h"

void	actor_draw(t_element *self, t_img *buffer)
{
	t_actor		*actor;
	t_transform	transform;

	actor = cast_actor(self->parent);
	if (!actor)
		return ;
	transform = t_from_pos(to_int2d(self->pos));
	if (actor->direction == -1)
		transform.scale.x = -1;
	texture_blend_anim(self->texture, buffer, transform, "Idle_1", 0);
}
