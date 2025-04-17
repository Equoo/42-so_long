/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:12:45 by dderny            #+#    #+#             */
/*   Updated: 2025/04/17 14:02:16 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entities/player.h"
#include "vector2d.h"
#include "collisions.h"

void	player_attack(t_player *self)
{

	self->base->play_anim(self->base, "Attack_1");
}
