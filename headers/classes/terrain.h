/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terrain.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:56:50 by dderny            #+#    #+#             */
/*   Updated: 2025/03/26 06:05:01 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERRAIN_H
# define TERRAIN_H
# include "classes/element.h"
# include "classes/entity.h"
# include "classes/vector2d.h"

# define MAP_CHARS "01CEP"
# define MAP_COIN 'C'
# define MAP_PLAYER 'P'
# define MAP_EXIT 'E'
# define MAP_WALL '1'
# define MAP_VOID '0'

typedef struct s_terrain
{
	t_element	*base;
	char		*grid;
	int			w;
	int			h;
	int			spawn;
	int			exit;
	int			*coins;

	t_float2d	(*collide)(struct s_terrain *self, t_entity *ent,
					t_float2d vel, t_float2d newpos);
}				t_terrain;

void		terrain_load(t_terrain *self, char *path);
int			terrain_findpath(t_terrain *self, int *checkedmap, t_int2d pos, t_int2d last);
void		terrain_draw(t_element *self, t_img *buffer);
t_float2d	terrain_collide(t_terrain *self, t_entity *ent, t_float2d vel, t_float2d newpos);

t_terrain	*ft_terrain(t_scene *scene, char *mappath, char *texpath);

void		terrain_del(t_element **self);

#endif
