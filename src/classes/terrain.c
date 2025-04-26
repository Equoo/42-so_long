/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terrain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 03:15:23 by dderny            #+#    #+#             */
/*   Updated: 2025/04/26 19:58:00 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include <stdlib.h>
#include "ft_vector.h"
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
		if (terrain->coins.data)
			vec_destroy(&terrain->coins);
		free(terrain);
	}
}

static void	init(t_terrain *terrain)
{
	terrain->base->class = CLASS_TERRAIN;
	terrain->base->parent = terrain;
	terrain->base->del = &terrain_del;
	terrain->base->draw = &terrain_draw;
}

t_terrain	*ft_terrain(t_scene *scene, char *mappath, char *texpath)
{
	t_terrain	*terrain;

	terrain = (t_terrain *)ft_calloc(1, sizeof(t_terrain));
	if (!terrain)
		return (NULL);
	terrain->base = ft_element(scene, 2);
	if (terrain->base)
		terrain->base->texture = ft_texture(&scene->env->render, texpath);
	if (terrain->base && terrain->base->texture)
		terrain->coins = vec_new(32, sizeof(int));
	if (terrain->coins.data)
		terrain_load(terrain, mappath);
	if (!terrain->base || !terrain->base->texture
		|| !terrain->coins.data || !terrain->grid)
	{
		if (terrain->coins.data)
			vec_destroy(&terrain->coins);
		if (terrain->base)
			terrain->base->del(&terrain->base);
		free(terrain);
		return (NULL);
	}
	init(terrain);
	return (terrain);
}
