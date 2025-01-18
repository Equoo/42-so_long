/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:12 by dderny            #+#    #+#             */
/*   Updated: 2025/01/18 00:05:49 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/vector2d.h"
#include "render.h"
#include "colors.h"
#include <mlx.h>

#define NPIXELS (sizeof(__m256i_u) / 4)

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

	a.img = img;
	a.addr = mlx_get_data_addr(a.img, &a.bpp, &a.line_length, &a.endian);
	b.img = mlx_new_image(mlx, a.img->width * scale, a.img->height * scale);
	b.addr = mlx_get_data_addr(b.img, &b.bpp, &b.line_length, &b.endian);
	y = 0;
	unsigned int src_pixels;
	char	*dst;
	while (y < a.img->height)
	{
		x = 0;
		while (x < a.img->width)
		{
			src_pixels = *(unsigned int *)(a.addr + (y * a.line_length + x * (a.bpp / 8)));
			i = 0;
			while (i < (int)(scale / NPIXELS * scale))
			{
				dst = b.addr + ((y * scale + i / (scale / NPIXELS)) * b.line_length + (x * scale + ((i % (scale / NPIXELS)) / NPIXELS)) * (b.bpp / 8));
				*(__m256i_u *)dst = ft_mm256_set1(src_pixels);
				i++;
			}
			x++;
		}
		y++;
	}
	return (b.img);
}

void	*mylx_img_addn(int x, int y, void *dest, void *src)
{
	t_data	a;
	t_data	b;

	a.img = dest;
	a.addr = mlx_get_data_addr(a.img, &a.bpp, &a.line_length, &a.endian);
	b.img = src;
	b.addr = mlx_get_data_addr(b.img, &b.bpp, &b.line_length, &b.endian);
	
	int		xi;
	int		yi;
	__m256i_u src_pixels;
	char	*dst;
	yi = 0;
	while (yi < b.img->height)
	{
		xi = 0;
		while ((unsigned long)xi < b.img->width / NPIXELS)
		{
			src_pixels = *(__m256i_u *)(b.addr + (yi * b.line_length + xi * NPIXELS * (b.bpp / 8)));
			dst = a.addr + ((yi + y) * a.line_length + (xi * NPIXELS + x) * (a.bpp / 8));
			
			*(__m256i_u *)dst = src_pixels;

			xi++;
		}
		yi++;
	}
	return (a.img);
}

void	*mylx_img_add(t_iaabb sqr, t_int2d pos, void *dest, void *src)
{
	t_data	a;
	t_data	b;

	a.img = dest;
	a.addr = mlx_get_data_addr(a.img, &a.bpp, &a.line_length, &a.endian);
	b.img = src;
	b.addr = mlx_get_data_addr(b.img, &b.bpp, &b.line_length, &b.endian);
	t_int2d	i;
	__m256i_u src_pixels;
	__m256i_u *dst_pixels;
	t_m256i_rgba src_chans;
	t_m256i_rgba dst_chans;
	i.y = sqr.a.y;
	while (i.y < sqr.b.y)
	{
		i.x = sqr.a.x / NPIXELS;
		while ((unsigned long)i.x < sqr.b.x / NPIXELS)
		{
			src_pixels = *(__m256i_u *)(b.addr + (i.y * b.line_length + i.x * NPIXELS * (b.bpp / 8)));
			dst_pixels = (__m256i_u *)(a.addr + ((i.y + pos.y - sqr.a.y) * a.line_length + (i.x * NPIXELS - sqr.a.x + pos.x) * (a.bpp / 8)));
			src_chans = m256_split_channels(src_pixels, 1);
			dst_chans = m256_split_channels(*dst_pixels, 0);
			*dst_pixels = m256_combine_channels(m256_blend_by_alpha(dst_chans, src_chans));
			i.x++;
		}
		i.y++;
	}
	return (a.img);
}
