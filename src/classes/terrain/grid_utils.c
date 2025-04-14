/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 22:51:14 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "vector2d.h"

char	getindir(t_terrain *self, t_int2d pos, int dir)
{
	const int dirs[][2] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};

	if (pos.x + dirs[dir][0] < 0 || pos.x + dirs[dir][0] >= self->w
		|| pos.y + dirs[dir][1] < 0 || pos.y + dirs[dir][1] >= self->h)
		return (MAP_WALL);
	return (self->grid[pos.x + pos.y * self->w + dirs[dir][0] + dirs[dir][1] * self->w]);
}

int	get_facing(t_terrain *self, t_int2d pos, int dirs[4])
{
	int			cur_dirs[4];
	int			count;
	int			i;

	count = 0;
	i = 0;
	while (i < 4)
	{
		cur_dirs[i] = 0;
		if (getindir(self, pos, i) == MAP_WALL)
		{
			cur_dirs[i] = 1;
			count++;
		}
		i++;
	}
	ft_memcpy(dirs, cur_dirs, sizeof(int) * 4);
	return (count);
}
