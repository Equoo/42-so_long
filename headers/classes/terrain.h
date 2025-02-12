/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terrain.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:32 by dderny            #+#    #+#             */
/*   Updated: 2025/02/12 10:21:48 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERRAIN_H
# define TERRAIN_H
# include "element.h"
# include "classes/texture.h"
# include "map.h"

typedef struct s_terrain
{
	t_element	*base;
	t_texture	*texture;
	t_map		*map;

	void		(*del)(t_terrain *self);
	int			(*collide)(t_terrain *self, t_float2d pos);
}				t_terrain;

void		terrain_draw(t_terrain *self);
void		terrain_collide(t_terrain *self, t_float2d pos);

t_terrain	*ft_terrain(char *texpath, t_map *map);

void		terrain_del(void);

#endif