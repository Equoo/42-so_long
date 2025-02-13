/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terrain.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:56:50 by dderny            #+#    #+#             */
/*   Updated: 2025/02/13 15:55:43 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERRAIN_H
# define TERRAIN_H
# include <mlx_int.h>
# include "classes/element.h"
# include "classes/vector2d.h"
# include "classes/texture.h"

# define MAP_CHARS "01CEP"
# define MAP_COIN 'C'
# define MAP_PLAYER 'P'
# define MAP_EXIT 'E'
# define MAP_WALL '1'
# define MAP_VOID '0'

typedef struct s_terrain
{
	void		*env;
	t_element	*base;
	t_texture	*texture;
	char		*grid;
	int			w;
	int			h;
	int			spawn;
	int			exit;
	int			*coins;

	void		*(*del)(struct s_terrain *self);
	int			(*collide)(struct s_terrain *self, t_float2d pos);
}				t_terrain;

void		terrain_load(t_terrain *self, char *path);
int			terrain_findpath(t_terrain *self, int *checkedmap, t_int2d pos, t_int2d last);
void		terrain_draw(t_element *self, t_img *buffer);
int			terrain_collide(t_terrain *self, t_float2d pos);

t_terrain	*ft_terrain(char *mappath, char *texpath, void *env);

void		*terrain_del(t_terrain *self);

#endif