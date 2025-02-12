/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terrain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 03:15:23 by dderny            #+#    #+#             */
/*   Updated: 2025/02/12 10:22:07 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "classes/texture.h"
#include "classes/terrain.h"
#include "map.h"

void	*terrain_del(t_terrain *self)
{
	if (self->texture)
		texture_del(&self->texture);
	if (self->base)
		self->base->del(self->base);
	free(self);
	return (NULL);
}

t_terrain	*ft_terrain(char *texpath, t_map *map, void *mlx)
{
	t_terrain	*terrain;

	if (!map || !mlx || !texpath)
		return (NULL);
	terrain = (t_terrain *)malloc(sizeof(t_terrain));
	if (!terrain)
		return (NULL);
	terrain->base = ft_element();
	if (!terrain->base)
		return (terrain_del(terrain));
	if (texpath)
	{
		terrain->texture = ft_texture(texpath, mlx);
		if (!terrain->texture)
			return (terrain_del(terrain));
	}
	terrain->map = map;
	terrain->del = &terrain_del;
	terrain->collide = &terrain_collide;
	terrain->base->draw = &terrain_draw;
	return (terrain);
}
