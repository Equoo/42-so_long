/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terrain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 03:15:23 by dderny            #+#    #+#             */
/*   Updated: 2025/03/24 02:25:40 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include <stdlib.h>
#include "so_long.h"
#include "classes/texture.h"
#include "classes/terrain.h"

void	terrain_del(t_element **self)
{
	t_terrain	*terrain;

	if ((*self)->parent)
	{
		terrain = (t_terrain *)(*self)->parent;
		if (terrain->grid)
			free(terrain->grid);
		if (terrain->texture)
			texture_del(&terrain->texture);
		free(terrain);
		(*self)->parent = NULL;
	}
	element_del(self);
}

int	terrain_collide(t_terrain *self, t_float2d pos)
{
	(void)self;
	(void)pos;
	return (0);
}

t_terrain	*ft_terrain(t_scene *scene, char *mappath, char *texpath, void *env)
{
	t_terrain	*terrain;

	terrain = (t_terrain *)ft_calloc(1, sizeof(t_terrain));
	if (!terrain)
		return (NULL);
	terrain->base = ft_element(scene);
	if (terrain->base)
		terrain->texture = ft_texture(texpath, ((t_gameenv *)env)->mlx);
	if (terrain->texture)
		terrain_load(terrain, mappath);
	if (!terrain->base || !terrain->texture || !terrain->grid)
	{
		terrain->base->del(&terrain->base);
		return (NULL);
	}
	terrain->base->parent = terrain;
	terrain->env = env;
	terrain->collide = &terrain_collide;
	terrain->base->del = &terrain_del;
	terrain->base->draw = &terrain_draw;
	return (terrain);
}
