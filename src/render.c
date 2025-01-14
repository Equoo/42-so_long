/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:12 by dderny            #+#    #+#             */
/*   Updated: 2025/01/14 13:29:18 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <mlx.h>

void	mylx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	mylx_pixel_get(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

void	*mylx_img_scale(void *mlx, void *img, int scale)
{
	t_data	a;
	t_data	b;
	int		x;
	int		y;
	int		i;
	unsigned int color;

	a.img = img;
	a.addr = mlx_get_data_addr(a.img, &a.bpp, &a.line_length, &a.endian);
	b.img = mlx_new_image(mlx, a.img->width * scale, a.img->height * scale);
	b.addr = mlx_get_data_addr(b.img, &b.bpp, &b.line_length, &b.endian);
	y = 0;
	while (y < a.img->height)
	{
		x = 0;
		while (x < a.img->width)
		{
			color = mylx_pixel_get(&a, x, y);
			if (color == 0xFF000000 && ++x)
				continue ;
			i = 0;
			while (i < scale * scale && ++i)
				mylx_pixel_put(&b, x * scale + (i - 1) / scale, y * scale + (i
						- 1) % scale, color);
			x++;
		}
		y++;
	}
	return (b.img);
}

void	*mylx_img_add(int x, int y, void *dest, void *src)
{
	t_data	a;
	t_data	b;
	int		xi;
	int		yi;
	unsigned int color;

	a.img = dest;
	a.addr = mlx_get_data_addr(a.img, &a.bpp, &a.line_length, &a.endian);
	b.img = src;
	b.addr = mlx_get_data_addr(b.img, &b.bpp, &b.line_length, &b.endian);
	yi = 0;
	while (yi < b.img->height)
	{
		xi = 0;
		while (xi < b.img->width)
		{
			color = mylx_pixel_get(&b, xi, yi);
			if ((color == 0xFF000000 || xi + x >= a.img->width || yi + y >= a.img->height) && ++xi)
				continue ;
			mylx_pixel_put(&a, xi + x, yi + y, color);

			xi++;
		}
		yi++;
	}
	return (a.img);
}
