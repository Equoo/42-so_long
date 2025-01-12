/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:44:26 by dderny            #+#    #+#             */
/*   Updated: 2025/01/12 16:11:47 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct s_gameenv {
	void	*mlx;
	void	*win;
	double	time;
	double	lastframe;
	double	frametime;
}	t_gameenv;

double	ft_uptime();

#endif