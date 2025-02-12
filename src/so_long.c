/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:03:13 by dderny            #+#    #+#             */
/*   Updated: 2025/02/12 15:59:33 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <ft_printf.h>

#include <stdlib.h>
#include <mlx.h>
#include <stdio.h>
#include <errno.h>
#include "classes/texture.h"
#include "classes/terrain.h"
#include "so_long.h"
#include "render.h"
#include "error.h"

int	process_close(t_gameenv *env)
{
	if (env->character)
		texture_del(&env->character);
	if (env->win)
		mlx_destroy_window(env->mlx, env->win);
	if (env->mlx)
	{
		mlx_destroy_display(env->mlx);
		free(env->mlx);
	}
	if (errno != 11 && errno && print_error("Initialization"))
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void	game_init(t_gameenv *env, char *mappath)
{
	env->terrain = ft_terrain(mappath, "./textures/stringstar_fields.xpm", env->mlx);
	if (env->terrain)
		env->character = ft_texture("./textures/cat.xpm", env->mlx);
	mlx_hook(env->win, ON_DESTROY, 0, process_close, env);
	mlx_loop_hook(env->mlx, &update, env);
}

int	main(int argc, char **argv)
{
	t_gameenv	env;

	if (argc != 1)
	{
		errno = EINVAL;
		return (process_close(&env));
	}
	(void)argv;
	env = (t_gameenv){};
	env.mlx = mlx_init();
	if (!env.mlx)
		return (process_close(&env));
	env.width = 1920;
	env.height = 1080;
	//mlx_get_screen_size(env.mlx, &env.width, &env.height);
	env.win = mlx_new_window(env.mlx, env.width, env.height, "So long");
	if (!env.win)
		return (process_close(&env));
	errno = 0;
	game_init(&env, argv[1]);
	if (errno)
		return (process_close(&env));
	mlx_loop(env.mlx);
	return (EXIT_SUCCESS);
}
