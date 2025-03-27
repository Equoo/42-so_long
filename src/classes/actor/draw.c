/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:20:50 by dderny            #+#    #+#             */
/*   Updated: 2025/03/26 18:13:12 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entities/actor.h"
#include "classes/texture.h"
#include "classes/vector2d.h"
#include "render.h"

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
	transform = t_from_pos(to_int2d(float2d_add(self->pos, self->txt_off_pos)));
	if (actor->direction == -1)
		transform.scale.x = -1;
	texture_blend_anim(self->texture, buffer, transform, self->anim, self->cycle);

	if (self->pos.x >= 0 && self->pos.x < buffer->width && self->pos.y >= 0 && self->pos.y < buffer->height)
		mylx_pixel_put(buffer, self->pos.x, self->pos.y, 0x00FF00);
	if (self->pos.x + actor->entity->hull.a.x >= 0 && self->pos.x + actor->entity->hull.a.x < buffer->width
		&& self->pos.y + actor->entity->hull.a.y >= 0 && self->pos.y + actor->entity->hull.a.y < buffer->height)
		mylx_pixel_put(buffer, self->pos.x + actor->entity->hull.a.x, self->pos.y + actor->entity->hull.a.y, 0x0000FF);
	if (self->pos.x + actor->entity->hull.b.x >= 0 && self->pos.x + actor->entity->hull.b.x < buffer->width
		&& self->pos.y + actor->entity->hull.b.y >= 0 && self->pos.y + actor->entity->hull.b.y < buffer->height)
		mylx_pixel_put(buffer, self->pos.x + actor->entity->hull.b.x, self->pos.y + actor->entity->hull.b.y, 0x0000FF);
}
