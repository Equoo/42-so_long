/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:46:39 by dderny            #+#    #+#             */
/*   Updated: 2025/04/18 16:33:23 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"

int	terrain_findpath(t_terrain *map, int *checkedmap, t_int2d pos, t_int2d last)
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
		if (map->grid[map->w * y + x] != MAP_WALL)
			if (terrain_findpath(map, checkedmap, (t_int2d){x, y}, pos))
				return (1);
		i++;
	}
	return (0);
}
