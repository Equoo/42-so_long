/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terrain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 03:15:23 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include <stdlib.h>
#include "so_long.h"
#include "classes/terrain.h"

void	terrain_del(t_element **self)
{
	t_terrain	*terrain;

	terrain = (t_terrain *)(*self)->parent;
	element_del(self);
	if (terrain)
	{
		if (terrain->grid)
			free(terrain->grid);
		free(terrain);
	}
}

t_terrain	*ft_terrain(t_scene *scene, char *mappath, char *texpath)
{
	t_terrain	*terrain;

	terrain = (t_terrain *)ft_calloc(1, sizeof(t_terrain));
	if (!terrain)
		return (NULL);
	terrain->base = ft_element(scene);
	if (terrain->base)
		terrain->base->texture = ft_texture(&scene->env->render, texpath);
	if (terrain->base && terrain->base->texture)
		terrain_load(terrain, mappath);
	if (!terrain->base || !terrain->base->texture || !terrain->grid)
	{
		terrain->base->del(&terrain->base);
		free(terrain);
		return (NULL);
	}
	terrain->base->parent = terrain;
	terrain->collide = &terrain_collide;
	terrain->base->del = &terrain_del;
	terrain->base->draw = &terrain_draw;
	terrain->base->zindex = 1;
	return (terrain);
}
