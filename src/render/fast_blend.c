/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_blend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:56:53 by dderny            #+#    #+#             */
/*   Updated: 2025/04/08 16:31:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "mlx_int.h"
#include "render.h"
#include "vector2d.h"
#include <mlx.h>

static void	blend_m256_block(t_img *dest, t_img *src, t_int2d pos, t_int2d i,
		t_iaabb sqr)
{
	__m256i_u		*src_pixels;
	__m256i_u		*dst_pixels;
	t_m256i_rgba	src_chans;
	t_m256i_rgba	dst_chans;

	src_pixels = mylx_m256_pixel_get(src, i.x * M256_NPIXEL, i.y);
	if (!src_pixels)
		return ;
	dst_pixels = mylx_m256_pixel_get(dest, i.x * M256_NPIXEL + pos.x - sqr.a.x,
			i.y + pos.y - sqr.a.y);
	src_chans = m256_split_channels(*src_pixels, 1);
	dst_chans = m256_split_channels(*dst_pixels, 0);
	*dst_pixels = m256_combine_channels(m256_blend_by_alpha(dst_chans,
				src_chans));
}

static void	blend_scalar_pixel(t_img *dest, t_img *src_img, t_int2d pos,
		t_int2d i, t_iaabb sqr)
{
	u_int	src;
	u_int	dst;
	u_int	result;
	u_int	dst_x;
	u_int	dst_y;

	dst_x = i.x + pos.x - sqr.a.x;
	dst_y = i.y + pos.y - sqr.a.y;
	src = *mylx_pixel_get(src_img, i.x, i.y);
	if (!src)
		return ;
	dst = *mylx_pixel_get(dest, dst_x, dst_y);
	result = combine_channels(blend_by_alpha(split_channels(dst, 0),
				split_channels(src, 1)));
	mylx_pixel_put(dest, dst_x, dst_y, result);
}

static void	process_scanline(t_img *dest, t_img *src, t_int2d pos, t_iaabb sqr,
		t_int2d i)
{
	int	m256_end;

	m256_end = sqr.b.x / M256_NPIXEL;
	i.x = sqr.a.x / M256_NPIXEL;
	while (i.x < m256_end)
	{
		if (i.x * M256_NPIXEL + pos.x - sqr.a.x >= 0 && i.x * M256_NPIXEL
			+ pos.x - sqr.a.x < dest->width)
			blend_m256_block(dest, src, pos, i, sqr);
		i.x++;
	}
	i.x *= M256_NPIXEL;
	while (i.x < sqr.b.x)
	{
		if (i.x + pos.x - sqr.a.x >= 0 && i.x + pos.x - sqr.a.x < dest->width)
			blend_scalar_pixel(dest, src, pos, i, sqr);
		i.x++;
	}
}

void	*mylx_img_fast_blend(t_iaabb sqr, t_int2d pos, t_img *dest, t_img *src)
{
	t_int2d	i;

	if (pos.x + sqr.b.x - sqr.a.x > dest->width)
		sqr.b.x -= (pos.x + sqr.b.x - sqr.a.x - dest->width);
	if (pos.y + sqr.b.y - sqr.a.y > dest->height)
		sqr.b.y -= (pos.y + sqr.b.y - sqr.a.y - dest->height);
	i.y = sqr.a.y;
	while (i.y < sqr.b.y)
	{
		if (i.y + pos.y - sqr.a.y >= 0 && i.y + pos.y - sqr.a.y < dest->height)
			process_scanline(dest, src, pos, sqr, i);
		i.y++;
	}
	return (dest);
}
