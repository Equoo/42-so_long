/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:44:26 by dderny            #+#    #+#             */
/*   Updated: 2025/01/15 17:31:56 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef TICK
#  define TICK 20
# endif

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
}			t_gameenv;

int			update(t_gameenv *env);

double		uptime(void);

#endif