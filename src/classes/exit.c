/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:01:30 by dderny            #+#    #+#             */
/*   Updated: 2025/04/25 22:55:56 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entities/exit.h"
#include "classes/entities/player.h"
#include "classes/entity.h"
#include "classes/terrain.h"
#include "ft_printf.h"
#include "scene.h"
#include "so_long.h"
#include "texture.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void	exit_del(t_element **self)
{
	t_exit	*exit;

	exit = (*self)->parent;
	entity_del(self);
	if (exit)
		free(exit);
}

static void	init_frog(t_scene *scene, t_exit *exit, t_entity *entity)
{
	exit->entity = entity;
	exit->entity->on_collide = &exit_on_collide;
	exit->entity->nogravity = TRUE;
	exit->base = entity->base;
	exit->base->texture = ft_texture(&scene->env->render,
			"./textures/exit.xpm");
	exit->base->txt_off_pos = (t_float2d){-8, -19};
	exit->entity->hull = (t_aabb){{-8, -19}, {8, 0}, {0}, {0}};
	exit->base->zindex = 10;
	exit->base->parent = exit;
	exit->base->anim = "all";
	exit->base->del = &exit_del;
	exit->entity->base = exit->base;
}

t_exit	*ft_exit(t_scene *scene)
{
	t_entity	*entity;
	t_exit		*exit;

	entity = ft_entity(scene);
	if (!entity)
		return (NULL);
	exit = ft_calloc(1, sizeof(t_exit));
	if (!exit)
	{
		entity->base->del(&entity->base);
		return (NULL);
	}
	init_frog(scene, exit, entity);
	return (exit);
}

void	exit_on_collide(t_entity *self, t_element *other, t_sweep data)
{
	t_player	*player;

	(void)data;
	if (!other || other->class != CLASS_PLAYER)
		return ;
	player = other->parent;
	if (!player
		|| player->coins
		!= ((t_terrain *)other->scene->terrain)->coins.actual_size)
		return ;
	player->base->draw = NULL;
	ft_printf("Congratulations !\n");
	ft_printf("You collected all the coins in %fs and %u grounded moves!\n",
		other->scene->env->time - other->scene->env->start_time,
		(uint)player->walk_count);
	process_close(self->base->scene->env);
}
