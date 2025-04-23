/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:42 by dderny            #+#    #+#             */
/*   Updated: 2025/04/24 01:38:13 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/element.h"
#include "scene.h"
#include "so_long.h"
#include <libft.h>
#include <stdint.h>

void	do_nothing(void *ptr)
{
	(void)ptr;
}

void	element_del(t_element **self)
{
	t_scene	*scene;
	t_list	*elem;

	if (!self || !*self)
		return ;
	scene = (*self)->scene;
	if (scene && !scene->removed && scene->elements)
	{
		elem = scene->elements;
		while (elem && elem->next)
		{
			if (((t_element *)elem->next->content)->id == (*self)->id)
				break ;
			elem = elem->next;
		}
		__builtin_printf("Element %d deleted, %p\n", (*self)->id, elem->next);
		if (elem->next)
			ft_lstrmone(&elem->next, &do_nothing);
		else if (((t_element *)elem->content)->id == (*self)->id)
			ft_lstrmone(&scene->elements, &do_nothing);
		__builtin_printf("Element %d deleted, %p\n", (*self)->id, elem->next);
	}
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
	element->internal_update = &element_internal_update;
	element->play_anim = &element_play_anim;
	element->id = elements_count;
	return (element);
}

t_element	*cast_element(void *element)
{
	if (!element)
		return (NULL);
	return ((t_element *)(*(uintptr_t *)element));
}

void			element_internal_update(t_element *self)
{
	t_gameenv *env;

	env = self->scene->env;
	if (self->anim)
	{
		if (!self->last_anim_time)
			self->last_anim_time = env->time;
		self->cycle = (env->time - self->last_anim_time) / texture_slice_time(
				self->texture, self->anim);
		if (self->cycle >= 1)
		{
			self->cycle = 0;
			self->last_anim_time = env->time;
		}
	}
	if (self->force_anim_time && self->force_anim_time < env->time)
	{
		self->cycle = 0;
		self->last_anim_time = env->time;
		self->force_anim_time = 0;
	}
	if (!self->force_anim_time && self->anim_coroutine)
		self->anim_coroutine(self, &env->render);
	if (self->update)
		self->update(self);
}
