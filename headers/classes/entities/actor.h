/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:32 by dderny            #+#    #+#             */
/*   Updated: 2025/04/08 05:49:59 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTOR_H
# define ACTOR_H

# include "classes/entity.h"

typedef struct s_actor
{
	t_element	*base;
	t_entity	*entity;
	void		*actor;
	void		*parent;
	int			health;
	int			direction;

	void		(*anim_couroutine)(struct s_actor *self);
	void		(*move)(struct s_actor *self, int dir, int modifier);
}				t_actor;

typedef enum e_move_modifier
{
	MOVE_JOG,
	MOVE_SPEED,
	MOVE_WALK
}				t_move_modifier;

void	actor_draw(t_element *self, t_render *render);
void	actor_del(t_element **self);

void	actor_move(t_actor *self, int dir, int modifier);

t_actor		*ft_actor(t_scene *scene);
t_actor		*cast_actor(void *actor);

#endif
