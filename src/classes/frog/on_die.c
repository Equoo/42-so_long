/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_die.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:27:49 by dderny            #+#    #+#             */
/*   Updated: 2025/04/24 22:57:17 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entities/actor.h"
#include "classes/entities/player.h"

void	frog_on_die(t_actor *self)
{
	t_player	*player;

	player = self->base->scene->ply;
	if (!self->base->scene->removed && player)
		player->coins += 1;
}