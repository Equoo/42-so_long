/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:12 by dderny            #+#    #+#             */
/*   Updated: 2025/02/05 07:54:04 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/vector2d.h"
#include "colors.h"
#include "render.h"
#include <mlx.h>

void	*mylx_img_scale(void *mlx, t_img *img, int scale)
{
	t_img			*dest;
	t_int2d			pos;
	unsigned int	pixels[M256_NPIXEL];
	unsigned int	*src_pixels;

	dest = mlx_new_image(mlx, img->width * scale, img->height * scale);
	pos.y = -1;
	while (pos.y < img->height * scale && ++pos.y + 1)
	{
		pos.x = -1;
		while (pos.x < img->width * scale && ++pos.x + 1)
		{
			if (img->width * scale - pos.x >= M256_NPIXEL && pos.x % M256_NPIXEL)
				continue ;
			src_pixels = mylx_pixel_get(img, pos.x / scale, pos.y / scale);
			if (img->width * scale - pos.x >= M256_NPIXEL)
			{
				int i = 0;
				while (i < M256_NPIXEL)
				{
					pixels[i] = src_pixels[(pos.x % scale + i) / scale];
					i++;
				}
				mylx_m256_pixel_put(dest, pos.x, pos.y, (t_m256i)(t_v8si){pixels[0], pixels[1], pixels[2], pixels[3], pixels[4], pixels[5], pixels[6], pixels[7]});
			}
			else
				mylx_pixel_put(dest, pos.x, pos.y, *src_pixels);
		}
	}
	return (dest);
}

void	*mylx_img_copy(t_iaabb sqr, t_int2d pos, t_img *dest, t_img *src)
{
	t_int2d	i;
	void	*src_pixels;

	i.y = sqr.a.y;
	while (i.y < sqr.b.y)
	{
		i.x = sqr.a.x;
		while (i.x < sqr.b.x)
		{
			if (sqr.b.x - i.x >= M256_NPIXEL && (i.x - sqr.b.x) % M256_NPIXEL
				&& ++i.x)
				continue ;
			src_pixels = mylx_pixel_get(src, i.x, i.y);
			if (sqr.b.x - i.x >= M256_NPIXEL)
				mylx_m256_pixel_put(dest, i.x + pos.x - sqr.a.x, i.y + pos.y
					- sqr.a.y, *(t_m256i_u *)src_pixels);
			else
				mylx_pixel_put(dest, i.x + pos.x - sqr.a.x, i.y + pos.y
					- sqr.a.y, *(unsigned int *)src_pixels);
			i.x++;
		}
		i.y++;
	}
	return (dest);
}

void	*mylx_img_blend(t_iaabb sqr, t_int2d pos, t_img *dest, t_img *src)
{
	t_int2d			i;
	t_m256i_u		*src_pixels;
	t_m256i_u		*dst_pixels;
	t_m256i_rgba	src_chans;
	t_m256i_rgba	dst_chans;

	i.y = sqr.a.y;
	while (i.y < sqr.b.y)
	{
		i.x = sqr.a.x / M256_NPIXEL;
		while (i.x < sqr.b.x / M256_NPIXEL)
		{
			src_pixels = mylx_m256_pixel_get(src, i.x * M256_NPIXEL, i.y);
			dst_pixels = mylx_m256_pixel_get(dest, i.x * M256_NPIXEL + pos.x
					- sqr.a.x, i.y + pos.y - sqr.a.y);
			src_chans = m256_split_channels(*src_pixels, 1);
			dst_chans = m256_split_channels(*dst_pixels, 0);
			*dst_pixels = m256_combine_channels(m256_blend_by_alpha(dst_chans,
						src_chans));
			i.x++;
		}
		i.y++;
	}
	return (dest);
}
