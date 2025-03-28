/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:32 by dderny            #+#    #+#             */
/*   Updated: 2025/03/28 13:48:41 by dderny           ###   ########.fr       */
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
	int			anim_cycle;

	char		*(*anim_couroutine)(struct s_actor *self);
	void		(*move)(struct s_actor *self, int dir);
}				t_actor;

void	actor_draw(t_element *self, t_img *buffer);
void	actor_del(t_element **self);

void	actor_move(t_actor *self, int dir);

t_actor		*ft_actor(t_scene *scene);
t_actor		*cast_actor(void *actor);

#endif
