/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:58:57 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "vector2d.h"
#include "mlx_int.h"
#include "render.h"

void	*mylx_img_fast_copy(t_iaabb sqr, t_int2d pos, t_img *dest, t_img *src)
{
	t_int2d	i;
	void	*src_pixels;

	if (pos.x + sqr.b.x - sqr.a.x > dest->width)
		sqr.b.x = sqr.b.x - ((pos.x + sqr.b.x - sqr.a.x) - dest->width);
	if (pos.y + sqr.b.y - sqr.a.y > dest->height)
		sqr.b.y = sqr.b.y - ((pos.y + sqr.b.y - sqr.a.y) - dest->height);
	i.y = sqr.a.y;
	while (pos.y + sqr.a.y - i.y < dest->height && i.y < sqr.b.y)
	{
		if (i.y + pos.y - sqr.a.y < 0 || i.y + pos.y - sqr.a.y >= dest->height)
			break ;
		i.x = sqr.a.x;
		while (i.x < sqr.b.x)
		{
			if (i.x + pos.x - sqr.a.x < 0 || i.x + pos.x - sqr.a.x >= dest->width)
				break ;
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
