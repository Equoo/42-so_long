/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:32:57 by dderny            #+#    #+#             */
/*   Updated: 2025/04/26 03:36:56 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/element.h"

void	element_draw(t_element *self, t_render *render)
{
	t_transform	transform;

	transform = t_from_pos(to_int2d(float2d_sub(float2d_add(self->pos,
						self->txt_off_pos), self->scene->cam_pos)));
	if (self->anim)
		texture_blend_anim(self->texture, render->buffer, transform,
			(t_anim_sl){self->anim, self->cycle});
}
