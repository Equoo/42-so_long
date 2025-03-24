/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:03:13 by dderny            #+#    #+#             */
/*   Updated: 2025/03/24 18:08:20 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <mlx.h>
#include <ft_time.h>
#include <errno.h>
#include <libft.h>
#include <ft_vector.h>
#include "classes/background.h"
#include "classes/scene.h"
#include "classes/texture.h"
#include "classes/terrain.h"
#include "so_long.h"
#include "error.h"

static void texturecache_del(void *content)
{
	t_texture *tex;

	tex = (t_texture *)content;
	texture_del(&tex);
}

static void scenes_del(void *content)
{
	scene_del(content);
}

int	process_close(t_gameenv *env)
{
	ft_lstclear(&env->scenes_lst, &scenes_del);
	ft_lstclear(texture_cache(), &texturecache_del);
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


int	load_map(t_gameenv *env, char *path)
{
	t_scene	*scene;
	t_list	*lst_scene;

	scene = ft_scene(env, path);
	if (!scene)
		return (1);
	scene->terrain = ft_terrain(scene, path, "./textures/stringstar_fields.xpm");
	if (scene->terrain)
	{
		scene_add(scene, scene->terrain);
		lst_scene = ft_lstnew(scene);
	}
	if (!scene->terrain || !lst_scene)
	{
		if (lst_scene)
			free(lst_scene);
		scene_del(&scene);
		return (1);
	}
	ft_lstadd_front(&env->scenes_lst, lst_scene);
	env->scene = scene;
	return (0);
}


void	game_init(t_gameenv *env, char *mappath)
{
	//if (env->character)
	//	env->character->base->texture = ft_texture("./textures/cat.xpm", env->mlx);

	load_map(env, mappath);
	if (errno)
		return ;
	scene_add(env->scene, ft_background(env->scene));
	if (errno)
		return ;

	env->seed = ft_uptime();
	mlx_hook(env->win, ON_DESTROY, 0, process_close, env);
	mlx_loop_hook(env->mlx, &update, env);
}

int	main(int argc, char **argv)
{
	t_gameenv	env;

	(void)argv;
	env = (t_gameenv){};
	if (argc != 2)
	{
		errno = EINVAL;
		return (process_close(&env));
	}
	env.mlx = mlx_init();
	if (!env.mlx)
		return (process_close(&env));
	env.width = 1920;
	env.height = 1080;
	//mlx_get_screen_size(env.mlx, &env.width, &env.height);
	errno = 0;
	env.win = mlx_new_window(env.mlx, env.width, env.height, "So long");
	if (!env.win)
		return (process_close(&env));
	game_init(&env, argv[1]);
	if (errno)
		return (process_close(&env));
	mlx_loop(env.mlx);
	return (EXIT_SUCCESS);
}
