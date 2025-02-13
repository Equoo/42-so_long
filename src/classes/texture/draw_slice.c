/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_slice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:36:19 by dderny            #+#    #+#             */
/*   Updated: 2025/02/13 11:59:38 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/texture.h"
#include "render.h"

void	texture_draw_slice(t_texture *self, t_img *buffer, t_int2d pos, char *slice)
{
	t_frame	frame;

	frame = texture_get_frame(self, slice);
	mylx_img_copy((t_iaabb){frame.a,
		(t_int2d){frame.a.x + frame.b.x, frame.a.y + frame.b.y}},
		pos, buffer, self->img);
}

void	texture_draw_anim(t_texture *self, t_img *buffer, t_int2d pos, char *slice, double cycle)
{
	t_frame	frame;

	frame = texture_get_cycle_frame(self, slice, cycle);
	mylx_img_copy((t_iaabb){frame.a,
		(t_int2d){frame.a.x + frame.b.x, frame.a.y + frame.b.y}},
		pos, buffer, self->img);
}

void	texture_blend_slice(t_texture *self, t_img *buffer, t_int2d pos, char *slice)
{
	t_frame	frame;

	frame = texture_get_frame(self, slice);
	mylx_img_blend((t_iaabb){frame.a,
		(t_int2d){frame.a.x + frame.b.x, frame.a.y + frame.b.y}},
		pos, buffer, self->img);
}

void	texture_blend_anim(t_texture *self, t_img *buffer, t_int2d pos, char *slice, double cycle)
{
	t_frame	frame;

	frame = texture_get_cycle_frame(self, slice, cycle);
	mylx_img_blend((t_iaabb){frame.a,
		(t_int2d){frame.a.x + frame.b.x, frame.a.y + frame.b.y}},
		pos, buffer, self->img);
}
