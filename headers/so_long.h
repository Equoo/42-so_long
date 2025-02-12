/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:44:26 by dderny            #+#    #+#             */
/*   Updated: 2025/02/11 01:53:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef TICK
#  define TICK 10000
# endif

# include "classes/texture.h"

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
	void	*mlx;
	void	*win;
	double	time;
	double	lastframe;
	double	frametime;
	int		width;
	int		height;

	t_texture	*terrain;	
	t_texture	*character;	
}			t_gameenv;

int			update(t_gameenv *env);

double		uptime(void);

#endif