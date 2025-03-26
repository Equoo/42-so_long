/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:32 by dderny            #+#    #+#             */
/*   Updated: 2025/03/25 15:53:38 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "classes/entity.h"
# include "classes/entities/actor.h"

typedef struct s_player
{
	t_element	*base;
	t_entity	*entity;
	t_actor		*actor;
	void		*parent;
	int			health;
	int			anim_cycle;

}				t_player;

void		player_del(t_element **self);

t_player	*ft_player(t_scene *scene);

#endif
