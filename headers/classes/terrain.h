/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terrain.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:56:50 by dderny            #+#    #+#             */
/*   Updated: 2025/04/26 21:36:23 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERRAIN_H
# define TERRAIN_H
# include "classes/element.h"
# include "ft_vector.h"
# include "vector2d.h"

# define MAP_CHARS "01CEP"
# define MAP_COIN 'C'
# define MAP_PLAYER 'P'
# define MAP_EXIT 'E'
# define MAP_WALL '1'
# define MAP_VOID '0'
# define MAP_MAXSIZE 16384

typedef struct s_terrain
{
	t_element	*base;
	char		*grid;
	int			w;
	int			h;
	int			spawn;
	int			exit;
	t_vector	coins;
}				t_terrain;

typedef struct s_prob
{
	int			rate;
	t_2int2d	size;
	char		slice[32];
}				t_prob;

char			getindir(t_terrain *self, t_int2d pos, int dir);
int				get_facing(t_terrain *self, t_int2d pos, int dirs[4]);
t_int2d			getposindir(t_int2d pos, int dir);

typedef t_bool	(*t_frule)(t_terrain *self, t_int2d pos, char **slice,
		t_transform *transform);

typedef t_bool	(*t_srule)(t_terrain *self, t_int2d *pos, char **slice,
		t_transform *transform, int *used);

t_bool	rs_other(t_terrain *self, t_int2d *pos, char **slice,
			t_transform *transform, int *used);
t_bool	rs_corgrass(t_terrain *self, t_int2d *pos, char **slice,
			t_transform *transform, int *used);

t_bool			rule_topgrass(t_terrain *self, t_int2d pos, char **slice,
					t_transform *transform);
t_bool			rule_corgrass(t_terrain *self, t_int2d pos, char **slice,
					t_transform *transform);
t_bool			rule_platform(t_terrain *self, t_int2d pos, char **slice,
					__attribute__((unused)) t_transform *transform);

void			terrain_load(t_terrain *self, char *path);
int				terrain_findpath(t_terrain *self, int *checkedmap, t_int2d pos,
					t_int2d last);
void			terrain_draw(t_element *self, t_render *render);

t_terrain		*ft_terrain(t_scene *scene, char *mappath, char *texpath);

void			terrain_del(t_element **self);

#endif
