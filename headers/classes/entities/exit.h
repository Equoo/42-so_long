/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:32 by dderny            #+#    #+#             */
/*   Updated: 2025/04/26 01:49:59 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include "classes/entity.h"
# include "collisions.h"
# include "scene.h"

typedef struct s_exit
{
	t_element	*base;
	t_entity	*entity;
	void		*parent;
}				t_exit;

void			exit_on_collide(t_entity *self, t_element *other, t_sweep data);
void			exit_del(t_element **self);

t_exit			*ft_exit(t_scene *scene);

#endif
