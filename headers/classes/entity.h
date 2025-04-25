/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:32 by dderny            #+#    #+#             */
/*   Updated: 2025/04/25 12:22:55 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

# include "collisions.h"
# include "element.h"
# include "vector2d.h"
# include <ft_bool.h>
# include <unistd.h>

# define GRAVITY 9.1

typedef struct s_entity
{
	t_element	*base;
	void		*entity;
	void		*parent;
	t_float2d	velocity;
	t_aabb		hull;
	t_bool		b_isground;
	t_bool		nocollision;
	t_float2d	gravity_dir;
	t_bool		nogravity;

	void		(*on_collide)(struct s_entity *self, t_element *other,
				t_sweep data);
}				t_entity;

void			entity_del(t_element **self);
void			entity_physic(t_element *self);

t_entity		*ft_entity(t_scene *scene);
t_entity		*cast_entity(void *entity);

#endif
