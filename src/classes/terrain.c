/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terrain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 03:15:23 by dderny            #+#    #+#             */
/*   Updated: 2025/02/12 18:30:44 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "so_long.h"
#include "classes/texture.h"
#include "classes/terrain.h"

void	*terrain_del(t_terrain *self)
{
	if (self->texture)
		texture_del(&self->texture);
	if (self->grid)
		free(self->grid);
	if (self->base)
		self->base->del(self->base);
	free(self);
	return (NULL);
}

int	terrain_collide(t_terrain *self, t_float2d pos)
{
	(void)self;
	(void)pos;
	return (0);	
}

t_terrain	*ft_terrain(char *mappath, char *texpath, void *env)
{
	t_terrain	*terrain;

	terrain = (t_terrain *)ft_calloc(1, sizeof(t_terrain));
	if (terrain)
		terrain->base = ft_element();
	if (terrain && terrain->base)
		terrain->texture = ft_texture(texpath, ((t_gameenv *)env)->mlx);
	if (terrain && terrain->texture)
		terrain_load(terrain, mappath);
	if (!terrain || !terrain->base || !terrain->texture || !terrain->grid)
		return (terrain_del(terrain));
	terrain->base->parent = terrain;
	terrain->env = env;
	terrain->del = &terrain_del;
	terrain->collide = &terrain_collide;
	terrain->base->draw = &terrain_draw;
	return (terrain);
}
