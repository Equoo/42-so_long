/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:17:11 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "render.h"
#include "vector2d.h"
#include "libft.h"
#include "seed.h"

typedef struct s_prob {
	double	ratio;
	char	*type;
}	t_prob;

void	terrain_draw(t_element *self_e, t_render *render)
{
	const t_frule	rules[] = {&rule_top_grass, &rule_corner_grass, &rule_platform};
	t_terrain	*self;
	int			i;
	int			j;
	t_transform transform;
	t_int2d		pos;
	t_int2d		offset;
	char		*tex;

	offset = to_int2d(float2d_scaled(self_e->scene->cam_pos, -1));

	self = (t_terrain *)self_e->parent;
	i = -1;
	while (++i + 1 && self->grid[i])
	{
		if (self->grid[i] != MAP_WALL)
			continue;
		pos = (t_int2d){i % self->w, i / self->w};
		tex = NULL;

		j = 0;
		transform = t_from_pos((t_int2d){offset.x + pos.x * 16, offset.y + pos.y * 16});
		while (j < 3)
		{
			if (rules[j](self, pos, &tex, &transform))
				break;
			j++;
		}
		if (j == 3)
			tex = ft_strdup("ground");
		if (!tex)
			return ;
		texture_blend_slice(self->base->texture, render->buffer, transform, tex);
		free(tex);
	}

	const char 	ground_slices[][64] = {"ground_mid_moss", "ground_mid_green_2", "ground_mid_green_3", "ground_mid_green_4", "ground_mid_red", "ground_mid_moss"};
	i = -1;
	while (++i + 1 && self->grid[i])
	{
		if (self->grid[i] != MAP_WALL || rand_int() % 8 != 0)
			continue;
		pos = (t_int2d){i % self->w, i / self->w};

		if (getindir(self, pos, DIR_TOP) == MAP_WALL
			&& getindir(self, pos, DIR_BOTTOM) == MAP_WALL
			&& getindir(self, pos, DIR_LEFT) == MAP_WALL
			&& getindir(self, pos, DIR_RIGHT) == MAP_WALL)
			tex = (char *)ground_slices[rand_int() % 6];
		else
			continue;

		texture_draw_slice(self->base->texture, render->buffer, (t_transform){
			{offset.x + pos.x * 16, offset.y + pos.y * 16}, {0}, 0}, tex);
	}
}
