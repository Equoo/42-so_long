/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:32 by dderny            #+#    #+#             */
/*   Updated: 2025/01/27 14:28:56 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H
# include "element.h"
# include "vector2d.h"

typedef struct s_entity
{
	t_element	*base;
	t_float2d	velocity;
	t_faabb		hull;

	void		(*collide)(t_entity *self, t_element *element);
	void		(*del)(t_entity *self);
}				t_entity;

t_entity		*ft_entity(void);

void			entity_del(void);

#endif