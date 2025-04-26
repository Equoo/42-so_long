/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:18:20 by dderny            #+#    #+#             */
/*   Updated: 2025/04/26 02:44:31 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/background.h"
#include "classes/element.h"
#include "classes/entities/exit.h"
#include "classes/entities/frog.h"
#include "classes/entities/player.h"
#include "classes/terrain.h"
#include "error.h"
#include "ft_time.h"
#include "ft_vector.h"
#include "libft.h"
#include "scene.h"
#include "so_long.h"
#include "vector2d.h"
#include <X11/X.h>
#include <X11/Xutil.h>
#include <errno.h>
#include <stdlib.h>

int	load_map(t_gameenv *env, char *path)
{
	t_scene	*scene;
	t_list	*lst_scene;

	scene = ft_scene(env, path);
	if (!scene)
		return (1);
	scene->terrain = ft_terrain(scene, path,
			"./textures/stringstar_fields.xpm");
	lst_scene = ft_lstnew(scene);
	if (!scene->terrain || !lst_scene)
	{
		if (scene->terrain)
			((t_terrain *)scene->terrain)->base->del(
				&((t_terrain *)scene->terrain)->base);
		if (lst_scene)
			free(lst_scene);
		scene_del(scene);
		return (1);
	}
	ft_lstadd_front(&env->scenes_lst, lst_scene);
	env->scene = scene;
	return (0);
}

static int	add_exitncoins(t_scene *scene, t_terrain *terrain, t_player *player)
{
	t_frog	*element;
	t_exit	*exit;
	int		i;

	exit = ft_exit(scene);
	if (!exit)
		return (1);
	exit->base->pos = float2d_sub((t_float2d){(terrain->exit % terrain->w) * 16,
			(terrain->exit / terrain->w) * 16}, player->entity->hull.min);
	i = 0;
	while (i < terrain->coins.actual_size)
	{
		element = ft_frog(scene);
		if (element)
			cast_element(element)->pos = (t_float2d){(*(int *)vec_get(
					&terrain->coins, i) % terrain->w) * 16,
			(*(int *)vec_get(&terrain->coins, i) / terrain->w)
			* 16};
		else
			break ;
		i++;
	}
	return (0);
}

int	game_init(t_gameenv *env, char *mappath)
{
	void		*element;
	t_scene		*scene;
	t_terrain	*terrain;
	t_player	*player;

	if (load_map(env, mappath) || errno)
		return (1);
	scene = (t_scene *)env->scene;
	element = ft_background(env->scene);
	if (!element)
		return (1);
	player = ft_player(scene);
	if (!player)
		return (1);
	terrain = (t_terrain *)scene->terrain;
	player->base->play_anim(player->base, "Spawn_2");
	player->base->pos = float2d_sub((t_float2d){(terrain->spawn % terrain->w)
			* 16, (terrain->spawn / terrain->w) * 16},
			player->entity->hull.min);
	scene->ply = player;
	scene->seed = ft_uptime();
	if (add_exitncoins(scene, terrain, player)
		|| (scene->seed == -1 && print_error("Seed")))
		return (1);
	return (0);
}
