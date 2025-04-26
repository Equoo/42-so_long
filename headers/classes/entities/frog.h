/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frog.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:32 by dderny            #+#    #+#             */
/*   Updated: 2025/04/27 01:23:15 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FROG_H
# define FROG_H

# include "classes/entities/actor.h"
# include "classes/entity.h"
# include "collisions.h"
# include "texture.h"

typedef struct s_frog
{
	t_element	*base;
	t_entity	*entity;
	t_actor		*actor;
	void		*parent;
	t_texture	*textures[6];
}				t_frog;

void			frog_del(t_element **self);

void			frog_anim_coroutine(t_element *self, t_render *render);
void			frog_on_die(t_actor *self);
void			frog_on_collide(t_entity *self, t_element *other, t_sweep data);

t_frog			*ft_frog(t_scene *scene);

#endif
