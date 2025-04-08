/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:19:09 by dderny            #+#    #+#             */
/*   Updated: 2025/04/08 18:14:15 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/element.h"
#include "classes/entities/player.h"
#include "classes/entity.h"
#include "render.h"
#include "scene.h"
#include "vector2d.h"

void		player_update(t_element *self)
{
	//t_entity	*entity;

	element_update(self);
	entity_physic(self);
	//entity = cast_entity(self->parent);
	self->scene->cam_pos = float2d_sub(self->pos, (t_float2d){(double)self->scene->env->render.r_width / 2, (double)self->scene->env->render.r_height / 2});
	self->scene->cam_pos.y -= self->scene->env->render.r_height / 6;
}
