/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frog.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:32 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FROG_H
# define FROG_H

# include "classes/entity.h"
# include "classes/entities/actor.h"

typedef struct s_frog
{
	t_element	*base;
	t_entity	*entity;
	t_actor		*actor;
	void		*parent;
}				t_frog;

void		frog_del(t_element **self);

void		frog_anim_coroutine(t_actor *self);

t_frog		*ft_frog(t_scene *scene);

#endif
