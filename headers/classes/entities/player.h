/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:32 by dderny            #+#    #+#             */
/*   Updated: 2025/04/16 00:53:24 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "classes/entity.h"
# include "classes/entities/actor.h"
# include "ft_bool.h"

typedef struct s_player
{
	t_element	*base;
	t_entity	*entity;
	t_actor		*actor;
	void		*parent;
	t_bool		is_jumping;
}				t_player;

void		player_del(t_element **self);

void		player_update(t_element *self);
void		player_anim_coroutine(t_element *self, t_render *render);

t_player	*ft_player(t_scene *scene);

#endif
