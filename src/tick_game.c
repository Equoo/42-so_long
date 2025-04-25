/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tick_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 23:44:48 by dderny            #+#    #+#             */
/*   Updated: 2025/04/25 23:53:01 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/element.h"
#include "classes/entities/player.h"
#include "classes/terrain.h"
#include "ft_bool.h"
#include "ft_vector.h"
#include "input.h"
#include "libft.h"
#include "render.h"
#include "scene.h"
#include "so_long.h"
#include "vector2d.h"
#include <X11/X.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <string.h>

void	tick_key(t_player *ply, t_gameenv *env)
{
	int	modifier;

	if (input_ispressed('w', env))
	{
		ply->actor->move(ply->actor, 2, 0);
		ply->base->play_anim(ply->base, "J_2");
		ply->is_jumping = TRUE;
	}
	modifier = MOVE_JOG;
	if (input_isdown(XK_Alt_L, env))
		modifier = MOVE_WALK;
	if (input_isdown(XK_Shift_L, env))
		modifier = MOVE_SPEED;
	if (input_isdown('a', env))
		ply->actor->move(ply->actor, 0, modifier);
	if (input_isdown('d', env))
		ply->actor->move(ply->actor, 1, modifier);
	if (input_ispressed('s', env))
	{
		ply->entity->gravity_dir = (t_float2d){0, -ply->entity->gravity_dir.y};
		ply->base->txt_off_pos.y = ply->base->txt_off_pos.y + 16
			* ply->entity->gravity_dir.y;
	}
	if (input_ispressed(XK_space, env))
		ply->attack(ply);
}

// NOT MALLOC SAFE
static void	draw_hud(t_gameenv *env, t_scene *scene, char *text)
{
	text = ft_itoa(((t_player *)scene->ply)->coins);
	if (!text)
		return ;
	draw_text(&env->render, "COINS:", (t_float2d){39, 35}, 32);
	draw_text(&env->render, text, (t_float2d){55, 35}, 32);
	free(text);
	text = ft_itoa(((t_terrain *)scene->terrain)->coins.actual_size);
	if (!text)
		return ;
	draw_text(&env->render, "/", (t_float2d){57 + 3 * 4, 35}, 32);
	draw_text(&env->render, text, (t_float2d){61 + 3 * 4, 35}, 32);
	free(text);
	text = ft_itoa(env->smooth_fps);
	if (!text)
		return ;
	draw_text(&env->render, "FPS:", (t_float2d){39, 30}, 32);
	draw_text(&env->render, text, (t_float2d){50, 30}, 32);
	free(text);
	text = ft_itoa((int)((t_player *)scene->ply)->walk_count);
	if (!text)
		return ;
	draw_text(&env->render, "MOVES:", (t_float2d){39, 25}, 32);
	draw_text(&env->render, text, (t_float2d){55, 25}, 32);
	free(text);
}

void	tick_game(t_gameenv *env)
{
	t_scene		*scene;
	t_list		*node;
	t_list		*tmp_node;
	t_element	*node_elem;

	scene = (t_scene *)env->scene;
	tick_key(scene->ply, env);
	node = scene->elements;
	while (node)
	{
		tmp_node = node->next;
		node_elem = (t_element *)node->content;
		if (node_elem->internal_update && scene->ply
			&& (float2d_length(float2d_sub(node_elem->pos,
						cast_element(scene->ply)->pos)) < 2048))
			node_elem->internal_update(node_elem);
		node = tmp_node;
	}
	draw_hud(env, scene, NULL);
}
