/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:42 by dderny            #+#    #+#             */
/*   Updated: 2025/03/26 04:33:30 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/element.h"
#include "so_long.h"
#include <libft.h>
#include <stdint.h>

void	element_del(t_element **self)
{
	if ((*self)->anim)
		free((*self)->anim);
	free(*self);
	*self = NULL;
}

t_element	*ft_element(t_scene *scene)
{
	static int  elements_count = 0;
	t_element *element;

	element = ft_calloc(1, sizeof(t_element));
	if (!element)
		return (NULL);
	elements_count++;
	element->base = element;
	element->class = CLASS_ELEMENT;
	element->scene = scene;
	element->del = &element_del;
	element->update = &element_update;
	element->id = elements_count;
	return (element);
}

t_element	*cast_element(void *element)
{
	if (!element)
		return (NULL);
	return ((t_element *)(*(uintptr_t *)element));
}

void			element_update(t_element *self)
{
	t_gameenv *env;

	env = self->scene->env;
	if (self->anim)
	{
		if (!self->last_anim_time)
			self->last_anim_time = env->time;
		self->cycle = (env->time - self->last_anim_time)
				/ texture_slice_time(self->texture, self->anim);
		if (self->cycle >= 1)
		{
			self->cycle = 0;
			self->last_anim_time = env->time;
		}
	}
}
