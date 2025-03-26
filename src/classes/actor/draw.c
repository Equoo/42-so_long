/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:20:50 by dderny            #+#    #+#             */
/*   Updated: 2025/03/26 04:32:20 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entities/actor.h"
#include "classes/texture.h"
#include "classes/vector2d.h"

/*
static double sanim;
	if (!sanim)
		sanim = env->time;
	double tanim = (env->time - sanim) / 0.8 * 7;
	mylx_img_copy((t_iaabb){(t_int2d){32 * (int)tanim, 0}, (t_int2d){32 * ((int)tanim + 1), 32}}, (t_int2d){86, 160}, lbuffer, env->character->img);
	mylx_img_blend((t_iaabb){(t_int2d){32 * (int)tanim, 0}, (t_int2d){32 * ((int)tanim + 1), 32}}, (t_int2d){86, 146}, lbuffer, env->character->img);
	if (env->time - sanim > 0.8)
		sanim = env->time;
		 */

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
	texture_blend_anim(self->texture, buffer, transform, self->anim, self->cycle);
}
