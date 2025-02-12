/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:17:11 by dderny            #+#    #+#             */
/*   Updated: 2025/02/12 20:24:42 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "seed.h"

void	terrain_draw(t_element *self_element, t_img *buffer)
{
	const char 	top_ground_slices[][64] = {"ground_top_green_1", "ground_top_green_2"};
	const char 	ground_slices[][64] = {"ground_mid_moss", "ground"};
	t_terrain	*self;
	int			i;
	t_int2d		pos;
	char		*tex;

	self = (t_terrain *)self_element->parent;
	i = -1;
	while (++i + 1 && self->grid[i])
	{
		if (self->grid[i] != MAP_WALL)
			continue;
		pos = (t_int2d){i % self->w, i / self->w};
		
		if (pos.y > 0 && self->grid[i - self->w] != MAP_WALL)
			tex = (char *)top_ground_slices[rand_int() % 2];
		else
			tex = (char *)ground_slices[rand_int() % 2];

		texture_draw_slice(self->texture, buffer,
			(t_int2d){pos.x * 16, pos.y * 16}, tex);
	}
}
