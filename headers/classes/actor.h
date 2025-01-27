/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:32 by dderny            #+#    #+#             */
/*   Updated: 2025/01/27 15:48:06 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTOR_H
# define ACTOR_H
# include "entity.h"

typedef struct s_actor
{
	t_entity	*base;
	int			health;

	void		(*collide)(t_actor *self, t_element *element);
	void		(*del)(t_actor *self);
}				t_actor;

t_actor			*ft_actor(void);

void			actor_del(void);

#endif