/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:39:08 by dderny            #+#    #+#             */
/*   Updated: 2025/03/24 18:23:02 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entity.h"
#include "classes/scene.h"
#include <libft.h>

void	entity_del(t_element **self)
{
	t_entity *entity;

	entity = cast_entity((*self)->parent);
	element_del(self);
	if (entity)
		free(entity);
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
	entity->entity = entity;
	entity->base->parent = entity;
	entity->base->class = CLASS_ENTITY;
	entity->base->del = entity_del;
	return (entity);
}

t_entity	*cast_entity(void *entity)
{
	if (!entity)
		return (NULL);
	return ((t_entity *)(((uintptr_t *)entity))[1]);
}
