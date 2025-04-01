/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:36:52 by dderny            #+#    #+#             */
/*   Updated: 2025/04/01 21:06:16 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/texture.h"
#include "classes/vector2d.h"
#include "libft.h"
#include <stddef.h>

void	draw_text(void *mlx, t_img *buffer, char *text, t_float2d pos, int font_size)
{
	size_t		len;
	char		slice_char[16];
	t_transform	transfo;
	size_t		i;

	if (buffer->format)
	pos = float2d_scaled(float2d_sub(pos, (t_float2d){8, 8}), buffer->format);
	len = ft_itoato(font_size, slice_char);
	slice_char[len] = '_';
	i = 0;
	transfo = t_from_pos(to_int2d(pos));
	while (text[i])
	{
		ft_memcpy(slice_char + len + 1, text + i, 1);
		slice_char[len + 2] = 0;
		__builtin_printf("Slice: %s\n", slice_char);
		transfo.pos.x += font_size;
		texture_blend_slice(ft_texture("textures/font.xpm", mlx), buffer, transfo, slice_char);
		i++;
	}
}
