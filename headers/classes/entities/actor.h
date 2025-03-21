/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:32 by dderny            #+#    #+#             */
/*   Updated: 2025/03/21 16:38:41 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTOR_H
# define ACTOR_H

# include "classes/entity.h"

typedef struct s_actor
{
	t_element	*base;
	t_entity	*entity;
	void		*parent;
	int			health;
	int			anim_cycle;

	char		*(*anim_couroutine)(struct s_actor *self);
	void		(*movement)(struct s_actor *self);
}				t_actor;

t_actor		*ft_actor(t_scene *scene);

#endif
