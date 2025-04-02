/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 03:15:23 by dderny            #+#    #+#             */
/*   Updated: 2025/04/02 19:21:13 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "classes/element.h"
#include "render.h"
#include "texture.h"
#include "vector2d.h"
#include "so_long.h"
#include "classes/background.h"

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
	return (init_background(scene, background));
}

void	background_draw(t_element *self_element, t_render *buffer)
{
	t_background	*background;

	background = (t_background *)self_element->parent;
	texture_draw_slice(self_element->texture, buffer->buffer,
			t_from_pos((t_int2d){0, 16}), "all");
	texture_blend_slice(background->back_1, buffer->buffer,
			t_from_pos((t_int2d){0, 16 * 9}), "all");
	texture_blend_slice(background->back_2, buffer->buffer,
			t_from_pos((t_int2d){0, 16 * 9 + 8}), "all");

	texture_draw_slice(self_element->texture, buffer->buffer,
			t_from_pos((t_int2d){288, 16}), "all");
	texture_blend_slice(background->back_1, buffer->buffer,
			t_from_pos((t_int2d){288, 16 * 9}), "all");
	texture_blend_slice(background->back_2, buffer->buffer,
			t_from_pos((t_int2d){288, 16 * 9 + 8}), "all");
}
