/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:44:26 by dderny            #+#    #+#             */
/*   Updated: 2025/03/24 04:45:01 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include "classes/scene.h"
# ifndef TICK
#  define TICK 240
# endif

# include "classes/texture.h"
# include "classes/entities/actor.h"
# include "classes/terrain.h"

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_gameenv
{
	void		*mlx;
	void		*win;
	double		time;
	double		lastframe;
	double		frametime;
	int			width;
	int			height;
	int			seed;

	t_scene		*scene;
	t_list		*scenes_lst;

	t_texture	*back0;
	t_texture	*back1;
	t_texture	*back2;
}			t_gameenv;

int			update(t_gameenv *env);

double		uptime(void);

#endif
