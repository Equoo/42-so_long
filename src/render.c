/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:10:51 by dderny            #+#    #+#             */
/*   Updated: 2025/04/22 14:37:57 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "classes/element.h"
#include "so_long.h"
#include "scene.h"
#include <mlx.h>

void	tick_render(t_gameenv *env, t_render *render)
{
	t_img		*buffer;
	t_list		*node;
	t_element	*node_elem;

	node = ((t_scene *)env->scene)->elements;
	while (node)
	{
		node_elem = (t_element *)node->content;
		if (node_elem->draw)
			node_elem->draw(node_elem, render);
		node = node->next;
	}
	if (render->r_scale)
	{
		buffer = mylx_img_scale(render->mlx, render->buffer, render->r_scale);
		render_texts(render, buffer);
		mlx_put_image_to_window(render->mlx, render->win,
				buffer, -ft_abs(buffer->width - render->w_width) / 2,
				-ft_abs(buffer->height - render->w_height) / 2);
		mlx_destroy_image(render->mlx, buffer);
		return ;
	}
	render_texts(render, render->buffer);
	mlx_put_image_to_window(render->mlx, render->win,
				render->buffer, 0, 0);
}

int	render_init(t_gameenv *env)
{
	t_render	*render;

	render = &env->render;
	render->mlx = mlx_init();
	if (!render->mlx)
		return (1);
	render->w_width = 1920;
	render->w_height = 1080;
	//mlx_get_screen_size(env.mlx, &env.width, &env.height);
	render->win = mlx_new_window(render->mlx, render->w_width,
			render->w_height, "So long");
	if (!render->win)
		return (1);
	render->r_width = 398;
	render->r_height = 224;
	render->r_scale = (int)((double)render->w_height / 224 * 1.3);
	render->buffer = mlx_new_image(render->mlx, render->r_width,
			render->r_height);
	render->font = ft_texture(render, "textures/font.xpm");
	if (!render->buffer || !render->font)
		return (1);
	render->texts = vec_new(32, sizeof(t_rtext));
	if (!render->texts.data)
		return (1);
	return (0);
}
