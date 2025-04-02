/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:18:20 by dderny            #+#    #+#             */
/*   Updated: 2025/04/02 20:16:50 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"
#include "input.h"
#include "so_long.h"
#include "error.h"
#include "scene.h"
#include "classes/entities/player.h"
#include "classes/background.h"
#include "classes/terrain.h"
#include <X11/X.h>
#include <errno.h>

void	tick_game(t_gameenv *env)
{
	t_scene		*scene;
	t_player	*ply;
	t_list		*node;
	t_element	*node_elem;
	int modifier;

	scene = (t_scene *)env->scene;
	ply = scene->ply;
	if (input_ispressed('w', env))
		ply->actor->move(ply->actor, 2, 0);
	modifier = MOVE_JOG;
	if (input_isdown(XK_Alt_L, env))
		modifier = MOVE_WALK;
	if (input_isdown(XK_Shift_L, env))
		modifier = MOVE_SPEED;
	if (input_isdown('a', env))
		ply->actor->move(ply->actor, 0, modifier);
	if (input_isdown('d', env))
		ply->actor->move(ply->actor, 1, modifier);
	node = scene->elements;
	while (node)
	{
		node_elem = (t_element *)node->content;
		if (node_elem->update)
			node_elem->update(node_elem);
		node = node->next;
	}
}

int	load_map(t_gameenv *env, char *path)
{
	t_scene	*scene;
	t_list	*lst_scene;

	scene = ft_scene(env, path);
	if (!scene)
		return (1);
	scene->terrain = ft_terrain(scene, path, "./textures/stringstar_fields.xpm");
	lst_scene = ft_lstnew(scene);
	if (scene_add(scene, scene->terrain) || !lst_scene)
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

int	game_init(t_gameenv *env, char *mappath)
{
	void		*element;
	t_scene		*scene;
	t_player	*player;

	if (load_map(env, mappath) || errno)
		return (1);
	element = ft_background(env->scene);
	if (scene_add(env->scene, element) && print_error("Background"))
		return (1);
	player = ft_player(env->scene);
	if (scene_add(env->scene, player) && print_error("Player"))
		return (1);
	player->base->pos = (t_float2d){80, 60};
	scene = (t_scene *)env->scene;
	scene->ply = player;
	scene->seed = ft_uptime();
	if (scene->seed == -1 && print_error("Seed"))
		return (1);
	return (0);
}
