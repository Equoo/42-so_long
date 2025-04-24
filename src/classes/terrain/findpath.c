/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:46:39 by dderny            #+#    #+#             */
/*   Updated: 2025/04/24 18:50:05 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "ft_vector.h"
#include "vector2d.h"
#include <fcntl.h>
#include <stddef.h>
#include <sys/types.h>

static int	findpath(t_terrain *map, int *checkedmap, t_int2d pos, t_int2d last, t_vector *queue)
{
	const int	dir[4][2] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};
	int			i;
	int			x;
	int			y;

	i = 0;
	while (i < 4)
	{
		x = pos.x + dir[i][0];
		y = pos.y + dir[i][1];
		if (((last.x == x && last.y == y) || checkedmap[map->w * y + x]) && ++i)
			continue ;
		checkedmap[map->w * y + x] = 1;
		if (map->grid[map->w * y + x] == MAP_PLAYER)
			return (1);
		if (map->grid[map->w * y + x] != MAP_WALL && map->grid[map->w * y + x] != MAP_EXIT)
		{
			((t_2int2d *)queue->data)[queue->actual_size] = (t_2int2d){(t_int2d){x, y}, pos};
			queue->actual_size++;
		}
		i++;
	}
	return (0);
}

int	terrain_findpath(t_terrain *map, int *checkedmap, t_int2d pos, t_int2d last)
{
	t_vector	queue;
	t_2int2d	val;
	uint		i;
	int			res;

	queue = vec_new(map->w * map->h, sizeof(t_2int2d));
	if (!queue.data)
		return (-1);
	*((t_2int2d *)queue.data) = (t_2int2d){pos, last};
	queue.actual_size = 1;
	res = 0;
	i = -1;
	while (++i < queue.actual_size && !res)
	{
		val = ((t_2int2d *)queue.data)[i];
		res = findpath(map, checkedmap, val.a, val.b, &queue);
	}
	vec_destroy(&queue);
	return (res);
}
