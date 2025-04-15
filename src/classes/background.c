/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 03:15:23 by dderny            #+#    #+#             */
/*   Updated: 2025/04/16 00:43:01 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "classes/element.h"
#include "render.h"
#include "texture.h"
#include "vector2d.h"
#include "so_long.h"
#include "classes/background.h"
#include <math.h>

void	background_del(t_element **self)
{
	t_background	*background;

	background = (t_background *)(*self)->parent;
	element_del(self);
	if (background)
		free(background);
}

static void	*init_background(t_scene *scene, t_background *background)
{
	t_render	*render;

	render = &scene->env->render;
	background->base->class = CLASS_BACKGROUND;
	background->base->del = &background_del;
	background->base->draw = &background_draw;
	background->base->texture = ft_texture(render, "./textures/background0.xpm");
	if (background->base->texture)
		background->back_1 = ft_texture(render, "./textures/background1.xpm");
	if (background->back_1)
		background->back_2 = ft_texture(render, "./textures/background2.xpm");
	if (!background->base->texture || !background->back_1
		|| !background->back_2)
	{
		background->base->del(&background->base);
		return (NULL);
	}
	return (background);
}

t_background	*ft_background(t_scene *scene)
{
	t_element		*base;
	t_background	*background;

	base = ft_element(scene);
	if (!base)
		return (NULL);
	background = (t_background *)ft_calloc(1, sizeof(t_background));
	if (!background)
	{
		base->del(&base);
		return (NULL);
	}
	background->base = base;
	background->base->parent = background;
	background->base->internal_update = NULL;
	return (init_background(scene, background));
}

void	background_draw(t_element *self_element, t_render *buffer)
{
	t_background	*background;
	int				offset;
	int				offsety;
	int				offset2;
	int				offset3;

	background = (t_background *)self_element->parent;
	offsety = (double)self_element->scene->cam_pos.y / 16;
	offset = (double)((int)((double)self_element->scene->cam_pos.x / 8) % 288);
	offset2 = (double)((int)((double)self_element->scene->cam_pos.x / 4) % 288);
	offset3 = (double)((int)((double)self_element->scene->cam_pos.x / 2) % 288);
	//texture_draw_slice(self_element->texture, buffer->buffer,
	//		t_from_pos((t_int2d){-offset, 0}), "all");
	//texture_draw_slice(self_element->texture, buffer->buffer,
	//		t_from_pos((t_int2d){288 - offset, 0}), "all");
	texture_blend_slice(self_element->texture, buffer->buffer,
		t_from_pos((t_int2d){-offset, 0}), "all");
	texture_blend_slice(self_element->texture, buffer->buffer,
			t_from_pos((t_int2d){288 - offset, 0}), "all");
	texture_blend_slice(background->back_1, buffer->buffer,
			t_from_pos((t_int2d){-offset2, 16 * 6 - offsety / 2 + 8}), "all");
	texture_blend_slice(background->back_1, buffer->buffer,
			t_from_pos((t_int2d){288 - offset2, 16 * 6 - offsety / 2 + 8}), "all");
	texture_blend_slice(background->back_2, buffer->buffer,
			t_from_pos((t_int2d){-offset3, 16 * 7 + 8 - offsety}), "all");
	texture_blend_slice(background->back_2, buffer->buffer,
			t_from_pos((t_int2d){288 - offset3, 16 * 7 + 8 - offsety}), "all");
}
