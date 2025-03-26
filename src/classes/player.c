/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 01:32:11 by dderny            #+#    #+#             */
/*   Updated: 2025/03/25 02:09:29 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entities/player.h"
#include "classes/scene.h"
#include "classes/texture.h"
#include "libft.h"
#include "so_long.h"
#include <stdlib.h>
#include <stdint.h>

void	player_del(t_element **self)
{
	t_player	*player;

	player = (t_player *)(*self)->parent;
	actor_del(self);
	if (player)
		free(player);
}

t_player	*ft_player(t_scene *scene)
{
	t_actor *actor;
	t_player *player;

	actor = ft_actor(scene);
	if (!actor)
		return (NULL);
	player = ft_calloc(1, sizeof(t_player));
	if (!player)
	{
		actor->base->del(&actor->base);
		return (NULL);
	}
	player->base = actor->base;
	player->entity = actor->entity;
	player->actor = actor;
	player->base->class = CLASS_PLAYER;
	player->base->parent = player;
	player->base->del = &player_del;
	player->base->anim = ft_strdup("Idle_2");
	player->base->texture = ft_texture("./textures/cat.xpm", ((t_gameenv *)scene->env)->mlx);
	if (!player->base->texture)
		player->base->del(&player->base);
	return (player);
}

t_player	*cast_player(void *player)
{
	if (!player)
		return (NULL);
	return ((t_player *)(((uintptr_t *)player))[2]);
}
