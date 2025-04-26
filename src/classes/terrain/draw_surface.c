/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_surface.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:52:11 by dderny            #+#    #+#             */
/*   Updated: 2025/04/27 00:53:00 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "libft.h"
#include "render.h"
#include "vector2d.h"
#include <X11/X.h>
#include <errno.h>
#include <stdlib.h>

static char	*get_surface_text(t_terrain *self, t_int2d *pos,
		const t_srule rules[2], t_rule_data data)
{
	char	*tex;
	int		i;

	i = -1;
	tex = NULL;
	while (++i < 2)
		if (rules[i](self, pos, &tex, data))
			break ;
	return (tex);
}

static void	ground_surface_one(t_terrain *self, t_render *render,
		t_2int2d off_pos, int *used)
{
	const t_srule	rules[] = {&rs_corgrass, &rs_other};
	t_transform		transform;
	char			*tex;

	if (used[off_pos.b.x + off_pos.b.y * self->w])
		return ;
	transform = (t_transform){.scale = {1, 1}};
	tex = get_surface_text(self, &off_pos.b, rules, (t_rule_data){&transform,
			used});
	if (errno)
		return ;
	transform.pos = (t_int2d){off_pos.a.x + off_pos.b.x * 16, off_pos.a.y
		+ off_pos.b.y * 16};
	if (tex && !*tex)
	{
		free(tex);
		return ;
	}
	if (!tex || !*tex)
		return ;
	texture_blend_slice(self->base->texture, render->buffer, transform, tex);
	free(tex);
}

void	ground_surface(t_terrain *self, t_render *render, t_int2d offset)
{
	int		i;
	int		j;
	t_int2d	origin;
	int		*used;

	used = ft_calloc(self->w * self->h, sizeof(int));
	if (!used)
		return ;
	i = -1;
	while (!errno && ++i + 1 && self->grid[i])
	{
		if (self->grid[i] != MAP_WALL)
			continue ;
		j = -1;
		while (!errno && ++j < 4)
		{
			origin = (t_int2d){i % self->w, i / self->w};
			if (getindir(self, origin, j) != MAP_WALL)
				ground_surface_one(self, render, (t_2int2d){offset,
					getposindir(origin, j)}, used);
		}
	}
	free(used);
}
