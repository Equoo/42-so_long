/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terrain.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:56:50 by dderny            #+#    #+#             */
/*   Updated: 2025/02/12 14:55:45 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERRAIN_H
# define TERRAIN_H
# include "classes/vector2d.h"
# include "element.h"
# include "classes/texture.h"

# define MAP_CHARS "01CEP"
# define MAP_COIN 'C'
# define MAP_PLAYER 'P'
# define MAP_EXIT 'E'
# define MAP_WALL '1'
# define MAP_VOID '0'
# define FOUR_2D_DIRS {{0, -1}, {-1, 0}, {1, 0}, {0, 1}}

typedef struct s_terrain
{
	t_element	*base;
	t_texture	*texture;
	char		*grid;
	int			w;
	int			h;
	int			spawn;
	int			exit;
	int			*coins;

	void		(*del)(struct s_terrain *self);
	int			(*collide)(struct s_terrain *self, t_float2d pos);
}				t_terrain;

void		terrain_load(t_terrain *self, char *path);
int			terrain_findpath(t_terrain *self, int *checkedmap, t_int2d pos, t_int2d last);
void		terrain_draw(t_terrain *self);
int			terrain_collide(t_terrain *self, t_float2d pos);

t_terrain	*ft_terrain(char *mappath, char *texpath, void *mlx);

void		*terrain_del(t_terrain *self);

#endif