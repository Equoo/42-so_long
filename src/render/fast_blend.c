/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_blend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:56:53 by dderny            #+#    #+#             */
/*   Updated: 2025/04/02 19:17:12 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "vector2d.h"
#include "colors.h"
#include "mlx_int.h"
#include "render.h"

void	*mylx_img_fast_blend(t_iaabb sqr, t_int2d pos, t_img *dest, t_img *src)
{
	t_int2d			i;
	__m256i_u		*src_pixels;
	__m256i_u		*dst_pixels;
	t_m256i_rgba	src_chans;
	t_m256i_rgba	dst_chans;

	if (pos.x + sqr.b.x - sqr.a.x > dest->width)
		sqr.b.x = sqr.b.x - ((pos.x + sqr.b.x - sqr.a.x) - dest->width);
	i.y = sqr.a.y;
	while (i.y < sqr.b.y && i.y + pos.y - sqr.a.y < dest->height && i.y + pos.y - sqr.a.y >= 0)
	{
		i.x = sqr.a.x / M256_NPIXEL;
		while (i.x < sqr.b.x / M256_NPIXEL && i.x * M256_NPIXEL + pos.x
			- sqr.a.x < dest->width && i.x * M256_NPIXEL + pos.x
			- sqr.a.x >= 0)
		{
			src_pixels = mylx_m256_pixel_get(src, i.x * M256_NPIXEL, i.y);
			dst_pixels = mylx_m256_pixel_get(dest, i.x++ * M256_NPIXEL + pos.x
					- sqr.a.x, i.y + pos.y - sqr.a.y);
			src_chans = m256_split_channels(*src_pixels, 1);
			dst_chans = m256_split_channels(*dst_pixels, 0);
			*dst_pixels = m256_combine_channels(m256_blend_by_alpha(dst_chans,
						src_chans));
		}
		i.y++;
	}
	return (dest);
}
