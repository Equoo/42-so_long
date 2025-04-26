/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:17:11 by dderny            #+#    #+#             */
/*   Updated: 2025/04/26 22:02:32 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "libft.h"
#include "render.h"
#include "seed.h"
#include "vector2d.h"
#include <X11/X.h>
#include <errno.h>
#include <stdlib.h>

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

static char	*get_text(t_terrain *self, t_int2d pos,
		const t_frule rules[3], t_transform *transform)
{
	char	*tex;
	int		i;

	i = -1;
	tex = NULL;
	while (++i < 3)
		if (rules[i](self, pos, &tex, transform))
			break ;
	if (i == 3)
		tex = ft_strdup("ground");
	return (tex);
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
		transform = t_from_pos((t_int2d){offset.x + pos.x * 16, offset.y + pos.y
				* 16});
		tex = get_text(self, pos, rules, &transform);
		if (!tex)
			return ;
		texture_blend_slice(self->base->texture, render->buffer, transform,
			tex);
		free(tex);
	}
}

static char	*get_surface_text(t_terrain *self, t_int2d *pos,
	const t_srule rules[2], t_transform *transform, int *used)
{
	char	*tex;
	int		i;

	i = -1;
	tex = NULL;
	while (++i < 2)
		if (rules[i](self, pos, &tex, transform, used))
			break ;
	return (tex);
}

void	ground_surface(t_terrain *self, t_render *render, t_int2d offset)
{
	const t_srule	rules[] = {&rs_corgrass, &rs_other};
	t_int2d			origin;
	t_int2d			pos;
	t_transform		transform;
	t_int2d			i;
	char			*tex;

	int		*used = ft_calloc(self->w * self->h, sizeof(int));
	if (!used)
		return ;
	i.x = -1;
	while (++i.x + 1 && self->grid[i.x])
	{
		if (self->grid[i.x] != MAP_WALL)
			continue ;
		origin = (t_int2d){i.x % self->w, i.x / self->w};
		i.y = -1;
		while (++i.y < 4)
		{
			if (getindir(self, origin, i.y) == MAP_WALL)
				continue ;
			pos = getposindir(origin, i.y);
			if (used[pos.x + pos.y * self->w])
				continue ;
			transform = (t_transform){.scale = {1, 1}};
			tex = get_surface_text(self, &pos, rules, &transform, used);
			if (errno)
				return ;
			transform.pos = (t_int2d){offset.x + pos.x * 16, offset.y + pos.y
				* 16};
			if (tex && !*tex)
			{
				free(tex);
				continue ;
			}
			if (!tex || !*tex)
				continue ;
			texture_blend_slice(self->base->texture, render->buffer, transform,
				tex);
			free(tex);
		}
	}
	free(used);
}

void	terrain_draw(t_element *self_e, t_render *render)
{
	t_terrain	*self;
	t_int2d		offset;

	self = (t_terrain *)self_e->parent;
	offset = to_int2d(float2d_scaled(self_e->scene->cam_pos, -1));
	ground_surface(self, render, offset);
	ground_gen(self, render, offset);
	hover_ground_gen(self, render, offset);
}
