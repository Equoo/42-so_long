/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:17:11 by dderny            #+#    #+#             */
/*   Updated: 2025/04/25 22:40:42 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "libft.h"
#include "render.h"
#include "seed.h"
#include "vector2d.h"

void	hover_ground_gen(t_terrain *self, t_render *render, t_int2d offset)
{
	const char	ground_slices[][64] = {"ground_mid_moss", "ground_mid_green_2",
		"ground_mid_green_3", "ground_mid_green_4", "ground_mid_red",
		"ground_mid_moss"};
	t_int2d		pos;
	char		*tex;
	int			i;

	i = -1;
	while (++i + 1 && self->grid[i])
	{
		if (self->grid[i] != MAP_WALL || rand_int() % 8 != 0)
			continue ;
		pos = (t_int2d){i % self->w, i / self->w};
		if (getindir(self, pos, DIR_TOP) == MAP_WALL && getindir(self, pos,
				DIR_BOTTOM) == MAP_WALL && getindir(self, pos,
				DIR_LEFT) == MAP_WALL && getindir(self, pos,
				DIR_RIGHT) == MAP_WALL)
			tex = (char *)ground_slices[rand_int() % 6];
		else
			continue ;
		texture_draw_slice(self->base->texture, render->buffer,
			(t_transform){{offset.x + pos.x * 16, offset.y + pos.y * 16}, {0},
			0}, tex);
	}
}

void	ground_gen(t_terrain *self, t_render *render, t_int2d offset)
{
	const t_frule	rules[] = {&rule_topgrass, &rule_corgrass, &rule_platform};
	t_int2d			pos;
	t_transform		transform;
	char			*tex;
	t_int2d			i;

	i.x = -1;
	while (++i.x + 1 && self->grid[i.x])
	{
		if (self->grid[i.x] != MAP_WALL)
			continue ;
		pos = (t_int2d){i.x % self->w, i.x / self->w};
		tex = NULL;
		transform = t_from_pos((t_int2d){offset.x + pos.x * 16, offset.y + pos.y
				* 16});
		i.y = -1;
		while (++i.y < 3)
			if (rules[i.y](self, pos, &tex, &transform))
				break ;
		if (i.y == 3)
			tex = "ground";
		texture_blend_slice(self->base->texture, render->buffer, transform,
			tex);
	}
}

void	terrain_draw(t_element *self_e, t_render *render)
{
	t_terrain	*self;
	t_int2d		offset;

	self = (t_terrain *)self_e->parent;
	offset = to_int2d(float2d_scaled(self_e->scene->cam_pos, -1));
	ground_gen(self, render, offset);
	hover_ground_gen(self, render, offset);
}
