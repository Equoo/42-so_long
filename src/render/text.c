/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:36:52 by dderny            #+#    #+#             */
/*   Updated: 2025/04/15 01:27:29 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_vector.h"
#include "texture.h"
#include "vector2d.h"
#include "libft.h"
#include "render.h"
#include <stddef.h>

void	draw_text(t_render *render, char *text, t_float2d pos, int font_size)
{
	t_rtext		data;

	data = (t_rtext){0};
	data.text = text;
	data.pos = to_int2d(pos);
	data.font_size = font_size;
	vec_append(&render->texts, &data); // need to be secured
}

void	render_one_text(t_render *render, t_img *buffer, t_rtext *data)
{
	size_t		len;
	char		slice_char[16];
	t_transform	transfo;
	size_t		i;

	if (!data || !data->font_size)
		return ;
	if (render->r_scale)
		data->pos = int2d_scaled(data->pos, render->r_scale);
	len = ft_itoato(data->font_size, slice_char);
	slice_char[len] = '_';
	i = 0;
	transfo = t_from_pos(data->pos);
	while (data->text[i])
	{
		ft_memcpy(slice_char + len + 1, data->text + i, 1);
		slice_char[len + 2] = 0;
		transfo.pos.x += data->font_size / 2;
		texture_blend_slice(render->font, buffer, transfo, slice_char);
		i++;
	}
}

void	render_texts(t_render *render, t_img *buffer)
{
	t_rtext	*data;
	int		i;

	if (!render->texts.actual_size)
		return ;
	data = (t_rtext *)render->texts.data;
	i = 0;
	__builtin_printf("rendering %zu texts\n", render->texts.actual_size);
	while (i < render->texts.actual_size)
	{
		render_one_text(render, buffer, data + i);
		i++;
	}
	ft_bzero(render->texts.data, render->texts.actual_size * render->texts.type_size);
	render->texts.actual_size = 0;
}
