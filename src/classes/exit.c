/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:01:30 by dderny            #+#    #+#             */
/*   Updated: 2025/04/25 12:33:57 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entities/exit.h"
#include "classes/entities/player.h"
#include "classes/entity.h"
#include "scene.h"
#include "so_long.h"
#include "texture.h"
#include "vector2d.h"
#include <stdlib.h>
#include <stdint.h>

void	exit_del(t_element **self)
{
	t_exit	*exit;

	exit = (*self)->parent;
	entity_del(self);
	if (exit)
		free(exit);
}

t_exit	*ft_exit(t_scene *scene)
{
	t_entity *entity;
	t_exit *exit;

	entity = ft_entity(scene);
	if (!entity)
		return (NULL);
	exit = ft_calloc(1, sizeof(t_exit));
	if (!exit)
	{
		entity->base->del(&entity->base);
		return (NULL);
	}
	exit->entity = entity;
	exit->entity->on_collide = &exit_on_collide;
	exit->exit = exit;
	exit->base = entity->base;
	exit->base->texture = ft_texture(&scene->env->render, "textures/exit.xpm");
	exit->base->zindex = 10;
	exit->base->parent = exit;
	exit->base->anim = "all";
	exit->base->del = &exit_del;
	exit->entity->base = exit->base;
	return (exit);
}

void	exit_on_collide(t_entity *self, t_element *other, t_sweep data)
{
	t_player	*player;

	(void)data;
	if (!other || other->class != CLASS_PLAYER)
		return ;
	player = other->parent;
	if (!player)
		return ;
	player->base->draw = NULL;
	process_close(self->base->scene->env);
}
