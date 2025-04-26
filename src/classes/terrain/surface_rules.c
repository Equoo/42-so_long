/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 22:50:38 by dderny            #+#    #+#             */
/*   Updated: 2025/04/26 22:03:48 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "collisions.h"
#include "vector2d.h"
#include "ft_bool.h"
#include "libft.h"
#include "seed.h"

static int	get_random(t_prob *table, int size)
{
	int		i;
	int		rate_total;
	int		rand;

	i = 0;
	rate_total = 0;
	while (i < size)
	{
		rate_total += table[i].rate;
		i++;
	}
	i = 0;
	if (rate_total == 0)
		return (-1);
	rand = rand_int() % rate_total;
	while (i < size)
	{
		if (rand < table[i].rate)
			return (i);
		rand -= table[i].rate;
		i++;
	}
	return (-1);
}

static t_bool	check_space(t_terrain *self, t_int2d pos, t_int2d size, int *used)
{
	int		i;
	int		j;
	int		index;

	i = -1;
	while (++i < size.x)
	{
		j = -1;
		while (++j < ft_fabs(size.y))
		{
			index = (pos.x + i) + (pos.y + j * (int)getsign(size.y)) * self->w;
			if (used[index] || self->grid[index] == MAP_WALL)
				return (FALSE);
		}
		if (self->grid[(pos.x + i) + (pos.y - 1 * (int)getsign(size.y)) * self->w]
				!= MAP_WALL)
			return (FALSE);
	}
	return (TRUE);
}

t_bool	rs_corgrass(t_terrain *self, t_int2d *pos, char **slice,
	t_transform *transform, int *used)
{
	const char	textures[][19] = {"corner_grass_1", "corner_grass_2"};
	int			dirs[4];
	int			dir;

	if (get_facing(self, *pos, dirs) < 2)
		return (FALSE);
	dir = -1;
	while (++dir < 4)
		if (dirs[dir] && rule_platform(self,
				getposindir(*pos, dir), NULL, transform))
			return (FALSE);
	if (dirs[DIR_TOP] == 1 && dirs[DIR_RIGHT] == 1)
		transform->angle = 90;
	else if (dirs[DIR_TOP] == 1 && dirs[DIR_LEFT] == 1)
		transform->angle = 180;
	else if (dirs[DIR_BOTTOM] == 1 && dirs[DIR_LEFT] == 1)
		transform->angle = -90;
	used[pos->x + pos->y * self->w] = 1;
	*slice = ft_strdup(textures[rand_int() % 2]);
	return (TRUE);
}

static void	rs_basic(char **slice, t_transform *transform, int dir)
{
	const char	textures[][19] = {"grass_1", "grass_2", "grass_3"};

	if (*slice)
		free(*slice);
	if (dir == DIR_TOP)
		transform->angle = 180;
	else if (dir == DIR_RIGHT)
		transform->angle = 90;
	else if (dir == DIR_LEFT)
		transform->angle = -90;
	*slice = ft_strdup(textures[rand_int() % 3]);
}

static t_bool	rs_falling(t_terrain *self, char **slice, t_int2d *pos, int *used)
{
	t_prob	textures[] = {(t_prob){5, {{1, 1}, {1, 1}}, "moss"},
		(t_prob){15, {{1, 3}, {1, 3}}, "moss_flower_2"},
		(t_prob){20, {{1, 1}, {1, 1}}, "moss_flower_1"},
		(t_prob){10, {{1, 4}, {1, 4}}, "moss_flower_3"},
		(t_prob){30, {{1, 1}, {1, 1}}, ""}};
	int			i;
	int			res;

	i = -1;
	while (++i < 5)
		if (!check_space(self, *pos, textures[i].size.a, used))
			textures[i].rate = 0;
	res = get_random(textures, 5);
	if (res == -1)
		return (FALSE);
	*slice = ft_strdup(textures[res].slice);
	if (!*slice)
		return (FALSE);
	i = 0;
	while (++i < textures[res].size.b.x * textures[res].size.b.y)
		used[(pos->x + i % textures[res].size.b.x)
			+ (pos->y + i / textures[res].size.b.x) * self->w] = 1;
	return (TRUE);
}

static t_bool	rs_ground(t_terrain *self, char **slice, t_int2d *pos, int *used)
{
	t_prob	textures[] = {(t_prob){100, {{4, 4}, {2, 4}}, "tree"},
		(t_prob){400, {{8, 9}, {4, 9}}, "big_tree"},
		(t_prob){40, {{5, 2}, {5, 2}}, "large_bush"},
		(t_prob){25, {{3, 2}, {3, 2}}, "bush"},
		(t_prob){10, {{1, 1}, {1, 1}}, "rock"},
		(t_prob){18, {{3, 2}, {3, 2}}, "big_rock"},
		(t_prob){10, {{1, 1}, {1, 1}}, "flower_1"},
		(t_prob){10, {{1, 1}, {1, 1}}, "flower_2"},
		(t_prob){10, {{1, 1}, {1, 1}}, "flower_3"},
		(t_prob){10, {{1, 1}, {1, 1}}, "flower_4"},
		(t_prob){100, {{1, 1}, {1, 1}}, ""}};
	int			i;
	int			res;
	int			space;

	i = -1;
	while (++i < 11)
		if (!check_space(self, *pos, int2d_multiply(textures[i].size.a, (t_int2d){1, -1}), used))
			textures[i].rate = 0;
	res = get_random(textures, 11);
	if (res == -1)
		return (FALSE);
	*slice = ft_strdup(textures[res].slice);
	if (!*slice)
		return (FALSE);
	i = 0;
	space = (textures[res].size.a.x - textures[res].size.b.x) / 2;
	while (++i < textures[res].size.b.x * textures[res].size.b.y)
		used[(pos->x + space + i % textures[res].size.b.x)
			+ (pos->y + i / textures[res].size.b.x * -1) * self->w] = 1;
	pos->y -= textures[res].size.b.y - 1;
	return (TRUE);
}

t_bool	rs_other(t_terrain *self, t_int2d *pos, char **slice,
		t_transform *transform, int *used)
{
	int			dirs[4];
	int			dir;
	t_int2d		lastpos;

	if (get_facing(self, *pos, dirs) < 1)
		return (FALSE);
	dir = -1;
	while (++dir < 4)
		if (dirs[dir] && !rule_platform(self,
				getposindir(*pos, dir), NULL, NULL))
			break ;
	if (dir == 4)
		return (FALSE);
	if (rand_int() % 2)
		transform->scale.x = -1;
	lastpos = *pos;
	if (dir == DIR_BOTTOM && rs_ground(self, slice, pos, used) && **slice)
		return (TRUE);
	*pos = lastpos;
	if (dir == DIR_TOP && rs_falling(self, slice, pos, used) && **slice)
		return (TRUE);
	*pos = lastpos;
	rs_basic(slice, transform, dir);
	used[pos->x + pos->y * self->w] = 1;
	return (TRUE);
}
