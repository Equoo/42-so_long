/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 06:58:02 by dderny            #+#    #+#             */
/*   Updated: 2025/03/26 15:31:04 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entities/actor.h"
#include "so_long.h"

void	actor_move(struct s_actor *self, int dir)
{
	if (dir == 0)
		self->base->pos.x -= 100 * ((t_gameenv *)self->base->scene->env)->frametime;
	else if (dir == 1)
		self->base->pos.x += 100 * ((t_gameenv *)self->base->scene->env)->frametime;
	else if (dir == 2)
		self->base->pos.y -= 100 * ((t_gameenv *)self->base->scene->env)->frametime;
	else if (dir == 3)
		self->base->pos.y += 100 * ((t_gameenv *)self->base->scene->env)->frametime;
}
