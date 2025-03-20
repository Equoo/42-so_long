/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:58:57 by dderny            #+#    #+#             */
/*   Updated: 2025/03/20 01:03:20 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "classes/vector2d.h"
#include "mlx_int.h"
#include "render.h"

void	*mylx_img_fast_copy(t_iaabb sqr, t_int2d pos, t_img *dest, t_img *src)
{
	t_int2d	i;
	void	*src_pixels;

	if (pos.x + sqr.b.x - sqr.a.x > dest->width)
		sqr.b.x = sqr.b.x - ((pos.x + sqr.b.x - sqr.a.x) - dest->width);
	i.y = sqr.a.y;
	while (pos.y + sqr.a.y - i.y < dest->height && i.y < sqr.b.y)
	{
		i.x = sqr.a.x;
		while (i.x < sqr.b.x)
		{
			src_pixels = mylx_pixel_get(src, i.x, i.y);
			if (sqr.b.x - i.x >= M256_NPIXEL)
			{
				mylx_m256_pixel_put(dest, i.x + pos.x - sqr.a.x, i.y + pos.y
					- sqr.a.y, *(__m256i_u *)src_pixels);
				i.x += M256_NPIXEL - 1;
			}
			else
				mylx_pixel_put(dest, i.x + pos.x - sqr.a.x, i.y + pos.y
					- sqr.a.y, *(unsigned int *)src_pixels);
			i.x++;
		}
		i.y++;
	}
	return (dest);
}
