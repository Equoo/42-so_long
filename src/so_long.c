/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:03:13 by dderny            #+#    #+#             */
/*   Updated: 2025/03/27 02:04:07 by dderny           ###   ########.fr       */
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
#include "classes/entities/player.h"
#include "so_long.h"
#include "classes/vector2d.h"
#include "error.h"

#include <X11/keysym.h>
#include <X11/X.h>

int	process_close(t_gameenv *env)
{
	ft_lstclear(&env->scenes_lst, &scene_del);
	ft_lstclear(texture_cache(), &texture_del);
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
		if (scene->terrain && lst_scene)
			free(lst_scene);
		scene_del(scene);
		return (1);
	}
	ft_lstadd_front(&env->scenes_lst, lst_scene);
	env->scene = scene;
	return (0);
}


int	down_key(int keycode, t_gameenv *env)
{
	__builtin_printf("Key, %d\n", keycode);
	if (keycode == 'w')
		env->ply->actor->move(env->ply->actor, 2);
	if (keycode == 'a')
		env->ply->actor->move(env->ply->actor, 0);
	if (keycode == 's')
		env->ply->actor->move(env->ply->actor, 3);
	if (keycode == 'd')
		env->ply->actor->move(env->ply->actor, 1);
	if (keycode == XK_Escape)
		process_close(env);
	return (0);
}

void	game_init(t_gameenv *env, char *mappath)
{
	load_map(env, mappath);
	if (errno)
		return ;
	scene_add(env->scene, ft_background(env->scene));
	t_player	*player = ft_player(env->scene);
	scene_add(env->scene, player);
	player->base->pos = (t_float2d){50, 50};
	env->ply = player;
	if (errno)
		return ;

	env->seed = ft_uptime();
	mlx_hook(env->win, ON_DESTROY, 0, &process_close, env);
	mlx_hook(env->win, KeyPress, KeyPressMask, &down_key, env);
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
	env.win = NULL;
	env.win = mlx_new_window(env.mlx, env.width, env.height, "So long");
	if (!env.win)
		return (process_close(&env));
	game_init(&env, argv[1]);
	if (errno)
		return (process_close(&env));
	mlx_loop(env.mlx);
	return (EXIT_SUCCESS);
}
