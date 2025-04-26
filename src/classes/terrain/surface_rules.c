/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 22:50:38 by dderny            #+#    #+#             */
/*   Updated: 2025/04/26 07:35:41 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "vector2d.h"
#include "ft_bool.h"
#include "libft.h"
#include "seed.h"

t_bool	rs_corgrass(t_terrain *self, t_int2d pos, char **slice,
	t_transform *transform, int *used)
{
	const char	textures[][19] = {"corner_grass_1", "corner_grass_2"};
	int			dirs[4];
	int			dir;

	if (get_facing(self, pos, dirs) < 2)
		return (FALSE);
	dir = -1;
	while (++dir < 4)
		if (dirs[dir] && rule_platform(self,
				getposindir(pos, dir), NULL, transform))
			return (FALSE);
	if (dirs[DIR_TOP] == 1 && dirs[DIR_RIGHT] == 1)
		transform->angle = 90;
	else if (dirs[DIR_TOP] == 1 && dirs[DIR_LEFT] == 1)
		transform->angle = 180;
	else if (dirs[DIR_BOTTOM] == 1 && dirs[DIR_LEFT] == 1)
		transform->angle = -90;
	used[pos.x + pos.y * self->w] = 1;
	*slice = ft_strdup(textures[rand_int() % 2]);
	return (TRUE);
}

static void	rs_basic(char **slice, t_transform *transform, int dir)
{
	const char	textures[][19] = {"grass_1", "grass_2", "grass_3"};

	if (dir == DIR_TOP)
		transform->angle = 180;
	else if (dir == DIR_RIGHT)
		transform->angle = 90;
	else if (dir == DIR_LEFT)
		transform->angle = -90;
	*slice = ft_strdup(textures[rand_int() % 3]);
}

static t_bool	rs_falling(t_terrain *self, char **slice, t_int2d pos, int *used)
{
	const t_prob	textures[] = {(t_prob){16, "moss"},
		(t_prob){12, "moss_flower_2"},
		(t_prob){10, "moss_flower_1"},
		(t_prob){16, "moss_flower_3"}};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (rand_int() % textures[i].ratio == 0)
		{
			*slice = ft_strdup(textures[i].slice);
			break ;
		}
		i++;
	}
	if (!*slice)
		return (FALSE);
	used[pos.x + pos.y * self->w] = 1;
	return (TRUE);
}

static t_bool	rs_ground(t_terrain *self, char **slice, t_int2d pos, int *used)
{
	const t_prob	textures[] = {(t_prob){16, "bush"},
		(t_prob){16, "flower_1"},
		(t_prob){16, "flower_2"},
		(t_prob){16, "flower_3"},
		(t_prob){16, "flower_4"},
		(t_prob){50, "large_bush"},
		(t_prob){32, "rock"},
		(t_prob){50, "big_rock"},
		(t_prob){50, "tree"},
		(t_prob){100, "big_tree"}};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (rand_int() % textures[i].ratio == 0)
		{
			*slice = ft_strdup(textures[i].slice);
			break ;
		}
		i++;
	}
	if (!*slice)
		return (FALSE);
	used[pos.x + pos.y * self->w] = 1;
	return (TRUE);
}

t_bool	rs_grass(t_terrain *self, t_int2d pos, char **slice,
		t_transform *transform, int *used)
{
	int			dirs[4];
	int			dir;

	if (get_facing(self, pos, dirs) < 1)
		return (FALSE);
	dir = -1;
	while (++dir < 4)
		if (dirs[dir] && !rule_platform(self,
				getposindir(pos, dir), NULL, transform))
			break ;
	if (dir == 4)
		return (FALSE);
	if (dir == DIR_BOTTOM && rs_ground(self, slice, pos, used))
		return (TRUE);
	if (dir == DIR_TOP && rs_falling(self, slice, pos, used))
		return (TRUE);
	else
		rs_basic(slice, transform, dir);
	used[pos.x + pos.y * self->w] = 1;
	return (TRUE);
}
