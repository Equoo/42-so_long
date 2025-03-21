/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:39:08 by dderny            #+#    #+#             */
/*   Updated: 2025/03/21 16:57:58 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entity.h"
#include "classes/scene.h"
#include <libft.h>

void	entity_del(t_element **self)
{
	if ((*self)->parent)
		free((*self)->parent);
	free(*self);
	*self = NULL;
}

t_entity	*ft_entity(t_scene *scene)
{
	t_element *base;
	t_entity *entity;

	base = ft_element(scene);
	if (!base)
		return (NULL);
	entity = ft_calloc(1, sizeof(t_entity));
	if (!entity)
	{
		base->del(&base);
		return (NULL);
	}
	*entity = (t_entity){0};
	entity->base = base;
	entity->base->parent = entity;
	entity->base->class = CLASS_ENTITY;
	entity->base->del = entity_del;
	return (entity);
}
